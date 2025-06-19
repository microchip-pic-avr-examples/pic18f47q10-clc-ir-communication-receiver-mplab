/**
 * PWM2 Generated Driver API Header File.
 * 
 * @file ccp2.h
 * 
 * @defgroup pwm2 PWM2
 * 
 * @brief This file contains the API prototypes for the PWM2 module.
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

#ifndef PWM2_H
#define PWM2_H

 /**
   Section: Included Files
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>


 /**
 * @ingroup pwm2
 * @brief Initializes the CCP2 module. This is called only once before calling other CCP2 APIs.
 * @param None.
 * @return None.
 */
void CCP2_Initialize(void);
/**
 * @ingroup pwm2
 * @brief Loads the 16-bit duty cycle value.
 * @pre CCP2_Initialize() is already called.
 * @param dutyValue - 16-bit duty cycle value.
 * @return None.
 */
void CCP2_LoadDutyValue(uint16_t dutyValue);
/**
 * @ingroup pwm2
 * @brief Returns the PWM output status.
 * @pre CCP2_Initialize() is already called.
 * @param None.
 * @retval True - CCP2 PWM output is high
 * @retval False - CCP2 PWM output is low
 */
bool CCP2_OutputStatusGet(void);
#endif //PWM2_H
/**
 End of File
*/
