#include "lcd.h"
#include <xc.h>


void LCD_DATA(unsigned char data)
{
    if (data & 1)
        D4 = 1;
    else D4 = 0;
    if (data & 2)
        D5 = 1;
    else D5 = 0;
    if (data & 4)
        D6 = 1;
    else D6 = 0;
    if (data & 8)
        D7 = 1;
    else D7 = 0;
}

void LCD_CMD(unsigned char cmd)
{
    RS = 0;
    LCD_DATA(cmd);
    EN = 1;
    __delay_us(LCD_EN_Delay);
    EN = 0;
    __delay_us(LCD_EN_Delay);
    
}

void LCD_Init()
{
    LCD_DATA_PORT_D = 0;
    LCD_RS_D = 0;
    LCD_EN_D = 0;
    
    LCD_DATA(0x00); 
    __delay_ms(30);
    __delay_us(LCD_EN_Delay);
    
    LCD_CMD(0x03);
    __delay_ms(5);
    
    LCD_CMD(0x03);
    __delay_us(150);
    
    LCD_CMD(0x03);
    
    LCD_CMD(0x02);
    
    LCD_CMD(0x02);
    LCD_CMD(0x08);
    
    LCD_CMD(0x00);
    LCD_CMD(0x01);
    
    LCD_CMD(0x00);
    LCD_CMD(0x0c);
    
    LCD_CMD(0x00);
    LCD_CMD(0x06);
}

void LCD_Write_Char(char data)
{
    char low4, high4;
    
    high4 = data >> 4;
    low4 = data & 0x0f;
    
    RS = 1;
    LCD_DATA(high4);
    EN = 1;
    __delay_us(LCD_EN_Delay);
    EN = 0;
    __delay_us(LCD_EN_Delay);
    
    LCD_DATA(low4);
    EN = 1;
    __delay_us(LCD_EN_Delay);
    EN = 0;
    __delay_us(LCD_EN_Delay);    
}

void LCD_Write_String(char* str)
{
    int i = 0;
    while(str[i] != '\0')
    {
        LCD_Write_Char(str[i++]);
    }
}

void LCD_Clear()
{
    LCD_CMD(0);
    LCD_CMD(1);
}

void LCD_Set_Cursor(unsigned char r, unsigned char c)
{
    unsigned char temp, high4, low4;
    
    if(r == 1)
    {
        temp = 0x80 + c - 1;
        high4 = temp >> 4;
        low4 = temp & 0x0f;
        LCD_CMD(high4);
        LCD_CMD(low4);
    }
    
    if(r == 2)
    {
        temp = 0xc0 + c - 1;
        high4 = temp >> 4;
        low4 = temp & 0x0f;
        LCD_CMD(high4);
        LCD_CMD(low4);
    }
    
}
void LCD_SR()
{
    LCD_CMD(0x01);
    LCD_CMD(0x0c);
}

void LCD_SL()
{
    LCD_CMD(0x01);
    LCD_CMD(0x08);
}



