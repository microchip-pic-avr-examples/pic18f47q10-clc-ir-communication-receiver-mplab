#pragma warning disable 520,2053
/******************************************************************************/
/*                                                                            */
/*                               HEADER FILES                                 */
/*                                                                            */
/******************************************************************************/
#include "application.h"
#include <stdio.h>
#include "macros.h"
#include "mcc_generated_files/system/system.h"

/******************************************************************************/
/*                                                                            */
/*                           USER DEFINED VARIABLES                           */
/*                                                                            */
/******************************************************************************/
volatile bool fallingEdgeDetected=false;        // Flag is set when falling edge is detected on port RA1 connected to IR Click
volatile bool ccpCapturedFlag = false;          // Flag is set if CCP has captured Timer value on falling edge on RC0 (connected to RA1 with CLC as buffer)
volatile uint16_t ccpCapturedVal;               // Value of CCP capture
uint16_t ccpCapturedValueBuf[DATA_BIT_COUNT];   // Buffer for storing CCP capture values for 32 bit IR data
uint8_t index;
volatile IR_DATA IR_data;
const uint8_t dutyCycleValArr[MAX_CMD_NO] = {25, 50, 75, 100, 75, 50, 25, 0}; // Duty values for LED dimming when command is received

/******************************************************************************/
/*                                                                            */
/*                    USER DEFINED FUNCTION DECLARATIONS                      */
/*                                                                            */
/******************************************************************************/
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
static bool GetEvent(void);

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
static bool check4Start(void);

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
static void DisableCapture(void);

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
static void Init4nextFrame(void);

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
static e_cmd_status DecodeCmd(void);

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
static void ControlAction(uint8_t cmd);

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
static uint8_t Reverse(uint8_t byteVar);

/******************************************************************************/
/*                                                                            */
/*                    USER DEFINED FUNCTION DEFINITIONS                       */
/*                                                                            */
/******************************************************************************/
void ApplicationTask(void) 
{
    static e_app_states appState=GET_EVENT;
    e_cmd_status cmd_status;
    uint8_t rxCommand;
    
    switch(appState) 
    {
        case GET_EVENT:
            if(GetEvent())                                  // Check if falling edge is detected on the port pin connected to the IR photo diode 
            {   
                TMR1_CounterSet(0);                         // Valid falling edge is detected on the port pin, initialize capture
                TMR1_Start();                               // Enable timer 1, CCP1 and CCP falling edge interrupt for start of frame detection
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
                    appState = CAPTURE_DATA_BITS;           // Start of frame is detected now capture 32 bits of data from the IR frame
                }
                else
                {
                    DisableCapture();                       // Error in start of frame
                    lcd_writeString("  Start  Error  ", 0);
                    lcd_writeString("----------------", 1);
                    appState = INIT_FOR_NEXT_FRAME;  
                }    
            }
            else if (TMR1_HasOverflowOccured())
            {                
                Clear_TMR1_OVF();                           // Falling edge for start of frame is not received for 16.384 ms and timer 1 has overflowed
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

                if (ccpCapturedVal < BIT_TIME_MAX)          // Check for max bit length
                {
                    ccpCapturedValueBuf[index]= ccpCapturedVal;
                    ccpCapturedVal=0;
                    index++;
                    if (index>=DATA_BIT_COUNT)              // Check if all the 32 bits have been received
                    {
                        appState = DECODE_CMD;              // Decode command from 32 bit data received
                    }
                }
                else
                {                    
                    DisableCapture();                       // Error in data bit length
                    lcd_writeString(" Bit Time Error ", 0);
                    lcd_writeString("----------------", 1);
                    appState = INIT_FOR_NEXT_FRAME;
                }                
            }
            else if (TMR1_HasOverflowOccured())
            {                
                Clear_TMR1_OVF();                           // Falling edge for next data bit is not received for 16.384 ms and timer 1 has overflowed
                DisableCapture();
                lcd_writeString("DataBit Wait Err", 0);
                lcd_writeString("----------------", 1);
                appState = INIT_FOR_NEXT_FRAME;
            }            
            break;
            
        case DECODE_CMD:
            cmd_status=DecodeCmd();                         // Decode command from 32 bit data received and check for the error
            
            if (cmd_status==DATA_BIT_ERR)
            {                
                lcd_writeString(" Data Bit Error ", 0);     // Error in data bits
                lcd_writeString("----------------", 1);
                appState = INIT_FOR_NEXT_FRAME;
            }
            else if (cmd_status==RX_ADDR_ERR)
            {                
                lcd_writeString("RX Address Error", 0);     // RX address mismatch error
                lcd_writeString("----------------", 1);
                appState = INIT_FOR_NEXT_FRAME;
            }
            else if (cmd_status==RX_CMD_ERR)
            {                
                lcd_writeString("RX Command Error", 0);     // RX Command and inverse of command mismatch error
                lcd_writeString("----------------", 1);
                appState = INIT_FOR_NEXT_FRAME;
            }
            else
            {                
                appState = CONTROL_ACTION;                  // Command decoded successfully take corresponding control action
            }
        break;
        
        case CONTROL_ACTION:
            rxCommand=Reverse(IR_data.command);             // Reverse the bits in the command byte as in NEC protocol LSb is transmitted first
            ControlAction(rxCommand);                       // Take control action as per command received
            appState = INIT_FOR_NEXT_FRAME;
            break;
            
        case INIT_FOR_NEXT_FRAME:
            Init4nextFrame();                               // Reset timer1, disable CCP, enable IOC for next frame reception
            appState = GET_EVENT;       
            break; 
            
        default:
            appState = GET_EVENT;
            break;
    }
}

static e_cmd_status DecodeCmd(void)
{
    e_cmd_status retVal=CMD_DECODED;
    uint8_t count=0;
    uint8_t rxAddr;
    
    for (count=0;count<DATA_BIT_COUNT;count++)
    {
        if((ccpCapturedValueBuf[count] < (LOGIC_0 + BIT_TIME_ERROR)) && (ccpCapturedValueBuf[count] > (LOGIC_0 - BIT_TIME_ERROR))) 
        {
            IR_data.data <<= 1;             // Logic 0 is received   
        } 
        else if(ccpCapturedValueBuf[count] < (LOGIC_1 + BIT_TIME_ERROR) && ccpCapturedValueBuf[count] > (LOGIC_1 - BIT_TIME_ERROR)) 
        {
            IR_data.data <<= 1;
            IR_data.data |= 1;              // Logic 1 is received 
        } 
        else 
        {            
            retVal = DATA_BIT_ERR;          // Error in data bits reception,
        }
    }
    
    // Check if the IR data received is as per NEC protocol
    // 32 bit IR data bits: address byte, complement of address byte, command byte, complement of command byte    
    rxAddr = Reverse((uint8_t)IR_data.address);
    
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

static void ControlAction(uint8_t cmd)
{
    char displayString1[17];
    uint8_t dutyCycleValIndex = cmd & LOWER_NIBBLE; // Mask higher nibble to get array index value from cmd
    uint8_t duty = 0;
    
    duty = dutyCycleValArr[dutyCycleValIndex - 1];  // Update PWM duty with corresponding fixed value from array
    
    if (dutyCycleValIndex < (MAX_CMD_NO + 1))
    {
        if (cmd & UPPER_NIBBLE)                     // cmd which has 0x8X meant for led D2
        {
            PWM3_LoadDutyValue(duty * 10);          // Set brightness of LED D2 according to command received
        }        
        
        sprintf(displayString1, "CMD Received = %2x",(cmd)); // Display the received command on LCD
        lcd_writeString(displayString1, 0);
        sprintf(displayString1, "DIM LED  : %3d %%" ,duty);
        lcd_writeString(displayString1, 1);
    }
    else
    {        
        lcd_writeString("Received Command", 0);     // The command is out of range. It is not implemented
        lcd_writeString("Not Implemented!", 1);
    }
}

static uint8_t Reverse(uint8_t byteVar) 
{
   byteVar = (byteVar & UPPER_NIBBLE) >> 4 | (byteVar & LOWER_NIBBLE) << 4;
   byteVar = (byteVar & BIT7632) >> 2 | (byteVar & BIT5410) << 2;
   byteVar = (byteVar & BIT7531) >> 1 | (byteVar & BIT6420) << 1;
   return byteVar;
}

void Init_display(void)
{
    lcd_setContrast(0x20);
    lcd_writeString(" Waiting for CMD", 0);
    lcd_writeString(" Waiting for CMD", 1);
    lcd_writeString("----------------", 1);
}

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

static void Init4nextFrame(void)
{
    DisableCapture();
    EnableFrameDet();                       // Turn on timer 2 ON bit, to start the timer when the first falling edge of next frame is detected,
   
}

static void DisableCapture(void)
{  
    TMR1_Stop();
    TMR1_CounterSet(ZERO);  
    Clear_TMR1_OVF();
    DisableCCP();
    DisableCCP_Interrupt(); 
    ccpCapturedVal=0;
    index=0;
}
 
void TMR2_UserInterruptHandler(void)
{    
    if (!IO_RA1_GetValue())                 // Check if RA1 is still low after 1mS of falling edge on RA1
    {
        TMR2_Stop();                        // Turn Off the ON bit of Timer. It will be turned on after detecting the whole IR frame for next frame detection
        fallingEdgeDetected=true;           // Set the flag as the falling edge on RA1 is not due to noise
    }
}

void CCP1_UserInterruptHandler(uint16_t capturedValue)
{
    TMR1_CounterSet(ZERO);       
    ccpCapturedVal = CCPR1;
    ccpCapturedFlag=true;
}