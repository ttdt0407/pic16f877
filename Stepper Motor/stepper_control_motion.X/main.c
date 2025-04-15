/*
 * File:   main.c
 * Author: ADIMIN
 *
 * Created on March 3, 2025, 8:28 PM
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000

void main(void) {
    
    TRISCbits.TRISC0 = 1;
    TRISCbits.TRISC1 = 1;
    
    TRISB = 0x00;
    PORTB = 0x00;
    
    unsigned char index = 0;
    unsigned char flag = 2;
    
    while (PORTCbits.RC0 || flag == 1)
    {
        flag = 1;
        
        PORTB = (1<< index);
        index++;
        __delay_ms(50);
        if (index == 4)
            index = 0;
        if (PORTCbits.RC1)
        {
            flag = 0;
            break;
        }
    }
    
     while (PORTCbits.RC1 || flag == 0)
    {
        PORTB = (8 >> index);
        index++;
        __delay_ms(50);
        if (index == 4)
            index = 0;
        if (PORTCbits.RC0)
        {
            flag = 1;
            break;
        }
    }
        
        
     

    
    return;
}
