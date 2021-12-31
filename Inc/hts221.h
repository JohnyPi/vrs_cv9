/*
 * hts221.h
 *
 *  Created on: Dec 30, 2021
 *      Author: Aspire VX15
 */

#ifndef HTS221_H_
#define HTS221_H_


#include "main.h"
#include "i2c.h"


#define 	HTS221_DEVICE_ADDRESS				0xBE

#define 	HTS221_WHO_AM_I_VALUE				0xBC
#define 	HTS221_WHO_AM_I_ADDRES				0x0F

#define 	HTS221_ADDRESS_CTRL1				0x20
#define 	HTS221_ADDRESS_CTRL2				0x21
#define 	HTS221_ADDRESS_CTRL3				0x22

#define		HTS221_ADDRESS_STATUS				0x27

#define 	HTS221_ADDRESS_HUMIDITY_L			0x28
#define 	HTS221_ADDRESS_HUMIDITY_H			0x29

#define 	HTS221_ADDRESS_TEMP_L				0x2A
#define 	HTS221_ADDRESS_TEMP_H				0x2B

#define 	HTS221_H0_RH_X2        0x30
#define		HTS221_H1_RH_X2        0x31
#define 	HTS221_T0_DEGC_X8      0x32
#define 	HTS221_T1_DEGC_X8      0x33
#define 	HTS221_T0_T1_DEGC_H2   0x35
#define 	HTS221_H0_T0_OUT_L     0x36
#define 	HTS221_H0_T0_OUT_H     0x37
#define 	HTS221_H1_T0_OUT_L     0x3A
#define 	HTS221_H1_T0_OUT_H     0x3B
#define 	HTS221_T0_OUT_L        0x3C
#define 	HTS221_T0_OUT_H        0x3D
#define 	HTS221_T1_OUT_L        0x3E
#define 	HTS221_T1_OUT_H        0x3F


uint8_t hts221_read_byte(uint8_t reg_addr);
void hts221_write_byte(uint8_t reg_addr, uint8_t value);
void hts221_readArray(uint8_t * data, uint8_t reg, uint8_t length);
uint8_t hts221_init(void);
float hts221_get_humidity(void);
float hts221_get_temperature(void);

#endif /* HTS221_H_ */
