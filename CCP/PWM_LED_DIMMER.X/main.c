/*
 * File:   main.c
 * Author: ADIMIN
 *
 * Created on April 14, 2025, 2:56 PM
 */
/**************************************************
 *How to use CCP modules to generate PWM 
 *signals with a desired frequency of 2kHz
 *and variable duty cycle. We?ll use the 
 *output PWM signal to control the brightness
 *of a small LED in this LAB. The duty cycle should 
 *be gradually increasing from 0 up-to 100% then it
 *should start to gradually drop back to 0% and so 
 * on.
 *************************************************/

#include <xc.h>
#include "config.h"
#include <stdint.h>
#define _XTAL_FREQ 4000000

void CCP_Init();
void TMR2_Init();
void Set_PR2();
void PWM_Set_Duty_Cycle(uint16_t dc);



int main(void) {
    CCP_Init();
    Set_PR2();
    TMR2_Init();
    
    uint16_t dc = 0;  // Duty cycle value
    while (1)
    {
        dc = 0;
        while (dc < 500)
        {
            PWM_Set_Duty_Cycle(dc);
            dc++;
            __delay_ms(2);
        }
        __delay_ms(100);
        while (dc > 0)
        {
            PWM_Set_Duty_Cycle(dc);
            dc--;
            __delay_ms(2);
        }
        __delay_ms(100);
    }
    
    
    return 0;
}

void CCP_Init()
{
    CCP1CONbits.CCP1M3 = 1;
    CCP1CONbits.CCP1M2 = 1;
    TRISCbits.TRISC2 = 0;
}

void Set_PR2()
{
    PR2 = 124;
}
void TMR2_Init()
{
    T2CONbits.T2CKPS0 = 1;
    T2CONbits.T2CKPS1 = 0;
    T2CONbits.TMR2ON = 1;
}

void PWM_Set_Duty_Cycle(uint16_t dc)
{
    if (dc < 1024)  // check the dc value to ensure its within 10- bit range
    {
        CCP1CONbits.CCP1Y = dc & 1;
        CCP1CONbits.CCP1X = dc & 2;
        CCPR1L = dc >> 2;
    }
    
}