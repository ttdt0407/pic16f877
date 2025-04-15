/*
 * File:   main.c
 * Author: PC
 *
 * Created on April 15, 2025, 11:35 AM
 */


#include <xc.h>
#include "config.h"
#include <stdint.h>
#define _XTAL_FREQ 4000000


void PINS_Init();
void PWM_Init();
void TMR2_Init();
void Set_PWM_Duty(uint16_t duty_cycle);




void main(void) {
    PINS_Init();
    PWM_Init();
    TMR2_Init();
    
    Set_PWM_Duty(0);
    while(1)
    {
        if (REV)
        {
            PORTDbits.RD0 = ~PORTDbits.RD0;
            PORTDbits.RD1 = ~PORTDbits.RD1;
            __delay_ms(500);   // button release
        }
        
        if (LEV1)
        {
            Set_PWM_Duty(0);
            __delay_ms(100);
        }
        if (LEV2)
        {
             Set_PWM_Duty(250);
            __delay_ms(100);
        }
        if (LEV3)
        {
             Set_PWM_Duty(375);
            __delay_ms(100);
        }
        if (LEV4)
        {
             Set_PWM_Duty(500);
            __delay_ms(100);
        }
        __delay_ms(10);
        
    }
    return;
}


void PINS_Init()
{
    TRISB = 0x1F;
    TRISCbits.TRISC2 = 0;
    TRISD = 0;
    PORTDbits.RD0 = 0;
    PORTDbits.RD1 = 1;
}
void PWM_Init()
{
    CCP1CONbits.CCP1M2 = 1;
    CCP1CONbits.CCP1M3 = 1;
}
void TMR2_Init()
{
    PR2 = 124;
    T2CONbits.T2CKPS1 = 0;
    T2CONbits.T2CKPS0 = 1;
    T2CONbits.TMR2ON = 1;
}
void Set_PWM_Duty(uint16_t duty_cycle)
{
    if (duty_cycle <= 1024)
    {
    CCP1CONbits.CCP1Y = duty_cycle & 1;
    CCP1CONbits.CCP1X = duty_cycle & 2;
    CCPR1L = duty_cycle >> 2;
    }
}