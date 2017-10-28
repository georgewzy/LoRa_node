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
#include <string.h>
#include <stdio.h>
#include "stm32f10x.h"
#include "bsp.h"
#include "common.h"
#include "timer.h"
#include "uart.h"
#include "systick.h"
#include "spi.h"


extern uint8_t	uart1_rx_data[UART1_BUFF_LENGHT], uart1_tx_data[UART1_BUFF_LENGHT];



void run_led(void)
{
	
	uint8_t ret = 0;
	if(is_timeout_1ms(tim_led_g, 1000))
	{
		ret = get_port_val(LED_G_R);
		set_port_val(LED_G, !ret);
	}
}



int main(void)
{
	uint8_t status = 0, PacketRxGain = 0, version = 0;
	uint8_t tmp_data[512] = {0};
	uint32_t len = 0;
	char tmp[16], tmp1[16];
	double rssi;

	bsp_init();	
  
	USART_OUT(USART1, "sx1278_version = %d\r", version);
	
	while (1)
  	{	
 	
		
		
	
		if(is_timeout_1ms(tim1_cnt, 1000))
		{

		
			sprintf(tmp, "%3.2f", rssi);
			USART_OUT(USART1, "rssi = %s\r", tmp);
			USART_OUT(USART1, "PacketRxGain = %d\r", PacketRxGain);
		}	
		
	}
}






