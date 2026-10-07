/*
 * File:   password.c
 * Author: Varun
 *
 * Created on 8 January, 2024, 5:15 PM
 */
#include <xc.h>
#include "main.h"
       
void inti_timer(void)
{
    GIE=1;
    PEIE=1;
    
    T08BIT=1;
    TMR0ON=1;
    T0CS=0;
    PSA=1;
    TMR0=6;
    TMR0IE=1;
    TMR0IF=0;
    
    TRISD=0x00;
    PORTD=0x00;
    
    TRISA=TRISA & 0xf0;
    PORTA=PORTA & 0xf0;
    
    TRISC=TRISC | 0x0f;
    PORTC=PORTC | 0x0f;
}
static  int sec=0,del=0;
int box_password(int *flag)
{
    int num2;
    num2=num2+(read_external_eeprom(0x79)-48);
    num2=(num2*10)+(read_external_eeprom(0x7a)-48);
    num2=(num2*10)+(read_external_eeprom(0x7b)-48);
    num2=(num2*10)+(read_external_eeprom(0x7c)-48);
    int fst=0;
    int num1=num2;
    del=0;
    int tm,delay=30;
    int num,size=4,n=3,wa=0;
    if(*flag==2)
    {
       while(1)
       {
           
           CLEAR_DISP_SCREEN;
           
           if(read_passwords(&num,size)==FAILURE)
           {
                *flag=0;
                
               return FAILURE;
           }
           if(num==num1)
           {
               *flag=0;
               return SUCCESS;
           }
           else
           {
             n--;
            
                 CLEAR_DISP_SCREEN;
            while (1) {
                if(n==0)
                {
                    while(1)
                    {
                        if(fst=0)
                        {
                           sec=0; 
                           fst=1;
                        }
                        
                      tm=delay-sec;
                    clcd_print("YOU ARE BLOCKED", LINE1(0));
                    clcd_putch('0' + (tm/100), LINE2(10));
                    clcd_putch('0' + ((tm/10)%10), LINE2(11));
                    clcd_putch('0' + (tm%10), LINE2(12));
                    if(tm==0)
                    {
                         CLEAR_DISP_SCREEN;
                        *flag=0;
                      return FAILURE;  
                    }
                    }
                    
                }
                else
                {
                clcd_print("FAILURE", LINE1(5));
                clcd_print("ATTEMPTS LEFT ", LINE2(0));
                clcd_putch('0' + (n % 10), LINE2(15));
                if (wa++ > 700) 
                {
                    wa=0;
                    CLEAR_DISP_SCREEN;
                    break;
                }
                }
           }
       }
    }
}
}

int read_passwords(int *num , int size1 ) {
    int i = 0,wa=0,blink=1,b=0;
    unsigned char key;
    clcd_print("ENTER PASSWORD", LINE1(0));
    sec=0;
    del=0;
    while (1) {
        if(blink)
        {
          clcd_putch('_',LINE2(b));
        }
        else
                clcd_putch(' ',LINE2(b));
        
        key = read_switches(STATE_CHANGE);
        if (key == MK_SW11) {
            sec=0;
            del=0;
            clcd_putch('*', LINE2(i));
            *num = ((*num)*10) + 1;
            i++;
            b++;
        }
        if (key == MK_SW12) {
            sec=0;
            del=0;
            clcd_putch('*', LINE2(i));
            *num = ((*num)*10) + 0;
            i++;
            b++;
        }
        if (i == size1) {
            CLEAR_DISP_SCREEN;
            break;
        }
        if(wa++>2500)
        {
            wa=0;
          blink=!blink;    
        }
        if(del==1)
        {
            return FAILURE;
        }
    }
    return UNDEFINED;
    i = 0;
    b=0;
    
}
void __interrupt() isr(void)
{
	static unsigned long count;
     
	if (TMR0IF)
	{
		TMR0 = TMR0 + 8;

		if (count++ == 20000)
		{
            sec++;
            if(sec==3)
            del=!del;
			count = 0;
		}
		TMR0IF = 0;
	}
}