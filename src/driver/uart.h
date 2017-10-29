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

#ifndef __UART_H
#define __UART_H
#include <stm32f10x.h>



#define UART1_BUFF_LENGHT				   	512
#define UART3_BUFF_LENGHT					512




void uart1_rece_data(uint8_t *rx_data);
void uart3_rece_data(uint8_t *rx_data);
void uart1_send_data(uint8_t tx_data[], uint16_t tx_data_len);
void uart3_send_data(uint8_t *tx_data, uint16_t tx_data_len);
void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...);
void float_char(float f, unsigned char *s);
void double_char(double f, unsigned char *s);
#endif




