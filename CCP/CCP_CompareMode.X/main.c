/*
 * File:   main.c
 * Author: PC
 *
 * Created on March 31, 2025, 11:06 PM
 */

#include "config.h"
#include <stdint.h>
#include <xc.h>

uint8_t C = 0;
void GPIO_Init();
void TMR1_Init();
void Compare_Init();



void main(void) {
    GPIO_Init();
    TMR1_Init();
    Compare_Init();
    while (1)
    {
        
    }
    
    return;
}

void __interrupt() ISR(void)
{
    if(PIR1bits.CCP1IF)
    {
        C++;
        if (C == 10)
        {
            PORTCbits.RC4 = ~PORTCbits.RC4;
            C = 0;
        }
        PIR1bits.CCP1IF = 0;
    }
}

void GPIO_Init()
{
    TRISCbits.TRISC4 = 0;
    PORTCbits.RC4 = 0;
}

void TMR1_Init()
{
    T1CON = 0b00000001;
}

void Compare_Init()
{
    CCPR1 = 50000;
    CCP1CON = 0b00001011;
    PIE1bits.CCP1IE = 1;
    PIR1bits.CCP1IF = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}


