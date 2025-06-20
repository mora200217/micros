/*
 * File:   main.c
 * Author: amoralesma
 *
 * Created on June 15, 2025, 12:20 PM
 */


#include <xc.h>
#include "led_changer.h"

#pragma config FOSC = EC_EC
#pragma config WDT = OFF 
#pragma config LVP = OFF 


#define _XTAL_FREQ 1000000 // 1MHz
extern void my_rutine(void); 

void main(void) {
      my_rutine(); // Loop 
    
    /* LED_init(); 
    
    while(1){
        LED_change(); 
        // __delay_ms(2000); 
    }*/ 
    return;
}
