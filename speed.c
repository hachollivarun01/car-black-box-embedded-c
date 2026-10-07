/*
 * File:   speed.c
 * Author: Varun
 *
 * Created on 5 January, 2024, 8:16 PM
 */


#include "main.h"
#include <xc.h>

int car_speed(unsigned short adc_reg_val)
{
    int speed;
    speed=adc_reg_val/10.23;
    if(speed>99)
    {
        speed=99;
    }
    clcd_putch('0'+ speed/10, LINE2(14));
    clcd_putch('0'+ speed%10, LINE2(15));
    return speed;
}


/*void main(void)
{
    unsigned short adc_reg_val;

    init_config();

    while (1)
    {
        adc_reg_val = read_adc(CHANNEL4);
        glow_led(adc_reg_val);
    }
}
*/

