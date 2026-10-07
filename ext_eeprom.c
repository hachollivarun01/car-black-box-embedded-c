/*
 * File:   ext_eeprom.c
 * Author: Varun
 *
 * Created on 12 January, 2024, 10:40 AM
 */

#include <xc.h>
#include "main.h"
void write_external_eeprom(unsigned char address, unsigned char data)
{
	i2c_start();
	i2c_write(SLAVES_WRITE);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
	for(unsigned int i = 3000;i--;);
}

unsigned char read_external_eeprom(unsigned char address)
{
	unsigned char data;

	i2c_start();
	i2c_write(SLAVES_WRITE);
	i2c_write(address);
	i2c_rep_start();
	i2c_write(SLAVES_READ);
	data = i2c_read();
	i2c_stop();

	return data;
}
