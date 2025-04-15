/*
 * File:   main.c
 * Author: PC
 *
 * Created on March 31, 2025, 10:36 PM
 */

#include "config.h"
#include <xc.h>

void GPIO_Init();
void TMR1_Init();
void Capture_Init();

void main(void) {
    GPIO_Init();
    TMR1_Init();
    Capture_Init();
    
    while(1)
    {
        PORTD = TMR1;
    }

    
    return;
}

void __interrupt() ISR(void)
{
    if (PIR1bits.CCP1IF)
    {
        PORTB = CCPR1;
        PIR1bits.CCP1IF = 0;
    }
}
void GPIO_Init()
{
    TRISCbits.TRISC2 = 1;
    TRISB = 0;
    TRISD = 0; 
    PORTB = 0;
    PORTD = 0;
    
}
void TMR1_Init()
{
    TMR1 = 0;
    T1CON = 0b00001011;

}

void Capture_Init()
{
    CCP1CON = 0b00000101;
    
    PIE1bits.CCP1IE = 1;
    PIR1bits.CCP1IF = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
}