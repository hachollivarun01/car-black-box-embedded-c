/*
 * File:   main.h
 * Author: Varun
 *
 * Created on 4 January, 2024, 4:18 PM
 */
#define SUCCESS             1
#define FAILURE             0
#define UNDEFINED           2

#ifndef LCD_H
#define LCD_H



#define CLCD_PORT			PORTD
#define CLCD_EN				RC2
#define CLCD_RS				RC1
#define CLCD_RW				RC0
#define CLCD_BUSY			RD7
#define PORT_DIR			TRISD7


#define HI												1
#define LO												0

#define INPUT											0xFF
#define OUTPUT											0x00

#define DATA_COMMAND									1
#define INSTRUCTION_COMMAND								0
#define _XTAL_FREQ                  20000000
#define LINE1(x)									(0x80 + (x))
#define LINE2(x)										(0xC0 + (x))

#define TWO_LINE_5x8_MATRIX_8_BIT					clcd_write(0x38, INSTRUCTION_COMMAND)
#define CLEAR_DISP_SCREEN				                clcd_write(0x01, INSTRUCTION_COMMAND)
#define CURSOR_HOME							clcd_write(0x02, INSTRUCTION_COMMAND)
#define DISP_ON_AND_CURSOR_OFF						clcd_write(0x0C, INSTRUCTION_COMMAND)
#define EIGHT_BIT_MODE   0x33
void init_clcd(void);
void clcd_print(const unsigned char *data, unsigned char addr);
void clcd_putch(const unsigned char data, unsigned char addr);
void clcd_write(unsigned char bit_values, unsigned char control_bit);

#endif

#ifndef Ds1307_H
#define Ds1307_H

#define SLAVE_READ		0xD1
#define SLAVE_WRITE		0xD0


#define SEC_ADDR		0x00
#define MIN_ADDR		0x01
#define HOUR_ADDR		0x02
#define DAY_ADDR		0x03
#define DATE_ADDR		0x04
#define MONTH_ADDR		0x05
#define YEAR_ADDR		0x06
#define CNTL_ADDR		0x07


void write_ds1307(unsigned char address1,  unsigned char data);
unsigned char read_ds1307(unsigned char address1);
void init_ds1307(void);

#endif

#ifndef I2C_H
#define I2C_H


void init_i2c(void);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
void i2c_write(unsigned char data);
unsigned char i2c_read(void);

#endif

void display_date(void);
void display_time(void);
void get_time(void);
static void get_date(void);
void init_realtime(void);

#ifndef ADC_H
#define ADC_H

#define CHANNEL0		0x00
#define CHANNEL1		0x01
#define CHANNEL2		0x02
#define CHANNEL3		0x03
#define CHANNEL4		0x04
#define CHANNEL5		0x05
#define CHANNEL6		0x06
#define CHANNEL7		0x07
#define CHANNEL8		0x08
#define CHANNEL9		0x09
#define CHANNEL10		0x0A

void init_adc(void);
unsigned short read_adc(unsigned char channel);

#endif

int car_speed(unsigned short adc_reg_val);

#ifndef MATRIX_KEYPAD_H
#define MATRIX_KEYPAD_H



#define MAX_ROW				4
#define MAX_COL				3

#define STATE_CHANGE				1
#define LEVEL_CHANGE				0
#define MATRIX_KEYPAD_PORT			PORTB
#define ROW3					PORTBbits.RB7
#define ROW2					PORTBbits.RB6
#define ROW1					PORTBbits.RB5
#define COL4					PORTBbits.RB4
#define COL3					PORTBbits.RB3
#define COL2					PORTBbits.RB2
#define COL1					PORTBbits.RB1


#define MK_SW1					1
#define MK_SW2					2
#define MK_SW3					3
#define MK_SW4					4
#define MK_SW5					5
#define MK_SW6					6
#define MK_SW7					7
#define MK_SW8					8
#define MK_SW9					9
#define MK_SW10				10
#define MK_SW11				11
#define MK_SW12				12

#define ALL_RELEASED	0xFF

#define HI				1
#define LO				0

unsigned char scan_key(void);
void inti_timer(void);
void inti_MKP(void);
unsigned char read_switches(unsigned char detection_type);
#endif
int read_passwords(int *num, int size1);
void read_passwordss(int *num, int *num1, int size1, int size2);
int change_password();
void car_gear( int key);
int box_password(int *flag);
void view_menu(void);

#ifndef EXTERNAL_EEPROM_H
#define EXTERNAL_EEPRO_H

#define SLAVES_READ		0xA1
#define SLAVES_WRITE		0xA0


void write_external_eeprom(unsigned char address1,  unsigned char data);
unsigned char read_external_eeprom(unsigned char address1);

#endif
