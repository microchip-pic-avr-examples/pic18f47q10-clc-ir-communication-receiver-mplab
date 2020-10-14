#ifndef APPLICATION_H
#define	APPLICATION_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "mcc_generated_files/mcc.h"
 
#define START_TIME      0xD2F0U//timer 1/CCP count for 13.5mS
#define START_TIME_MIN  0xB000U //timer 1/CCP count for 11.256mS
#define START_TIME_MAX  0xDF00U//timer 1/CCP count for 14.272mS
#define BIT_TIME_ERROR  0x0300U//timer 1/CCP count for 192 us
#define LOGIC_0         0x1194U//timer 1/CCP count for 1.125mS
#define LOGIC_1         0x2328U//timer 1/CCP count for 2.25mS    
#define BIT_TIME_MAX    0x2600U//timer 1/CCP count for 4.432mS   
   
#define ZERO            (uint8_t)0    

#define MAX_CMD_NO      (uint8_t)8
#define LED_D5          (uint8_t)1
#define LED_D2          (uint8_t)2 

//used in reversing the bits from MSb to LSb 
#define UPPER_NIBBLE    (uint8_t)0xF0
#define LOWER_NIBBLE    (uint8_t)0x0F
#define BIT7632         (uint8_t)0xCC
#define BIT5410         (uint8_t)0x33
#define BIT7531         (uint8_t)0xAA
#define BIT6420         (uint8_t)0x55 

//number of data bits in the command received as per NEC IR protocol    
#define DATA_BIT_COUNT  (uint8_t)32

//IR receiver Address
#define IR_RX_ADDRESS   (uint8_t)0xAA
    
typedef union {
    uint32_t data;
    struct {
        uint8_t nCommand;
        uint8_t command;
        uint8_t nAddress;
        uint8_t address;
    };
}IR_DATA;

//Application task states
typedef enum  {
    GET_EVENT,
    DETECT_START,
    CAPTURE_DATA_BITS,
    DECODE_CMD,
    CONTROL_ACTION,
    INIT_FOR_NEXT_FRAME        
}e_app_states;

typedef enum {
    CMD_DECODED,
    DATA_BIT_ERR,       
    RX_ADDR_ERR,
    RX_CMD_ERR    
}e_cmd_status;


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
void ApplicationTask(void);

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
void Init_display(void);

/**
   @Param
    none
   @Returns
   none
   @Description
     Timer interrupt handler function , 
 */
void TMR2_UserInterruptHandler(void);

/**
   @Param
    none
   @Returns
   none
   @Description
    CCP1 interrupt handler function , 
 */
void CCP1_UserInterruptHandler(void);

#ifdef	__cplusplus
}
#endif

#endif	/* APPLICATION_H */

