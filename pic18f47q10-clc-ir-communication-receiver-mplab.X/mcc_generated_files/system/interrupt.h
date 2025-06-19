/**
 * Interrupt Manager Generated Driver API Header File
 * 
 * @file interrupt.h
 * 
 * @defgroup interrupt INTERRUPT
 * 
 * @brief This file contains API prototypes and other data types for the Interrupt Manager driver.
 *
 * @version Interrupt Manager Driver Version 2.0.6
*/

/*
� [2025] Microchip Technology Inc. and its subsidiaries.

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

#ifndef INTERRUPT_H
#define INTERRUPT_H


/**
 * @ingroup interrupt
 * @brief Enables global interrupts.
 * @param None.
 * @return None.
 */
#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)

/**
 * @ingroup interrupt
 * @brief Disables global interrupts.
 * @param None.
 * @return None.
 */
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)

/**
 * @ingroup interrupt
 * @brief Returns the Global Interrupt Enable bit status.
 * @param None.
 * @retval 0 - Global interrupt disabled.
 * @retval 1 - Global interrupt enabled.
 */
#define INTERRUPT_GlobalInterruptStatus() (INTCONbits.GIE)

/**
 * @ingroup interrupt
 * @brief Enables peripheral interrupts.
 * @param None.
 * @return None.
 */
#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)

/**
 * @ingroup interrupt
 * @brief Disables peripheral interrupts.
 * @param None.
 * @return None.
 */
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)

/**
 * @ingroup interrupt
 * @brief Initializes peripheral interrupt priorities, enables or disables priority vectors and initializes the external interrupt.
 * @param None.
 * @return None.
 */
void INTERRUPT_Initialize (void);


/**
 * @ingroup interrupt
 * @brief Clears the Interrupt flag for the external interrupt, INT0.
 * @param None.
 * @return None.
 */
#define EXT_INT0_InterruptFlagClear()       (PIR0bits.INT0IF = 0)

/**
 * @ingroup interrupt
 * @brief Clears the interrupt enable for the external interrupt, INT0. This way, the external interrupts on this pin will not be serviced by the interrupt handler.
 * @param None.
 * @return None.
 */
#define EXT_INT0_InterruptDisable()     (PIE0bits.INT0IE = 0)

/**
 * @ingroup interrupt
 * @brief Sets the interrupt enable for the external interrupt, INT0. This way, the external interrupts on this pin will be serviced by the interrupt handler.
 * @param None.
 * @return None.
 */
#define EXT_INT0_InterruptEnable()       (PIE0bits.INT0IE = 1)

/**
 * @ingroup interrupt
 * @brief Sets the edge detect of the external interrupt to positive edge. This way, the Interrupt flag will be set when the external interrupt pin level transitions from low to high.
 * @param None.
 * @return None.
 */
#define EXT_INT0_risingEdgeSet()          (INTCONbits.INT0EDG = 1)

/**
 * @ingroup interrupt
 * @brief Sets the edge detect of the external interrupt to negative edge. This way, the Interrupt flag will be set when the external interrupt pin level transitions from high to low.
 * @param None.
 * @return None.
 */
#define EXT_INT0_fallingEdgeSet()          (INTCONbits.INT0EDG = 0)

/**
 * @ingroup interrupt
 * @brief Clears the Interrupt flag for the external interrupt, INT1.
 * @param None.
 * @return None.
 */
#define EXT_INT1_InterruptFlagClear()       (PIR0bits.INT1IF = 0)

/**
 * @ingroup interrupt
 * @brief Clears the interrupt enable for the external interrupt, INT1. This way, the external interrupts on this pin will not be serviced by the interrupt handler.
 * @param None.
 * @return None.
 */
#define EXT_INT1_InterruptDisable()     (PIE0bits.INT1IE = 0)

/**
 * @ingroup interrupt
 * @brief Sets the interrupt enable for the external interrupt, INT1. This way, the external interrupts on this pin will be serviced by the interrupt handler.
 * @param None.
 * @return None.
 */
#define EXT_INT1_InterruptEnable()       (PIE0bits.INT1IE = 1)

/**
 * @ingroup interrupt
 * @brief Sets the edge detect of the external interrupt to positive edge. This way, the Interrupt flag will be set when the external interrupt pin level transitions from low to high.
 * @param None.
 * @return None.
 */
#define EXT_INT1_risingEdgeSet()          (INTCONbits.INT1EDG = 1)

/**
 * @ingroup interrupt
 * @brief Sets the edge detect of the external interrupt to negative edge. This way, the Interrupt flag will be set when the external interrupt pin level transitions from high to low.
 * @param None.
 * @return None.
 */
#define EXT_INT1_fallingEdgeSet()          (INTCONbits.INT1EDG = 0)

/**
 * @ingroup interrupt
 * @brief Clears the Interrupt flag for the external interrupt, INT2.
 * @param None.
 * @return None.
 */
#define EXT_INT2_InterruptFlagClear()       (PIR0bits.INT2IF = 0)

/**
 * @ingroup interrupt
 * @brief Clears the interrupt enable for the external interrupt, INT2. This way, the external interrupts on this pin will not be serviced by the interrupt handler.
 * @param None.
 * @return None.
 */
#define EXT_INT2_InterruptDisable()     (PIE0bits.INT2IE = 0)

/**
 * @ingroup interrupt
 * @brief Sets the interrupt enable for the external interrupt, INT2. This way, the external interrupts on this pin will be serviced by the interrupt handler.
 * @param None.
 * @return None.
 */
#define EXT_INT2_InterruptEnable()       (PIE0bits.INT2IE = 1)

/**
 * @ingroup interrupt
 * @brief Sets the edge detect of the external interrupt to positive edge. This way, the Interrupt flag will be set when the external interrupt pin level transitions from low to high.
 * @param None.
 * @return None.
 */
#define EXT_INT2_risingEdgeSet()          (INTCONbits.INT2EDG = 1)

/**
 * @ingroup interrupt
 * @brief Sets the edge detect of the external interrupt to negative edge. This way, the Interrupt flag will be set when the external interrupt pin level transitions from high to low.
 * @param None.
 * @return None.
 */
#define EXT_INT2_fallingEdgeSet()          (INTCONbits.INT2EDG = 0)

/**
   Section: External Interrupt Handlers
 */

/**
 * @ingroup interrupt
 * @brief Executes the ISR whenever the signal on the INT0 pin transitions to the preconfigured state.
 * @pre Interrupt Manager is initialized.
 * @param None.
 * @return None.
 */
void INT0_ISR(void);

/**
 * @ingroup interrupt
 * @brief Allows for a specific callback function to be called in the INT0 ISR and for a nonspecific interrupt handler to be called at run time.
 * @pre Interrupt Manager is initialized.
 * @param None.
 * @return None.
 */
void INT0_CallBack(void);

/**
 * @ingroup interrupt
 * @brief Allows selecting an interrupt handler for EXT_INT0 - INT0 at application run time.
 * @pre Interrupt Manager is initialized.
 * @param (*InterruptHandler)(void) - InterruptHandler function pointer.
 * @return None.
 */
void INT0_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup interrupt
 * @brief Dynamic interrupt handler to be called every time the INT0 ISR is executed. It allows any function to be registered at run time.
 * @pre Interrupt Manager is initialized.
 * @param None.
 * @return None.
 */
extern void (*INT0_InterruptHandler)(void);

/**
 * @ingroup interrupt
 * @brief Default interrupt handler to be called every time the INT0 ISR is executed. It allows any function to be registered at run time.
 * @pre Interrupt Manager is initialized.
 * @param None.
 * @return None.
 */
void INT0_DefaultInterruptHandler(void);

/**
 * @ingroup interrupt
 * @brief Executes the ISR whenever the signal on the INT1 pin transitions to the preconfigured state.
 * @pre Interrupt Manager is initialized.
 * @param None.
 * @return None.
 */
void INT1_ISR(void);

/**
 * @ingroup interrupt
 * @brief Allows for a specific callback function to be called in the INT1 ISR and for a nonspecific interrupt handler to be called at run time.
 * @pre Interrupt Manager is initialized.
 * @param None.
 * @return None.
 */
void INT1_CallBack(void);

/**
 * @ingroup interrupt
 * @brief Allows selecting an interrupt handler for EXT_INT1 - INT1 at application run time.
 * @pre Interrupt Manager is initialized.
 * @param (*InterruptHandler)(void) - InterruptHandler function pointer.
 * @return None.
 */
void INT1_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup interrupt
 * @brief Dynamic interrupt handler to be called every time the INT1 ISR is executed. It allows any function to be registered at run time.
 * @pre Interrupt Manager is initialized.
 * @param None.
 * @return None.
 */
extern void (*INT1_InterruptHandler)(void);

/**
 * @ingroup interrupt
 * @brief Default interrupt handler to be called every time the INT1 ISR is executed. It allows any function to be registered at run time.
 * @pre Interrupt Manager is initialized.
 * @param None.
 * @return None.
 */
void INT1_DefaultInterruptHandler(void);

/**
 * @ingroup interrupt
 * @brief Executes the ISR whenever the signal on the INT2 pin transitions to the preconfigured state.
 * @pre Interrupt Manager is initialized.
 * @param None.
 * @return None.
 */
void INT2_ISR(void);

/**
 * @ingroup interrupt
 * @brief Allows for a specific callback function to be called in the INT2 ISR and for a nonspecific interrupt handler to be called at run time.
 * @pre Interrupt Manager is initialized.
 * @param None.
 * @return None.
 */
void INT2_CallBack(void);

/**
 * @ingroup interrupt
 * @brief Allows selecting an interrupt handler for EXT_INT2 - INT2 at application run time.
 * @pre Interrupt Manager is initialized.
 * @param (*InterruptHandler)(void) - InterruptHandler function pointer.
 * @return None.
 */
void INT2_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup interrupt
 * @brief Dynamic interrupt handler to be called every time the INT2 ISR is executed. It allows any function to be registered at run time.
 * @pre Interrupt Manager is initialized.
 * @param None.
 * @return None.
 */
extern void (*INT2_InterruptHandler)(void);

/**
 * @ingroup interrupt
 * @brief Default interrupt handler to be called every time the INT2 ISR is executed. It allows any function to be registered at run time.
 * @pre Interrupt Manager is initialized.
 * @param None.
 * @return None.
 */
void INT2_DefaultInterruptHandler(void);

#endif  // INTERRUPT_H
/**
 End of File
*/