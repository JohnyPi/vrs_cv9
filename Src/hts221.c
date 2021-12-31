/*
 * hts221.c
 *
 *  Created on: Dec 30, 2021
 *      Author: Aspire VX15
 */

#include <hts221.h>

uint8_t addres_hts221 = HTS221_DEVICE_ADDRESS;

uint8_t hts221_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addres_hts221, 0));
}

void hts221_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, addres_hts221, 0);
}

void hts221_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, addres_hts221, 1);
}



float hts221_get_humidity(void){
	  int16_t H0_T0_out, H1_T0_out, H_T_out;
	  int16_t H0_rh, H1_rh;
	  uint8_t buffer[2];
	  float   tmp_f;
	  uint16_t hum=0;

	  hts221_readArray(buffer,HTS221_H0_RH_X2,2);
	  H0_rh = buffer[0] >> 1;
	  H1_rh = buffer[1] >> 1;

	  hts221_readArray(buffer,HTS221_H0_T0_OUT_L,2);
	  H0_T0_out = (((uint16_t)buffer[1]) << 8) | (uint16_t)buffer[0];

	  hts221_readArray(buffer,HTS221_H0_T0_OUT_H,2);
	  H1_T0_out = (((uint16_t)buffer[1]) << 8) | (uint16_t)buffer[0];

	  hts221_readArray(buffer,HTS221_ADDRESS_HUMIDITY_L,2);
	  H_T_out = (((uint16_t)buffer[1]) << 8) | (uint16_t)buffer[0];

	  tmp_f = (float)(H_T_out - H0_T0_out) * (float)(H1_rh - H0_rh) / (float)(H1_T0_out - H0_T0_out)  +  H0_rh;
	  tmp_f *= 10.0f;

	  hum = ( tmp_f > 1000.0f ) ? 1000 : ( tmp_f <    0.0f ) ?    0 : ( uint16_t )tmp_f;

	  return hum/10.0;
}

float hts221_get_temperature(void){
	 int16_t T0_out, T1_out, T_out, T0_degC_x8_u16, T1_degC_x8_u16;
	  int16_t T0_degC, T1_degC;
	  uint8_t buffer[4], tmp;
	  float   tmp_f;

	  hts221_readArray(buffer,HTS221_T0_DEGC_X8,2);
	  hts221_readArray(&tmp,HTS221_T0_T1_DEGC_H2,1);
	  T0_degC_x8_u16 = (((uint16_t)(tmp & 0x03)) << 8) | ((uint16_t)buffer[0]);
	  T1_degC_x8_u16 = (((uint16_t)(tmp & 0x0C)) << 6) | ((uint16_t)buffer[1]);
	  T0_degC = T0_degC_x8_u16 >> 3;
	  T1_degC = T1_degC_x8_u16 >> 3;

	  hts221_readArray(buffer,HTS221_T0_OUT_L,4);

	  T0_out = (((uint16_t)buffer[1]) << 8) | (uint16_t)buffer[0];
	  T1_out = (((uint16_t)buffer[3]) << 8) | (uint16_t)buffer[2];

	  hts221_readArray(buffer,HTS221_ADDRESS_TEMP_L,2);

	  T_out = (((uint16_t)buffer[1]) << 8) | (uint16_t)buffer[0];

	  tmp_f = (float)(T_out - T0_out) * (float)(T1_degC - T0_degC) / (float)(T1_out - T0_out)  +  T0_degC;

	  return tmp_f;
}


uint8_t hts221_init(void){

	uint8_t status = 1;

	//LIS3MDL_ACC_ON;

	LL_mDelay(100);

	uint8_t val = hts221_read_byte(HTS221_WHO_AM_I_ADDRES);

	if(val == HTS221_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		status = 0;
		return status;
	}

	uint8_t ctrl1 =133; // 12<<4; // 51<<2
	hts221_write_byte(HTS221_ADDRESS_CTRL1, ctrl1);
	//uint8_t ctrl2 = 0b101<<0 ;
	//hts221_write_byte(HTS221_ADDRESS_CTRL1, ctrl2);



	return status;
}
