/**
  Section: Included Files
*/

#include "application.h"
#include <stdio.h>
#include "macros.h"
#include "mcc_generated_files/lcd_example.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/ccp1.h"
#include "mcc_generated_files/tmr1.h"

volatile bool fallingEdgeDetected=false;//flag is set when falling edge is detected on port RA1 connected to IR Click
volatile bool ccpCapturedFlag = false;//flag is set if CCP has captured Timer value on falling edge on RC0 (connected to RA1 with CLC as buffer)
volatile uint16_t ccpCapturedVal;// value of CCP capture
uint16_t ccpCapturedValueBuf[DATA_BIT_COUNT];//buffer for storing CCP capture values for 32 bit IR data
uint8_t index;
volatile IR_DATA IR_data;

//duty values for LED dimming when command is received
const uint8_t dutyCycleValArr[MAX_CMD_NO] = {25, 50, 75, 100, 75, 50, 25, 0};

static bool GetEvent(void);
static bool check4Start(void);
static void DisableCapture(void);
static void Init4nextFrame(void);
static e_cmd_status DecodeCmd(void);
static void ControlAction(uint8_t cmd);
static uint8_t Reverse(uint8_t byteVar);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
     main application function being executed in while loop
 Receives command over IR interface using NEC protocol, Decode command, 
 * take corresponding control action and change the brightness of LEDs accordingly
 * @Example
    ApplicationTask();
 */
void ApplicationTask(void) 
{
    static e_app_states appState=GET_EVENT;
    e_cmd_status cmd_status;
    uint8_t rxCommand;
    
    switch(appState) 
    {
        case GET_EVENT:
            if(GetEvent())//check if falling edge is detected on the port pin connected to the IR photo diode 
            {
                //valid falling edge is detected on the port pin, initialize capture
                //enable timer 1, CCP1 and CCP falling edge interrupt for start of frame detection
                TMR1_WriteTimer(0);
                TMR1_StartTimer();
                EnableCCP_Interrupt();
                EnableCCP();
                appState = DETECT_START;
            }
            break;
        case DETECT_START:
            if (ccpCapturedFlag)
            { 
                ccpCapturedFlag=false;
                if (check4Start())
                {
                    appState = CAPTURE_DATA_BITS;// start of frame is detected now capture 32 bits of data from the IR frame
                }
                else
                {
                    DisableCapture();//Error in start of frame
                    lcd_writeString("  Start  Error  ", 0);
                    lcd_writeString("----------------", 1);
                    appState = INIT_FOR_NEXT_FRAME;  
                }    
            }
            else if (TMR1_HasOverflowOccured())
            {
                //falling edge for start of frame is not received for 16.384 ms and timer 1 has overflowed
                Clear_TMR1_OVF();
                DisableCapture();
                lcd_writeString("Start wait Error", 0);
                lcd_writeString("----------------", 1);
                appState = INIT_FOR_NEXT_FRAME;
            }                
            break;
        case CAPTURE_DATA_BITS:
            if (ccpCapturedFlag)
            {
                ccpCapturedFlag=false;

                if (ccpCapturedVal < BIT_TIME_MAX) //check for max bit length
                {
                    ccpCapturedValueBuf[index]= ccpCapturedVal;
                    ccpCapturedVal=0;
                    index++;
                    if (index>=DATA_BIT_COUNT)//check if all the 32 bits have been received
                    {
                        appState = DECODE_CMD; // decode command from 32 bit data received
                    }
                }
                else
                {
                    //error in data bit length
                    DisableCapture();
                    lcd_writeString(" Bit Time Error ", 0);
                    lcd_writeString("----------------", 1);
                    appState = INIT_FOR_NEXT_FRAME;
                }                
            }
            else if (TMR1_HasOverflowOccured())
            {
                //falling edge for next data bit is not received for 16.384 ms and timer 1 has overflowed
                Clear_TMR1_OVF();
                DisableCapture();
                lcd_writeString("DataBit Wait Err", 0);
                lcd_writeString("----------------", 1);
                appState = INIT_FOR_NEXT_FRAME;
            }            
            break;
        case DECODE_CMD:
            cmd_status=DecodeCmd();//decode command from 32 bit data received and check for the error
            
            if (cmd_status==DATA_BIT_ERR)
            {
                //error in data bits
                lcd_writeString(" Data Bit Error ", 0);
                lcd_writeString("----------------", 1);
                appState = INIT_FOR_NEXT_FRAME;
            }
            else if (cmd_status==RX_ADDR_ERR)
            {
                //Receiver address mismatch error
                lcd_writeString("RX Address Error", 0);
                lcd_writeString("----------------", 1);
                appState = INIT_FOR_NEXT_FRAME;
            }
            else if (cmd_status==RX_CMD_ERR)
            {
                //RX Command and inverse of command mismatch error
                lcd_writeString("RX Command Error", 0);
                lcd_writeString("----------------", 1);
                appState = INIT_FOR_NEXT_FRAME;
            }
            else
            {
                //command decoded successfully take corresponding control action
                appState = CONTROL_ACTION;
            }
        break;        
        case CONTROL_ACTION:
            rxCommand=Reverse(IR_data.command);//reverse the bits in the command byte as in NEC protocol LSb is transmitted first
            ControlAction(rxCommand);//take control action as per command received
            appState = INIT_FOR_NEXT_FRAME;
            break;
        case INIT_FOR_NEXT_FRAME:
            Init4nextFrame();//reset timer1, disable CCP, enable IOC for next frame reception
            appState = GET_EVENT;       
            break; 
        default:
            appState = GET_EVENT;
            break;
    }
}

/**
 * @Param
    none
 * @Returns
    1 if command received and decoded successfully
    2 if data bit is neither logic_0 nor logic_1
    3 if mismatch in the received address and inverse of received address
    4 if mismatch in the received command and inverse of received command
 * @Description
    Decode the command from received IR data
 * @Example
    DecodeCmd();
 */
static e_cmd_status DecodeCmd(void)
{
    e_cmd_status retVal=CMD_DECODED;
    uint8_t count=0;
    uint8_t rxAddr;
    
    for (count=0;count<DATA_BIT_COUNT;count++)
    {
        if((ccpCapturedValueBuf[count] < (LOGIC_0 + BIT_TIME_ERROR)) && (ccpCapturedValueBuf[count] > (LOGIC_0 - BIT_TIME_ERROR))) 
        {
            IR_data.data <<= 1;   //logic 0 is received   
        } 
        else if(ccpCapturedValueBuf[count] < (LOGIC_1 + BIT_TIME_ERROR) && ccpCapturedValueBuf[count] > (LOGIC_1 - BIT_TIME_ERROR)) 
        {
            IR_data.data <<= 1;
            IR_data.data |= 1; //logic 1 is received 
        } 
        else 
        {
            //error in data bits reception,
            retVal= DATA_BIT_ERR;
        }
    }  
    //Check if the IR data received is as per NEC protocol
    //32 bit IR data bits: address byte, complement of address byte, command byte, complement of command byte    
    rxAddr=Reverse((uint8_t)IR_data.address);
    if(((uint8_t)IR_data.address != (uint8_t)~IR_data.nAddress) ||( rxAddr != IR_RX_ADDRESS) )
    {
        retVal= RX_ADDR_ERR;//Error: if mismatch in RX address and complement of RX address or the receiver address is different
    }
    
    if((uint8_t)IR_data.command != (uint8_t)~IR_data.nCommand)
    {
        retVal= RX_CMD_ERR;//Error: if mismatch in RX Command and complement of RX Command 
    }
    
    return retVal;
}

/**
 * @Param
    command byte
 * @Returns
    none
 * @Description
    Take corresponding control action after receiving the command
 *  command #81 make brightness of LED  25%
    command #82 make brightness of LED  50%
    command #83 make brightness of LED  75%
    command #84 make brightness of LED  100%
    command #85 make brightness of LED  75%
    command #86 make brightness of LED  50%
    command #87 make brightness of LED  25%
    command #88 make brightness of LED  0%
 * @Example
    ControlAction(cmd);
 */
static void ControlAction(uint8_t cmd)
{
    char displayString1[17];
    uint8_t dutyCycleValIndex = 0;
    uint8_t duty = 0;

    dutyCycleValIndex = cmd & LOWER_NIBBLE;//mask higher nibble to get array index value from cmd
    duty = dutyCycleValArr[dutyCycleValIndex - 1];//update PWM duty with corresponding fixed value from array
    
    if (dutyCycleValIndex < (MAX_CMD_NO + 1))
    {
        if (cmd & UPPER_NIBBLE)//cmd which has 0x8X meant for led D2
        {
            PWM3_LoadDutyValue(duty * 10);// Set brightness of LED D2 according to command received
        }      
        //Display the received command on LCD
        sprintf(displayString1, "Cmd Received =%2x", (cmd));
        lcd_writeString(displayString1, 0);
        sprintf(displayString1, "DIM LED  : %3d %%" ,duty);
        lcd_writeString(displayString1, 1);
    }
    else
    {
        //The command is out of range. It is not implemented
        lcd_writeString("Received Command", 0);
        lcd_writeString("Not Implemented!", 1);
    }

}

/**
 * @Param
    1 byte value
 * @Returns
    reverse of the byte with LSb as MSb
 * @Description
    In NEC protocol LSb is transmitted first. 
    This function is used to reverse the bits in the data byte and decode the byte received with msb first.
 * @Example
    Reverse();
 */
static uint8_t Reverse(uint8_t byteVar) 
{
   byteVar = (byteVar & UPPER_NIBBLE) >> 4 | (byteVar & LOWER_NIBBLE) << 4;
   byteVar = (byteVar & BIT7632) >> 2 | (byteVar & BIT5410) << 2;
   byteVar = (byteVar & BIT7531) >> 1 | (byteVar & BIT6420) << 1;
   return byteVar;
}

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Write initial text on LCD display
 * @Example
    Init_display();
 */
void Init_display(void)
{
    lcd_setContrast(0x20);
    lcd_writeString(" Waiting for CMD", 0);
    lcd_writeString(" Waiting for CMD", 0);
    lcd_writeString("----------------", 1);
}

/**
 * @Param
    none
 * @Returns
    true if start of frame detected
 * @Description
    Check if Start of frame is detected properly as per NEC protocol
 * @Example
    start=check4Start();
 */
static bool check4Start(void)
{
    if((ccpCapturedVal < START_TIME_MAX) && (ccpCapturedVal > START_TIME_MIN)) 
    {        
        ccpCapturedVal=0;
        index=0;
        return true;
    }
    else
    {
        return false;
    }    
}

/**
 * @Param
    None
 * @Returns
    Status of any falling edge event (interrupt on change on RA1
 * @Description
    This function is used to get information whether there is any event for generating command.
 * @Example
    event_status =GetEvent();
 */
static bool GetEvent(void)
{
    if (fallingEdgeDetected)
    {
        fallingEdgeDetected=false;
        return true;
    }
    else 
    {
        return false;
    }
}

/**
 * @Param
    None
 * @Returns
    None
 * @Description
    This function is used to initialize the peripherals for next data frame reception.
 * @Example
    Init4nextFrame();
 */
static void Init4nextFrame(void)
{
    DisableCapture();
    EnableFrameDet();//Turn on timer 2 ON bit, to start the timer when the first falling edge of next frame is detected,
   
}
/**
 * @Param
    None
 * @Returns
    None
 * @Description
    This function is used to disable CCP module
 * @Example
    DisableCapture();
 */
static void DisableCapture(void)
{  
    TMR1_StopTimer();
    TMR1_WriteTimer(ZERO);  
    Clear_TMR1_OVF();
    DisableCCP();
    DisableCCP_Interrupt(); 
    ccpCapturedVal=0;
    index=0;
}
 
/**
 * @Param
    None
 * @Returns
    None
 * @Description
  Timer interrupt handler function , 
 
 */
void TMR2_UserInterruptHandler(void)
{
     //timer interrupt  handler function
     if (!RA1_GetValue())//check if RA1 is still low after 1mS of falling edge on RA1
    {
        TMR2_Stop();//Turn Off the ON bit of Timer. It will be turned on after detecting the whole IR frame for next frame detection
        fallingEdgeDetected=true;// set the flag as the falling edge on RA1 is not due to noise
    }
}

/**
 * @Param
    None
 * @Returns
    None
 * @Description
 CCP1 interrupt handler function ,
 */
void CCP1_UserInterruptHandler(void)
{
    TMR1_WriteTimer(ZERO);
       
    ccpCapturedVal = CCPR1;
    ccpCapturedFlag=true;
}