 /*
     (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

#include <stdbool.h>
#include "expander.h"
#include "digipot.h"
#include "../delay.h"
#include "../pin_manager.h"

void lcd_sendNibble(uint8_t nibble, bool RSbit){
    uint8_t packet = (nibble << 4) | (RSbit << 2);
    expander_setOutput(packet);
    expander_setOutput(packet | (1<<3));
    DELAY_milliseconds(1);
    expander_setOutput(packet);
    DELAY_milliseconds(40);
}

void lcd_sendByte(uint8_t byte, bool RSbit){
    uint8_t nibbleHigh = byte >> 4;
    uint8_t nibbleLow = byte & 0xF;
    uint8_t packetHigh = (nibbleHigh << 4) | (RSbit << 2);
    uint8_t packetLow = (nibbleLow << 4) | (RSbit << 2);
    
    expander_setOutput(packetHigh);
    DELAY_milliseconds(2);
    expander_setOutput(packetHigh | (1<<3));
    DELAY_milliseconds(2);
    expander_setOutput(packetLow);
    DELAY_milliseconds(2);
    expander_setOutput(packetLow | (1<<3));
    DELAY_milliseconds(40);
}

void lcd_returnHome(void){
    lcd_sendByte(0b10, false);
    DELAY_milliseconds(2);
}

void lcd_clearDisplay(void){
    lcd_sendByte(0b1, false);
    DELAY_milliseconds(2);
}

void lcd_setAddr(uint8_t row, uint8_t character){
    lcd_sendByte(0x80 | (character + (row*40)), false);
}

void lcd_writeChar(uint8_t character){
    lcd_sendByte(character, true);
}

void lcd_writeString(uint8_t* string, uint8_t row) {
    lcd_setAddr(row, 0);
    uint8_t i = 0;
    for (i = 0; i < 16; i++) {
        if (string[i]) {
            lcd_writeChar(string[i]);
        }
    }
    lcd_returnHome();
}

void lcd_setContrast(uint8_t contrast){
    digipot_setWiper(contrast);
}

void lcd_setup(){
    LATDbits.LATD7 = 1; /* set LCDMini_nCS output high */
    LATAbits.LATA2 = 1; /* set LCDMini_nCS2 output high */
    LATDbits.LATD5 = 1; /* set LCDMini_nReset output high */
    expander_setup();
    expander_setOutput(0);
    DELAY_milliseconds(40);
    lcd_sendNibble(0b11, false);
    DELAY_milliseconds(10);

    lcd_sendNibble(0b11, false);
    DELAY_milliseconds(10);
    lcd_sendNibble(0b11, false);
    DELAY_milliseconds(10);
    lcd_sendNibble(0x2,false);
    lcd_sendByte(0x2C, false);
    lcd_sendByte(0b1100, false);
    lcd_sendByte(0x06, false);
    lcd_sendByte(0x0C, false);
    DELAY_milliseconds(2);
    lcd_returnHome();
    lcd_clearDisplay();
}
