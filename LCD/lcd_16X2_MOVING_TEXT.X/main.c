/*
 * File:   main.c
 * Author: PC
 *
 * Created on March 21, 2025, 7:49 PM
 */


#include <xc.h>
#include "config.h"
#include "lcd.h"

void main(void) {
    
    LCD_Init();
    LCD_Clear();
    LCD_Set_Cursor(1,5);
    LCD_Write_String("DinhTien");
    LCD_Set_Cursor(2,7);
    LCD_Write_String("HCMUT");
    
    while(1)
    {
        
    }
    return;
}
