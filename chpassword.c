/*
 * File:   chpassword.c
 * Author: Varun
 *
 * Created on 19 January, 2024, 8:30 PM
 */


#include <xc.h>
#include "main.h"

//static int setblink=20000;
int change_password() {

    long int j = 0,count=0, n = 5, wa = 0;
    long int num=0, num1=0;
    while (1) {
        
          
        
           
            read_passwordss(&num, &num1, 4, 4);
        
        if (num==num1) 
        {
            write_external_eeprom(0x79, '0'+(num/1000));
            write_external_eeprom(0x7a, '0'+((num/100)%10));
            write_external_eeprom(0x7b, '0'+((num/10)%10));
            write_external_eeprom(0x7c, '0'+(num%10));
            CLEAR_DISP_SCREEN;
            return num;
        } 
        else
        {
            CLEAR_DISP_SCREEN;  
            return 0;
        }

    }


}
void read_passwordss(int *num, int *num1, int size1, int size2) {
    int i = 0,wa=0,blink=1,b=0;
    unsigned char key;
    clcd_print("ENTER PASSWORD", LINE1(0));
    while (1) {
        if(blink)
        {
          clcd_putch('_',LINE2(b));
        }
        else
        {
         clcd_putch(' ',LINE2(b));
        }
        key = read_switches(STATE_CHANGE);
        if (key == MK_SW11) {
            clcd_putch('*', LINE2(i));
            *num = ((*num)*10) + 1;
            i++;
            b++;
        }
        if (key == MK_SW12) {
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
    }
    i = 0;
    b=0;
    clcd_print("RE ENTER PASSWORD", LINE1(0));
    while (1) 
    {
        if(blink)
        {
          clcd_putch('_',LINE2(b));
        }
        else
                clcd_putch(' ',LINE2(b));
        key = read_switches(STATE_CHANGE);
        if (key == MK_SW11) {
            clcd_putch('*', LINE2(i));
            *num1 = ((*num1)*10) + 1;
            i++;
            b++;
        }
        if (key == MK_SW12) {
            clcd_putch('*', LINE2(i));
            *num1 = ((*num1)*10) + 0;
            i++;
            b++;
        }
        if (i == size2) {
            CLEAR_DISP_SCREEN;
            break;
        }
        if(wa++>2500)
        {
            wa=0;
          blink=!blink;  
          
        }
    }
}
