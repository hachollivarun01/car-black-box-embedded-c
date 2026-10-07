/*
 * File:   menu.c
 * Author: Varun
 *
 * Created on 10 January, 2024, 5:02 PM
 */


#include <xc.h>
#include "main.h"
extern old;
int op = 1;

void view_menu(void) {
    for (long int i = 0; i < 50000; i++);
    CLEAR_DISP_SCREEN;
    clcd_putch('*', LINE1(14));
    int j = 0, k = 1, key = 0, po = -1, count = 0, press, count11 = 0, flag = 0, clear = 0, lg = 1;
    while (1) {
        int view = 1;
        char menu[5][20] = {"view log", "set time", "clear log", "download log", "cha pass"};
        //key = read_switches(STATE_CHANGE);

        clcd_print(menu[j], LINE1(0));
        clcd_print(menu[k], LINE2(0));

        if (read_switches(LEVEL_CHANGE) == MK_SW12) {
            count++;
        } else if (count < 300 && count > 0) //short press
        {
            op++;
            if (op >= 5) {
                op = 5;
            }
            po++;
            CLEAR_DISP_SCREEN;
            clcd_putch('*', LINE2(14));
            if (k == 4 || po == 0) {
                if (po > 3)
                    po == 3;
            } else {

                j++;
                k++;
            }
            count = 0;
        } else if (count > 300) //long press
        {
            CLEAR_DISP_SCREEN;
            if (op == 1) {
                if (clear == 1) {
                    clcd_print("NO RECENT LOGS", LINE1(0));
                    for (long int wa = 0; wa < 500000; wa++);
                    view = 0;
                    CLEAR_DISP_SCREEN;

                }
                char k = 0x00+(old*12);
                int c12 = 0, c11 = 0;
                while (view) {
                    if (flag == 1) {
                        if (k == 0x78) {
                            k = 0x00;
                        }
                        k = k + 12;
                        flag = 0;
                    } else if (flag == 2) {
                        if (k == 0x78) {
                            k = 0x00;
                        }
                        k = k - 12;
                        flag = 0;
                    }
                    clcd_print("LOG NUMBER", LINE1(0));
                    clcd_putch('0' + (lg / 10), LINE1(14));
                    clcd_putch('0' + (lg % 10), LINE1(15));
                    for (int l = 0; l < 12; l++) {
                        clcd_putch(read_external_eeprom(k + l), LINE2(l));
                    }
                    if (read_switches(LEVEL_CHANGE) == MK_SW12) {
                        c12++;
                    } else if (c12 < 300 && c12 > 0) {
                        lg++;
                        if (lg > 12) {
                            lg = 0;
                        }
                        flag = 1;
                        c12 = 0;
                    } 
                    else if (c12 > 300) 
                    {
                        k = 0x00;
                        c12 = 0;

                    }
                    if (read_switches(LEVEL_CHANGE) == MK_SW11) {
                        c11++;
                    }
                    else if (c11 < 300 && c11 > 0) {
                        lg--;
                        if (lg < 0) {
                            lg = 12;
                        }
                        flag = 2;
                        c11 = 0;
                    } else if (c11 > 300) {
                        CLEAR_DISP_SCREEN;
                        break;
                        c11 = 0;
                    }
                }
                op = 1;
            }
            if (op == 3) {
                clear = 1;
                clcd_print("LOGS CLEARED", LINE1(0));
                for (long int wa1 = 0; wa1 < 500000; wa1++);
                CLEAR_DISP_SCREEN;
                op = 3;
            }
            if (op == 5) 
            {
                if (change_password()) 
                {
                    CLEAR_DISP_SCREEN;
                    clcd_print("SUCCESS", LINE1(0));
                    for (long int wa1 = 0; wa1 < 500000; wa1++);
                } 
                else 
                {
                    CLEAR_DISP_SCREEN;
                    clcd_print("FAILURE", LINE1(0));
                    for (long int wa1 = 0; wa1 < 500000; wa1++);
                }
                op = 5;
            }
            if(op == 2)
            {
                
            }
            count = 0;

        }

        if (read_switches(LEVEL_CHANGE) == MK_SW11) {
            count11++;
        } else if (count11 < 300 && count11 > 0) // short press
        {
            op--;
            if (op <= 1) {
                op = 1;
            }
            po--;
            CLEAR_DISP_SCREEN;
            clcd_putch('*', LINE1(14));
            if (k == 1 || po == 3) {
                if (po<-1)
                    po == -1;
            } else {
                j--;
                k--;
            }
            count11 = 0;
        } else if (count11 > 300) //long press
        {
            CLEAR_DISP_SCREEN;
            clcd_print("in long", LINE1(0));
            while (1);
            count11 = 0;
        }


    }


}
