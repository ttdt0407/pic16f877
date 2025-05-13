/*
 * File:   main.c
 * Author: PC
 *
 * Created on May 13, 2025, 11:05 AM
 */

#include <xc.h>
#include <stdint.h>
#include "config.h"

#define _XTAL_FREQ 4000000

void UART_TX_Init();
void UART_Write_Data(uint8_t);
void GPIO_Init();



void main(void) {
    
    GPIO_Init();
    UART_TX_Init();
    uint8_t data = 0;
    
    
    while(1)
    {
        if (PORTBbits.RB0)
        {
            data++;
            __delay_ms(150);
        }
        if (PORTBbits.RB1)
        {
            data--;
            __delay_ms(150);
        }
        if (PORTBbits.RB2)
            {
            UART_Write_Data(data);
            __delay_ms(150);
        }
        PORTD = data;
    }
    return;
}


void UART_TX_Init()
{
    SPBRG = 25;
    TXSTAbits.BRGH = 1;
    TXSTAbits.SYNC = 0;
    RCSTAbits.SPEN = 1;
    TRISCbits.TRISC6 = 1;
    TRISCbits.TRISC7 = 1;
    TXSTAbits.TXEN = 1;
}

void UART_Write_Data(uint8_t data)
{
    while(!TXSTAbits.TRMT);
    TXREG = data;
}

void GPIO_Init()
{
    TRISB = 0x07;
    TRISD = 0x00;
    PORTD = 0x00;
}