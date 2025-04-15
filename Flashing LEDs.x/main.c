/*
 * File:   main.c
 * Author: ADIMIN
 *
 * Created on March 1, 2025, 1:31 PM
 */

#include "config.h"
#include <xc.h>
#include <pic16f877a.h>
#define _XTAL_FREQ 4000000
void main(void) {
    
    TRISB0 = 0;
    TRISB1 = 0;
    TRISB2 = 0;
    
    while(1)
    {
        RB0 = 1;
        __delay_ms(50);
        RB0 = 0;
        __delay_ms(50);
        
        RB1 = 1; 
        __delay_ms(50);
        RB1 = 0;
        __delay_ms(50);
        
        RB2 = 1;
        __delay_ms(50);
        RB2 = 0;
        __delay_ms(50);
        
    }
    
    return;
}
