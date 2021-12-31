/*
 * lps25hb.c
 *
 *  Created on: 29. 12. 2021
 *      Author: Aspire VX15
 */

#include <lps25hb.h>

uint8_t addres_lps25hb = LPS25HB_DEVICE_ADDRESS_0;

uint8_t lps25hb_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addres_lps25hb, 0));
}

void lps25hb_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, addres_lps25hb, 0);
}

void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, addres_lps25hb, 1);
}

float lps25hb_get_temp(void)
{
	uint8_t buffer[2];
	int16_t tempVal = 0;
	float T_out = 0;

	lps25hb_readArray(buffer, LPS25HB_ADDRESS_TEMP_L, 2);
	tempVal = ((((int16_t)buffer[1]) << 8) | (int16_t)buffer[0]);
	T_out = (((float)tempVal) / 480) + 42.5;
	return T_out;
}


float lps25hb_get_pressure(void){
	uint8_t buffer[3];
	int32_t tmp = 0;
	float P_out = 0;

	lps25hb_readArray(buffer, LPS25HB_ADDRESS_PRESS_XL, 3);

	  for(uint8_t i = 0; i < 3; i++)
	    tmp |= (((uint32_t)buffer[i]) << (8 * i));

	  /* convert the 2's complement 24 bit to 2's complement 32 bit */
	  if(tmp & 0x00800000)
	    tmp |= 0xFF000000;


	  P_out = ((float)tmp) / 4096;
	  return P_out;
}


uint8_t lps25hb_init(void)
{

	uint8_t status = 1;

	//LIS3MDL_ACC_ON;

	LL_mDelay(100);

	uint8_t val = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRES);

	if(val == LPS25HB_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		addres_lps25hb = LPS25HB_DEVICE_ADDRESS_1;
		val = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRES);
		if(val == LPS25HB_WHO_AM_I_VALUE)
		{
			status = 1;
		}
		else
		{
			status = 0;
			return status;
		}
	}

	uint8_t ctrl1 =39<<2; // 12<<4; // 51<<2
	lps25hb_write_byte(LPS25HB_ADDRESS_CTRL1, ctrl1);
	uint8_t ctrl2 = 0b0101 ;
	lps25hb_write_byte(LPS25HB_ADDRESS_RES_CONF, ctrl2);

	return status;
}






