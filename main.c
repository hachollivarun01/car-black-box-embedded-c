/*

 * File : main.c
 * Author : Varun
 *
 * Created on 4 January, 2024, 6 : 08 PM
 */


#include <xc.h>
#include "main.h"
int i = 0, flag = 0, pass = 0, j = 0, k = 0,old=0;
char key;
unsigned char time[9];
void main(void) {
    unsigned short adc_reg_val;
    inti_MKP();
    init_realtime();
    init_adc();
    //unsigned char time[9];
    int speed;
    char var=0x00;
    char gear[7][3] = {"ON", "GN", "GR", "G1", "G2", "G3", "G4"};
    char menu[5][20] = {"VIEW LOG", "SET TIME", "CLEAR LOG", "DOWNLOAD LOG", "CHANGE PASSWORD"};

    while (1) {
        adc_reg_val = read_adc(CHANNEL4);
        speed=car_speed(adc_reg_val);
        get_time();
        display_time();
        key = read_switches(STATE_CHANGE);
        car_gear(key);
        if (key == MK_SW11) {
            flag = 2;
        }
        pass = box_password(&flag);
        clcd_print(gear[i], LINE2(11));
        if (pass == SUCCESS) {
            view_menu();
        }
       if (key == MK_SW1 || key== MK_SW2 || key == MK_SW3) 
        {
           old++;
           if(old>12)
           {
               old=1;
           }
            if(var==0x79)
                var=0x00;
            write_external_eeprom(var++, time[0]);
            write_external_eeprom(var++, time[1]);
            write_external_eeprom(var++, time[2]);
            write_external_eeprom(var++, time[3]);
            write_external_eeprom(var++, time[4]);
            write_external_eeprom(var++, time[5]);
            write_external_eeprom(var++, time[6]);
            write_external_eeprom(var++, time[7]);
            write_external_eeprom(var++, gear[i][0]);
            write_external_eeprom(var++, gear[i][1]);
            write_external_eeprom(var++, '0'+ speed/10);
            write_external_eeprom(var++, '0'+ speed%10);
        }
    }

return;
}
