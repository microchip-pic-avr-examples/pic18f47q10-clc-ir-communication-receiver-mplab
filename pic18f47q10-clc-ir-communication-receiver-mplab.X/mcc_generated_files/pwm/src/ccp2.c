/**
 * PWM2 Generated Driver File.
 * 
 * @file ccp2.c
 * 
 * @ingroup pwm2
 * 
 * @brief This file contains the API implementations for the PWM2 driver.
 *
 * @version PWM2 Driver Version 2.0.3
*/
/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

 /**
   Section: Included Files
 */

#include <xc.h>
#include "../ccp2.h"

/**
  Section: Macro Declarations
*/

/* cppcheck-suppress misra-c2012-2.5 */
#define PWM2_INITIALIZE_DUTY_VALUE    0

/**
  Section: PWM2 Module APIs
*/

void CCP2_Initialize(void)
{
    // Set the PWM2 to the options selected in the User Interface
    
    // CCPM PWM; EN enabled; FMT right_aligned; 
    CCP2CON = 0x8C;
    
    // CCPRH 0; 
    CCPR2H = 0x0;
    
    // CCPRL 0; 
    CCPR2L = 0x0;
    
    // Selecting Timer 4
    CCPTMRSbits.C2TSEL = 0x2;
}

void CCP2_LoadDutyValue(uint16_t dutycycleValue)
{
    uint16_t dutyValue = dutycycleValue;
	  dutyValue &= 0x03FF;
    
    // Load duty cycle value
    if(1U == CCP2CONbits.FMT)
    {
        dutyValue <<= 6U;
        CCPR2H = (uint8_t)(dutyValue >> 8);
        CCPR2L = (uint8_t)dutyValue;
    }
    else
    {
        CCPR2H = (uint8_t)(dutyValue >> 8);
        CCPR2L = (uint8_t)dutyValue;
    }
}
bool CCP2_OutputStatusGet(void)
{
    // Returns the output status
    return(CCP2CONbits.OUT);
}
/**
 End of File
*/
