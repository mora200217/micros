/*
 * File:   learn.c
 * Author: amoralesma
 *
 * Created on June 16, 2025, 11:34 PM
 */


#include <xc.h>

#pragma config FOSC = INTOSC_EC 
#pragma config LVP = OFF 
#pragma config WDT = OFF 

#define _XTAL_FREQ 1000000 // 1MHz 

void main(void) {
    TRISD = 0; 
    while(1){
        LATDbits.LATD0 = 0; 
        _delay_ms(1000); 
        LATDbits.LATD0 = 1; 
        _delay_ms(1000); 
    
    }
    
    
    return;
}
