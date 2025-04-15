/*
 * File:   main.c
 * Author: ADIMIN
 *
 * Created on March 26, 2025, 10:41 AM
 */


#include <xc.h>
#include "config.h"
#include "lcd.h"
#include <stdint.h>
#include <stdio.h>

float value_1, value_2, value_3;
uint32_t data;
uint16_t C = 0;
char buffer[20];
volatile uint8_t updateSensor1 = 0;
volatile uint8_t updateSensor2 = 0;
volatile uint8_t updateSensor3 = 0;

void GPIO_Config();
void trigger_1();
void trigger_2();
void trigger_3();
void LCD_Display_1();
void LCD_Display_2();
void LCD_Display_3();
void TMR1_Init();
void TMR2_Init();

void __interrupt() ISR(void)
{   
    if(PIR1bits.TMR2IF) {
        C++;
        if(C == 1000) {
            updateSensor1 = 1;
        } else if (C == 2000) {
            updateSensor2 = 1;
        } else if (C == 3000) {
            updateSensor3 = 1;
            C = 0;
        }
        TMR2 = 68;
        PIR1bits.TMR2IF = 0;
    }
}


void main(void) {
    GPIO_Config();
    LCD_Init();
    LCD_Clear();
    TMR1_Init();
    TMR2_Init();
    
    while(1)
    {  
        if (updateSensor1) {
            trigger_1();
            LCD_Display_1();
            updateSensor1 = 0;
        }
        if (updateSensor2) {
            trigger_2();
            LCD_Display_2();
            updateSensor2 = 0;
        }
        if (updateSensor3) {
            trigger_3();
            LCD_Display_3();
            updateSensor3 = 0;
        }
    
    }
    return;
}

void TMR1_Init()
{
    TMR1 = 0;
    T1CONbits.TMR1CS = 0;
    T1CONbits.T1CKPS0 = 1;
    T1CONbits.T1CKPS1 = 1;
    
    PIE1bits.TMR1IE = 1;
    PIR1bits.TMR1IF = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
}

void TMR2_Init()
{
    T2CONbits.T2CKPS1 = 1;
    T2CONbits.T2CKPS0 = 0;
    TMR2 = 68;
    PIE1bits.TMR2IE = 1;
    PIR1bits.TMR2IF = 0;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    T2CONbits.TMR2ON = 1;
}

void trigger_1()
{   
    TRIG_1 = 1;
    __delay_us(10);
    TRIG_1 = 0;
    while(!ECHO_1);
    T1CONbits.TMR1ON = 1;
    TMR1 = 0;
    while(ECHO_1);
    T1CONbits.TMR1ON = 0;
    data = TMR1;
    value_1 = (float)data*0.048;

}
void trigger_2()
{
    TMR1 = 0;
    TRIG_2 = 1;
    __delay_us(10);
    TRIG_2 = 0;
     while(!ECHO_2);
    T1CONbits.TMR1ON = 1;
    TMR1 = 0;
    while(ECHO_2);
    T1CONbits.TMR1ON = 0;
    data = TMR1;
    value_2 = (float)data*0.048;
}
void trigger_3()
{
   
    TMR1 = 0;
    TRIG_3 = 1;
    __delay_us(10);
    TRIG_3 = 0;
     while(!ECHO_3);
    T1CONbits.TMR1ON = 1;
    TMR1 = 0;
    while(ECHO_3);
    T1CONbits.TMR1ON = 0;
    data = TMR1;
    value_3 = (float)data*0.048;
}

void GPIO_Config()
{
 TRIG_1_DATA = 0;
 TRIG_2_DATA = 0;
 TRIG_3_DATA = 0;
 ECHO_1_DATA = 1;
 ECHO_2_DATA = 1;
 ECHO_3_DATA= 1;
}
void LCD_Display_1()
{   
    LCD_Set_Cursor(1,1);
    LCD_Write_String("Distance 1 is:");
    LCD_Set_Cursor(2,1);
    sprintf(buffer, "%.3f [cm]", value_1);
    LCD_Write_String(buffer);
    __delay_ms(20);
}
void LCD_Display_2()
{   LCD_Set_Cursor(1,1);
    LCD_Write_String("Distance 2 is:");
    LCD_Set_Cursor(2,1);
    sprintf(buffer, "%.3f [cm]", value_2);
    LCD_Write_String(buffer);
    __delay_ms(20);
}
void LCD_Display_3()
{   
    LCD_Set_Cursor(1,1);
    LCD_Write_String("Distance 3 is:");
    LCD_Set_Cursor(2,1);
    sprintf(buffer, "%.3f [cm]", value_3);
    LCD_Write_String(buffer);
    __delay_ms(20);
}



