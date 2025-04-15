/*
 * File:   main.c
 * Author: ADIMIN
 *
 * Created on March 15, 2025, 8:57 PM
 */


#include <xc.h>
#include "config.h"
#include <stdint.h>


uint8_t C = 0;     // global variable


void __interrupt() ISR(void)
{
    if (PIR1bits.TMR1IF)    //check flag ngat
    {
        C++;                //neu co ngat tang bien global len 1
        if(C==15)           //check neu bien global tran 15 lan
        {
            //Event2: Toggle LED
            PORTBbits.RB0 = ~PORTBbits.RB0;     //event 2: dao trang thai led
            C=0;            //sau khi dao trang thai set bien global ve 0                   
        } 
        PIR1bits.TMR1IF = 0;  //clear flag ngat
    }
}
void main(void) {
    
    TRISBbits.TRISB0 = 0;     //cau hinh chan B0
    PORTBbits.RB0 = 0;        //output chan B0
    
    TMR1 = 0;                 //clear gia tri timer1
    T1CONbits.TMR1CS = 0;     //cau hinh timer1
    T1CONbits.T1CKPS0 = 0;
    T1CONbits.T1CKPS1 = 0;
    
    PORTBbits.RB0 = 1;     // bat den
    
    T1CONbits.TMR1ON = 1;  // bat timer 
    
    PIE1bits.TMR1IE = 1;   //bat ngat timer1
    PIR1bits.TMR1IF = 0;   //clear flag timer1
    INTCONbits.PEIE = 1;   //cau hinh ngat cho ngoai vi
    INTCONbits.GIE = 1;    //cau hinh ngat toan cuc
    
    while(1)              //chuong trinh chay
    {
        
    }
    
    
    
    return;
}
