/*
 * File:   main.c
 * Author: ADIMIN
 *
 * Created on March 3, 2025, 1:35 PM
 */
#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000

void main(void) {
    
    int count = 0;
    TRISB = 0x00;
    PORTB = 0x00;
    
    unsigned char seven_segments[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 
    0xBE, 0xE0, 0xFE, 0xF6};

    
    while(1)
    {
        PORTB = seven_segments[count];
        count++;
        if (count == 10)
            count = 0;
        __delay_ms(1000);
    }
    return;
}
