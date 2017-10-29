
#include "i2c.h"
#include "common.h"
#include "bsp.h"


bool i2c_start(void)
{
	SDA_HIGH();
	SCL_HIGH();
	delay(5);
	if(!SDA_READ())
	{
		return false;		// 
	}
	SDA_LOW();
	if(SDA_READ()) 
	{
		return false; 		// 
	}
	SDA_LOW();
	delay(5);
	return true;
}


void i2c_stop(void)
{
	SCL_LOW();
	delay(5);
	SDA_LOW();
	delay(5);
	SCL_HIGH();
	SDA_HIGH();
	delay(5);
}


bool i2c_wait_ack(void) //返回为:=1有ACK,=0无ACK
{
	SCL_LOW();
	delay(5);
	SDA_HIGH();
	delay(5);
	SCL_HIGH();
	delay(5);
	if(SDA_READ())
	{
		SCL_LOW();
		return false;
	}
	SCL_LOW();
	return true;
}

 
void i2c_ack(void)
{
	SCL_LOW();
	SDA_LOW();
	delay(5);
	SCL_HIGH();
	delay(5);
	SCL_LOW();
	delay(5);
}



void i2c_no_ack(void)
{ 
	SCL_LOW();
	SDA_HIGH();
	delay(5);
	SCL_HIGH();
	delay(5);
	SCL_LOW();
	delay(5);
}



void i2c_send_byte(uint8_t byte) //数据从高位到低位//
{
	uint8_t i = 8;
	while (i--)
	{
		SCL_LOW();
		delay(5);
		if (byte&0x80)
		{
			SDA_HIGH();
		}
		else 
		{
			SDA_LOW();
		}
		byte<<=1;
		SCL_HIGH();
		delay(5);
	}
	
	SCL_LOW();
}



uint8_t i2c_rece_byte(void)    //数据从高位到低位//
{ 
	uint8_t i=8;
	uint8_t byte=0;

	SDA_HIGH();
	while (i--)
	{
		byte <<= 1;
		SCL_LOW();
		delay(5);
		SCL_HIGH();
		if (SDA_READ())
		{
			byte |= 0x01;
		}
	}
	SCL_LOW();
	return byte;
}


/////////////////////////////////////////////////////////////////////////



