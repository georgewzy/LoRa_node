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
*************************************************/

#include <string.h>
#include <stdarg.h>
#include <stm32f10x_usart.h>
#include "uart.h"
#include "bsp.h"
#include "common.h"
#include "timer.h"



uint8_t	uart1_rx_data[UART1_BUFF_LENGHT] = {0}, uart1_tx_data[UART1_BUFF_LENGHT] = {0};
uint16_t uart1_rx_cnt = 0, uart1_tx_cnt = 0;
uint8_t uart3_rx_data[UART3_BUFF_LENGHT] = {0}, uart3_tx_data[UART3_BUFF_LENGHT] = {0};
uint16_t uart3_rx_cnt = 0, uart3_tx_cnt = 0;

uint8_t uart1_rece_flag = 0, uart3_rece_flag = 0;





/*
*Function: USART1_IRQHandler      
*Description: 串口2中断服务程序
*Calls: 无  
*Data Accessed: 
	rece_buff2
	send_at_flag
	rece_over_flag
*Data Updated: 
	rece_buff2
	rece_over_flag
*Input: 无
*Output: 无
*Return: 无     
*Others: 无    
*/
void USART1_IRQHandler(void)
{
	u8 ch = 0;	

   	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {   
	    USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
        ch = USART_ReceiveData(USART1);	
		uart1_rece_flag = 1;
		is_timeout_1ms(tim_uart1, 0);
        
		if (uart1_rx_cnt < UART1_BUFF_LENGHT)
		{
			uart1_rx_data[uart1_rx_cnt++] = ch;	
		}
		else
		{
			uart1_rece_flag = 0;
			uart1_rx_cnt = 0;
		}
	}
	
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)                  
  	{ 
     	USART_ITConfig(USART1, USART_IT_TXE, DISABLE);					   
  	}		
}

/*
*Function: USART3_IRQHandler      
*Description: 串口1中断服务程序  
*Calls: 无  
*Data Accessed: 无  
*Data Updated: 无    
*Input: 无
*Output: 无
*Return: 无     
*Others: 无    
*/
void USART3_IRQHandler(void)
{
	u8 ch = 0;

   	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {      
	    USART_ClearITPendingBit(USART3, USART_IT_RXNE);	
        ch = USART_ReceiveData(USART3);
	}
  		
	if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)                   
  	{ 
     	USART_ITConfig(USART3, USART_IT_TXE, DISABLE);					   
  	}		
}




/*
*Function: receive_data      
*Description: 接收串口数据  
*Calls: IS_TIMEOUT_1MS 
*Data Accessed: rece_over_flag  
*Data Updated: rece_over_flag 
*Input: rece_data：串口缓冲区数据
*Output: data：接收到的数据
*Return: 无     
*Others: 无    
*/
void uart1_rece_data(uint8_t *rx_data)
{	
	if (uart1_rece_flag == 1)
	{	
		if (is_timeout_1ms(tim_uart1, 50))
		{		
			memcpy(rx_data, uart1_rx_data, UART1_BUFF_LENGHT);			
			
			USART_OUT(USART3, uart1_rx_data);
			memset(uart1_rx_data, 0, UART1_BUFF_LENGHT);
			uart1_rx_cnt = 0;
			uart1_rece_flag = 0;
		}
	}
}






void uart1_send_data(uint8_t tx_data[], uint16_t tx_data_len)
{
	uint16_t i = 0;
		
	for (i=0; i<tx_data_len; i++)
	{
		USART_SendData(USART1, tx_data[i]);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
	}
}




/*
*Function: system_reset      
*Description: system reset  
*Calls: 无  
*Data Accessed: 无  
*Data Updated: 无    
*Input: 无
*Output: 无
*Return: 无     
*Others: 无    
*/
void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...)
{ 
	const char *s;
    int d;
	double lf;
    char buf[16];
    
	va_list ap;
    __va_start(ap, Data);

	while(*Data != '\0')
	{				                         
		if(*Data==0x5c)
		{									
			switch (*++Data)
			{
				case 'r':							          
					USART_SendData(USARTx, 0x0d);	   
					Data++;
				break;
				case 'n':							          
					USART_SendData(USARTx, 0x0a);	
					Data++;
				break;
				
				default:
					Data++;
			    break;
			}						 
		}
		else if(*Data=='%')
		{									  
			switch (*++Data){				
				case 's':										  
                	s = __va_arg(ap, const char *);
                	for ( ; *s; s++) 
					{
                    	USART_SendData(USARTx,*s);
						while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
                	}
					Data++;
                	break;
            	case 'd':										 
                	d = __va_arg(ap, int);
                	itoa(d, buf, 10);
                	for (s = buf; *s; s++) 
					{
                    	USART_SendData(USARTx,*s);
						while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
                	}
					Data++;
                	break;
//				case 'f':
//					lf = __va_arg(ap, double);
//					s = (char*)&lf;
//					*s = *lf;
//					*(s+1) = *(lf+1);
//					*(s+2) = *(lf+2);
//					*(s+3) = *(lf+3);
//					break;
//				default:
					Data++;
				    break;
			}		 
		}
		else 
			USART_SendData(USARTx, *Data++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
	}
}







void float_char(float f, unsigned char *s)
{

	unsigned char *p;
	
	p =(unsigned char *)&f;
	*s = *p;

	*(s+1) = *(p+1);
	*(s+2) = *(p+2);
	*(s+3) = *(p+3);
}

void double_char(double f, unsigned char *s)
{

	unsigned char *p;
	
	p =(unsigned char *)&f;
	*s = *p;

	*(s+1) = *(p+1);
	*(s+2) = *(p+2);
	*(s+3) = *(p+3);
}









