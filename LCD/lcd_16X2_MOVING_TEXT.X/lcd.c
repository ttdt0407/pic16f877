#include "lcd.h"
#include "config.h"

void LCD_DATA(unsigned char data)
{
    if(data & 1)
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

void LCD_CMD (unsigned char CMD)
{
    
    // Select Command REG
    RS = 0;
    // Move the command data to the LCD
    LCD_DATA(CMD);
    // Send the EN clock signal
    EN = 1;
    __delay_us(LCD_EN_Delay);
    EN = 0;
    __delay_us(LCD_EN_Delay);
    
}

void LCD_Init()
{
    
    // IO pins configuration
    LCD_DATA_PORT_D = 0;
    LCD_DATA_RS_D = 0;
    LCD_DATA_EN_D = 0;
    
    //The Init procedure
    LCD_DATA(0);    // clear all the bit in data of LCD 
    __delay_ms(30);// wait for LCD to start (larger than 15ms is safety)
    __delay_us(LCD_EN_Delay);   // wait 500us for LCD processing
    
    //The 3 times function set 8-bits length
    LCD_CMD(0x03); 
    __delay_ms(5);  // delay >= 4.1ms
    LCD_CMD(0x03);
    __delay_us(150);  // delay >= 100us
    LCD_CMD(0x03);
    
    // Interface 4 bits length
    LCD_CMD(0x02);
    
    // Function set: 4bit 2line 5x7dots
    LCD_CMD(0x02);
    LCD_CMD(0x08);
    
    // Display on, cursor off
    LCD_CMD(0x00);
    LCD_CMD(0x0c);
    
    //Display clear
    LCD_CMD(0x00);
    LCD_CMD(0x01);
    
    //Entry mode
    LCD_CMD(0x00);
    LCD_CMD(0x06);
}
    
void LCD_Clear()
{
    LCD_CMD(0);
    LCD_CMD(1);
}
void LCD_Write_Char(char data)
{
    char low4, high4;
    low4 = data & 0x0f;
    high4 = data & 0xf0;
    
    RS = 1; // set data mode
    
    LCD_DATA(high4>>4);
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

void LCD_Write_String (char*str)
{
    unsigned int i = 0;
    while(str[i] != '\0')
    {
        LCD_Write_Char(str[i++]);
    }
}

void LCD_Set_Cursor (unsigned char r, unsigned char c)
{
    unsigned char temp, low4, high4;
    
    if (r == 1)
    {
        temp = 0x80 + c - 1;
        high4 = temp >> 4;
        low4 = temp & 0x0f;
        LCD_CMD(high4);
        LCD_CMD(low4);
    }
    
    if (r == 2)
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