/*
 * File:   matrix.c
 * Author: Varun
 *
 * Created on 4 January, 2024, 8:00 PM
 */
#include <xc.h>
#include "main.h"

void inti_MKP(void) {
    ADCON1 = 0x0f;
    TRISB = 0x1e;
    RBPU = 0;
    PORTB = PORTB | 0xE0;
    //global and pherpharal interupt enabler
    GIE = 1;
    PEIE = 1;
    // timer 0 configurations 
    T08BIT = 1;
    TMR0ON = 1;
    T0CS = 0;
    PSA = 1;
    TMR0 = 6;
    TMR0IE = 1;
    TMR0IF = 0;
}
unsigned char scan_key(void) {
    ROW1 = LO;
    ROW2 = HI;
    ROW3 = HI;

    if (COL1 == LO) {
        return 1;
    } else if (COL2 == LO) {
        return 4;
    } else if (COL3 == LO) {
        return 7;
    } else if (COL4 == LO) {
        return 10;
    }

    ROW1 = HI;
    ROW2 = LO;
    ROW3 = HI;

    if (COL1 == LO) {
        return 2;
    } else if (COL2 == LO) {
        return 5;
    } else if (COL3 == LO) {
        return 8;
    } else if (COL4 == LO) {
        return 11;
    }

    ROW1 = HI;
    ROW2 = HI;
    ROW3 = LO;
    /* TODO: Why more than 2 times? */
    ROW3 = LO;

    if (COL1 == LO) {
        return 3;
    } else if (COL2 == LO) {
        return 6;
    } else if (COL3 == LO) {
        return 9;
    } else if (COL4 == LO) {
        return 12;
    }

    return 0xFF;
}

unsigned char read_switches(unsigned char detection_type) {
    static unsigned char once = 1, key;

    if (detection_type == STATE_CHANGE) {
        key = scan_key();
        if (key != 0xFF && once) {
            once = 0;
            return key;
        } else if (key == 0xFF) {
            once = 1;
        }
    } else if (detection_type == LEVEL_CHANGE) {
        return scan_key();
    }

    return 0xFF;
}


