/*************************************************
  Copyright (C), 1988-1999,  Tech. Co., Ltd.
  File name:      
  Author:       Version:        Date:
  Description:   
  Others:         
  Function List:  
    1. ....
  History:         
                   
    1. Date:
       Author:
       Modification:
    2. ...
*************************************************/
#ifndef __BSP_H
#define __BSP_H
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>
#include <stm32f10x_spi.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_iwdg.h>
#include <misc.h>


#define NVIC_VECTOR_ADDR			0x0

#define H						1
#define L						0

/*******************************I2C START**********************************/
#define	SCL_HIGH()			GPIO_SetBits(GPIOB, GPIO_Pin_6)			
#define SCL_LOW()			GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define SCL_READ()			GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6)

#define	SDA_HIGH()			GPIO_SetBits(GPIOB, GPIO_Pin_7)			
#define SDA_LOW()			GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define SDA_READ()			GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)
/*******************************I2C START**********************************/

#define LED_R_R()				GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)
#define LED_G_R()				GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)
#define RF_IRQ_R()				GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)

// DIO0~DIO5	
#define DIO0_R()				GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)
#define DIO1_R()				GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)
#define DIO2_R()				GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)
#define DIO3_R()				GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)
#define DIO4_R()				GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3)
#define DIO5_R()				GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)


#define	LED_R_H()				GPIO_SetBits(GPIOB, GPIO_Pin_0)			
#define LED_R_L()				GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define	LED_G_H()				GPIO_SetBits(GPIOB, GPIO_Pin_1)			
#define LED_G_L()				GPIO_ResetBits(GPIOB, GPIO_Pin_1)


#define SPI_SCN_H				GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define SPI_SCN_L				GPIO_ResetBits(GPIOB, GPIO_Pin_12)

#define RF_NREST_H				GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define RF_NREST_L				GPIO_ResetBits(GPIOA, GPIO_Pin_8)




typedef enum
{
	LED_R_R,
	LED_G_R,
	RF_IRQ_R,
	DIO0_R,
	DIO1_R,
	DIO2_R,
	DIO3_R,
	DIO4_R,
	DIO5_R
	
}GET_PORT;

typedef enum
{
	LED_R,
	LED_G,
	SPI_SCN,
	RF_NREST

}SET_PORT;



void system_reset(void);
void iwatchdog_clear(void);

uint8_t get_port_val(uint8_t port);
void set_port_val(u8 port, u8 val);
void bsp_init(void);

#endif



