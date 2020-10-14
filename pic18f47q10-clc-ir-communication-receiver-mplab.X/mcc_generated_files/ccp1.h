/**
  CCP1 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    ccp1.h

  @Summary
    This is the generated header file for the CCP1 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for CCP1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.4
        Device            :  PIC18F47Q10
        Driver Version    :  2.1.3
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

#ifndef CCP1_H
#define CCP1_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/** 
   Section: Data Type Definition
*/

/**
 @Summary
   Defines the values to convert from 16bit to two 8 bit and vice versa

 @Description
   This routine used to get two 8 bit values from 16bit also
   two 8 bit value are combine to get 16bit.

 Remarks:
   None
 */

typedef union CCPR1Reg_tag
{
   struct
   {
      uint8_t ccpr1l;
      uint8_t ccpr1h;
   };
   struct
   {
      uint16_t ccpr1_16Bit;
   };
} CCP1_PERIOD_REG_T ;

/**
  Section: Capture Module APIs
*/

/**
  @Summary
    Initializes the CCP1

  @Description
    This routine initializes the CCP1_Initialize.
    This routine must be called before any other CCP1 routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    

 @Example
    <code>
    CCP1_Initialize();
    </code>
 */
void CCP1_Initialize(void);

/**
  @Summary
    Implements ISR

  @Description
    This routine is used to implement the ISR for the interrupt-driven
    implementations.

  @Returns
    None

  @Param
    None
*/
void CCP1_CaptureISR(void);

/**
  @Summary
    Setter for CCP1 CallBack function

  @Description
    Calling this function will set a new custom call back function that will be 
    called from the Capture ISR.

  @Preconditions
    Initialize the CCP1 module with interrupt before calling this function.

  @Param
    A pointer to the new function

  @Returns
    None

  @Example
    <code>
    void Capture_CallBack(uint16_t capturedValue)
    {
        // Custom callback routine
    }
    
    void main(void)
    {
        // initialize the device
        SYSTEM_Initialize();
        
        // set the custom callback
        CCP1_SetCallBack(Capture_CallBack);
        
        while(1)
        {
            //Add your application code
        }
    }
    </code>
*/
 void CCP1_SetCallBack(void (*customCallBack)(uint16_t));


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  //CCP1_H
/**
 End of File
*/

