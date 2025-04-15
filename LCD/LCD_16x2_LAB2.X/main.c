/*
 * File:   main.c
 * Author: PC
 *
 * Created on March 22, 2025, 9:08 AM
 */


#include <xc.h>
#include "config.h"
#include "lcd.h"

void main(void) {
    
    
    LCD_Init();
    LCD_Clear();
    LCD_Set_Cursor(1,1);
    LCD_Write_String("DINHTIEN");
    LCD_Set_Cursor(2,3);
    LCD_Write_String("HCMUT");
    
    while(1)
    {
        for(int i = 0; i < 8; i ++)
        {
            __delay_ms(300);
            LCD_SR();
        }
        
        for(int i = 0; i < 8; i ++)
        {
            __delay_ms(300);
            LCD_SL();
        }
    }
    return;
}
