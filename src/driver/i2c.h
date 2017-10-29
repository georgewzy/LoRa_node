
#ifndef _I2C_H
#define _I2C_H
#include <stm32f10x.h>







bool i2c_start(void);
void i2c_stop(void);
bool i2c_wait_ack(void);
void i2c_ack(void);
void i2c_no_ack(void);
void i2c_send_byte(uint8_t byte);
uint8_t i2c_rece_byte(void);




#endif
