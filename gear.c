/*
 * File:   gear.c
 * Author: Varun
 *
 * Created on 9 January, 2024, 4:30 PM
 */
#include <xc.h>
#include "main.h"
extern int i;
void car_gear(int key) 
{
    char gear[7][3] = {"ON", "GN", "GR", "G1", "G2", "G3", "G4"};
    if (key == MK_SW2) 
    {
        if (i == 6) 
        {
            ;
        } 
        else 
        {
            i++;
        }

    } 
    else if (key == MK_SW3) 
    {
        if (i == 0) 
        {
            ;
        } 
        else 
        {
            i--;
        }

    }
    //  clcd_print(gear[i], LINE2(11));
}