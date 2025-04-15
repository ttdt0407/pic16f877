/*
 * File:   main.c
 * Author: PC
 *
 * Created on March 23, 2025, 6:54 PM
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000

void main(void) {
    
    // Configure the IO pins  
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    
    // Set interrupt when there's a raising edge
    OPTION_REGbits.INTEDG = 1;
    
    // Enable IRQ
    INTCONbits.INTE = 1;
    INTCONbits.GIE = 1;
    
    while(1)
    {
        PORTCbits.RC2 = 1;
        __delay_ms(1000);
        PORTCbits.RC2 = 0;
        __delay_ms(1000);
    }
    
    
    
    
    return;
}

void __interrupt() ISR(void)
{
    if (INTCONbits.INTF)
    {
        PORTCbits.RC1 = ~PORTCbits.RC1;
        INTCONbits.INTF = 0;
    }
    
}