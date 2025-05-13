/*
 * File:   main.c
 * Author: PC
 *
 * Created on May 13, 2025, 12:01 PM
 */


#include <xc.h>
#include "config.h"
#include <stdint.h>
#define _XTAL_FREQ 4000000

volatile uint8_t UART_Buffer = 0;
void UART_RX_Init();
void GPIO_Init();


void main(void) {
    
    UART_RX_Init();
    GPIO_Init();
    
    while(1)
    {
        
    }
    
    return;
}


void __interrupt() ISR(void)
{
    if (PIR1bits.RCIF)
    {
        UART_Buffer = RCREG;
        PORTD = UART_Buffer;
    }
    
}
 
 
void UART_RX_Init()
{
    SPBRG = 25;
    TXSTAbits.BRGH = 1;
    RCSTAbits.SPEN = 1;
    TXSTAbits.SYNC = 0;
    TRISCbits.TRISC6 = 1;
    TRISCbits.TRISC7 = 1;
    PIE1bits.RCIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    RCSTAbits.CREN  = 1;

}


void GPIO_Init()
{
    TRISD = 0;
    PORTD = 0;
}