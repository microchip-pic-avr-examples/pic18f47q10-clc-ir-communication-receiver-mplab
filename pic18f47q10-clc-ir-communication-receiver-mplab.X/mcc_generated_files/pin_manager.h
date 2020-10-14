/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.4
        Device            :  PIC18F47Q10
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.20 and above
        MPLAB 	          :  MPLAB X 5.40	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA1 procedures
#define RA1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define RA1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define RA1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define RA1_GetValue()              PORTAbits.RA1
#define RA1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define RA1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define RA1_SetPullup()             do { WPUAbits.WPUA1 = 1; } while(0)
#define RA1_ResetPullup()           do { WPUAbits.WPUA1 = 0; } while(0)
#define RA1_SetAnalogMode()         do { ANSELAbits.ANSELA1 = 1; } while(0)
#define RA1_SetDigitalMode()        do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set LCDMini_nCS2 aliases
#define LCDMini_nCS2_TRIS                 TRISAbits.TRISA2
#define LCDMini_nCS2_LAT                  LATAbits.LATA2
#define LCDMini_nCS2_PORT                 PORTAbits.RA2
#define LCDMini_nCS2_WPU                  WPUAbits.WPUA2
#define LCDMini_nCS2_OD                   ODCONAbits.ODCA2
#define LCDMini_nCS2_ANS                  ANSELAbits.ANSELA2
#define LCDMini_nCS2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LCDMini_nCS2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LCDMini_nCS2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define LCDMini_nCS2_GetValue()           PORTAbits.RA2
#define LCDMini_nCS2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LCDMini_nCS2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define LCDMini_nCS2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define LCDMini_nCS2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define LCDMini_nCS2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define LCDMini_nCS2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define LCDMini_nCS2_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define LCDMini_nCS2_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set RA3 procedures
#define RA3_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define RA3_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define RA3_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define RA3_GetValue()              PORTAbits.RA3
#define RA3_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define RA3_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define RA3_SetPullup()             do { WPUAbits.WPUA3 = 1; } while(0)
#define RA3_ResetPullup()           do { WPUAbits.WPUA3 = 0; } while(0)
#define RA3_SetAnalogMode()         do { ANSELAbits.ANSELA3 = 1; } while(0)
#define RA3_SetDigitalMode()        do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set RC0 procedures
#define RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define RC0_GetValue()              PORTCbits.RC0
#define RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define RC0_SetPullup()             do { WPUCbits.WPUC0 = 1; } while(0)
#define RC0_ResetPullup()           do { WPUCbits.WPUC0 = 0; } while(0)
#define RC0_SetAnalogMode()         do { ANSELCbits.ANSELC0 = 1; } while(0)
#define RC0_SetDigitalMode()        do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set LCD_BL aliases
#define LCD_BL_TRIS                 TRISCbits.TRISC2
#define LCD_BL_LAT                  LATCbits.LATC2
#define LCD_BL_PORT                 PORTCbits.RC2
#define LCD_BL_WPU                  WPUCbits.WPUC2
#define LCD_BL_OD                   ODCONCbits.ODCC2
#define LCD_BL_ANS                  ANSELCbits.ANSELC2
#define LCD_BL_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define LCD_BL_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define LCD_BL_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define LCD_BL_GetValue()           PORTCbits.RC2
#define LCD_BL_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define LCD_BL_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define LCD_BL_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define LCD_BL_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define LCD_BL_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define LCD_BL_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define LCD_BL_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define LCD_BL_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSELC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSELC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSELC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RD1 procedures
#define RD1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define RD1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define RD1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define RD1_GetValue()              PORTDbits.RD1
#define RD1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define RD1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define RD1_SetPullup()             do { WPUDbits.WPUD1 = 1; } while(0)
#define RD1_ResetPullup()           do { WPUDbits.WPUD1 = 0; } while(0)
#define RD1_SetAnalogMode()         do { ANSELDbits.ANSELD1 = 1; } while(0)
#define RD1_SetDigitalMode()        do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set LCDMini_nReset aliases
#define LCDMini_nReset_TRIS                 TRISDbits.TRISD5
#define LCDMini_nReset_LAT                  LATDbits.LATD5
#define LCDMini_nReset_PORT                 PORTDbits.RD5
#define LCDMini_nReset_WPU                  WPUDbits.WPUD5
#define LCDMini_nReset_OD                   ODCONDbits.ODCD5
#define LCDMini_nReset_ANS                  ANSELDbits.ANSELD5
#define LCDMini_nReset_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define LCDMini_nReset_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define LCDMini_nReset_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define LCDMini_nReset_GetValue()           PORTDbits.RD5
#define LCDMini_nReset_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define LCDMini_nReset_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define LCDMini_nReset_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define LCDMini_nReset_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define LCDMini_nReset_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define LCDMini_nReset_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define LCDMini_nReset_SetAnalogMode()      do { ANSELDbits.ANSELD5 = 1; } while(0)
#define LCDMini_nReset_SetDigitalMode()     do { ANSELDbits.ANSELD5 = 0; } while(0)

// get/set LCDMini_nCS aliases
#define LCDMini_nCS_TRIS                 TRISDbits.TRISD7
#define LCDMini_nCS_LAT                  LATDbits.LATD7
#define LCDMini_nCS_PORT                 PORTDbits.RD7
#define LCDMini_nCS_WPU                  WPUDbits.WPUD7
#define LCDMini_nCS_OD                   ODCONDbits.ODCD7
#define LCDMini_nCS_ANS                  ANSELDbits.ANSELD7
#define LCDMini_nCS_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define LCDMini_nCS_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define LCDMini_nCS_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define LCDMini_nCS_GetValue()           PORTDbits.RD7
#define LCDMini_nCS_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define LCDMini_nCS_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define LCDMini_nCS_SetPullup()          do { WPUDbits.WPUD7 = 1; } while(0)
#define LCDMini_nCS_ResetPullup()        do { WPUDbits.WPUD7 = 0; } while(0)
#define LCDMini_nCS_SetPushPull()        do { ODCONDbits.ODCD7 = 0; } while(0)
#define LCDMini_nCS_SetOpenDrain()       do { ODCONDbits.ODCD7 = 1; } while(0)
#define LCDMini_nCS_SetAnalogMode()      do { ANSELDbits.ANSELD7 = 1; } while(0)
#define LCDMini_nCS_SetDigitalMode()     do { ANSELDbits.ANSELD7 = 0; } while(0)

// get/set LED aliases
#define LED_TRIS                 TRISEbits.TRISE0
#define LED_LAT                  LATEbits.LATE0
#define LED_PORT                 PORTEbits.RE0
#define LED_WPU                  WPUEbits.WPUE0
#define LED_OD                   ODCONEbits.ODCE0
#define LED_ANS                  ANSELEbits.ANSELE0
#define LED_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define LED_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define LED_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define LED_GetValue()           PORTEbits.RE0
#define LED_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define LED_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define LED_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define LED_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define LED_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define LED_SetAnalogMode()      do { ANSELEbits.ANSELE0 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELEbits.ANSELE0 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/