/*
 * lps25hb.h
 *
 *  Created on: 29. 12. 2021
 *      Author: Aspire VX15
 */

#ifndef LPS25HB_H_
#define LPS25HB_H_



#include "main.h"
#include "i2c.h"


#define 	LPS25HB_DEVICE_ADDRESS_0				0xB8
#define 	LPS25HB_DEVICE_ADDRESS_1				0xBA

#define 	LPS25HB_WHO_AM_I_VALUE					0xBD
#define 	LPS25HB_WHO_AM_I_ADDRES					0x0F

#define 	LPS25HB_ADDRESS_CTRL1					0x20
#define		LPS25HB_ADDRESS_RES_CONF				0x10

#define 	LPS25HB_ADDRESS_TEMP_L					0x2B
#define 	LPS25HB_ADDRESS_TEMP_H					0x2C

#define		LPS25HB_ADDRESS_PRESS_XL				0x28


uint8_t lps25hb_init(void);
uint8_t lps25hb_read_byte(uint8_t reg_addr);
void lps25hb_write_byte(uint8_t reg_addr, uint8_t value);
void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length);
float lps25hb_get_temp(void);
float lps25hb_get_pressure(void);


#endif /* LPS25HB_H_ */
