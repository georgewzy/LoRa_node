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
#include "bsp.h"
#include "common.h"
#include "timer.h"

/*
*Function: rcc_config      
*Description: 系统时钟初始化  
*Calls: 无  
*Data Accessed: 无  
*Data Updated: 无    
*Input: 无
*Output: 无
*Return: 无     
*Others: 无    
*/
void rcc_config(void)
{
	ErrorStatus err_status;

	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);

	err_status = RCC_WaitForHSEStartUp();

	if (err_status == SUCCESS)
	{
// 		/* Enable Prefetch Buffer */
//         FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
//         
//         /* Flash 2 wait state */
//         FLASH_SetLatency(FLASH_Latency_2);
        
        /* HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1); 
        
        /* PCLK2 = HCLK */
        RCC_PCLK2Config(RCC_HCLK_Div1); 
        
        /* PCLK1 = HCLK */
        RCC_PCLK1Config(RCC_HCLK_Div1);
        
        /* PLLCLK = 8MHz * 9 = 64 MHz */
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
        
        /* Enable PLL */ 
        RCC_PLLCmd(ENABLE);
	
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        
        /* Wait till PLL is used as system clock source */
        while(RCC_GetSYSCLKSource() != 0x08);
	}


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_SPI2, ENABLE);
						   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB 
                        , ENABLE);
	
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
void system_reset(void) 
{ 
	__set_FAULTMASK(1); 
	NVIC_SystemReset();  
}


/*
*Function: iwatchdog_config      
*Description: 独立看门狗初始化 
*Calls: 无  
*Data Accessed: 无  
*Data Updated: 无    
*Input: 无
*Output: 无
*Return: 无     
*Others: 无    
*/
void iwatchdog_config(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_256);
	IWDG_SetReload(0xFFE);
	IWDG_ReloadCounter();
	IWDG_Enable();		
}

/*
*Function: iwatchdog_clear      
*Description: 独立看门狗 清狗 
*Calls: 无  
*Data Accessed: 无  
*Data Updated: 无    
*Input: 无
*Output: 无
*Return: 无     
*Others: 无    
*/
void iwatchdog_clear(void)
{
	IWDG_ReloadCounter();
}



void systick_config(void)
{
// 	SystemCoreClock / 1000    1ms中断一次
// 	SystemCoreClock / 100000 10us中断一次
//  SystemCoreClock / 1000000 1us中断一次	
	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	while(SysTick_Config(SystemCoreClock / 1000000));	 
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;		

}


/*
*Function: gpio_config      
*Description: GPIO初始化
*Calls: 无  
*Data Accessed: 无  
*Data Updated: 无    
*Input: 无
*Output: 无
*Return: 无     
*Others: 无    
*/
void gpio_config(void)
{
	GPIO_InitTypeDef gpio_init_structure;
	
	// LED_G == 1 LED_R == 0
	gpio_init_structure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;   //
  	gpio_init_structure.GPIO_Mode = GPIO_Mode_Out_PP;
  	gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &gpio_init_structure);	

	// RF_NREST
	gpio_init_structure.GPIO_Pin = GPIO_Pin_8;
	gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init_structure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &gpio_init_structure);
	
	// RF_CSN   RF_SDN
	gpio_init_structure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_11;
	gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init_structure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &gpio_init_structure);
	
	// RF_IRQ
	gpio_init_structure.GPIO_Pin = GPIO_Pin_10;
	gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init_structure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &gpio_init_structure);
	
	
	// IO0 ~ IO5
	gpio_init_structure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init_structure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio_init_structure);
	

	// UART1
  	gpio_init_structure.GPIO_Pin = GPIO_Pin_9;				// UART1 TX				    
  	gpio_init_structure.GPIO_Mode = GPIO_Mode_AF_PP;
  	gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;			 //
  	GPIO_Init(GPIOA, &gpio_init_structure);
	gpio_init_structure.GPIO_Pin = GPIO_Pin_10;				// UART1 RX	    
  	gpio_init_structure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;			 //
  	GPIO_Init(GPIOA, &gpio_init_structure);
		
	// SPI2
	gpio_init_structure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	gpio_init_structure.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio_init_structure);
	
	// I2C1
	gpio_init_structure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init_structure.GPIO_Mode =  GPIO_Mode_Out_OD; 
	GPIO_Init(GPIOB, &gpio_init_structure);	
	
}

/*
*Function: timer2_config      
*Description: 定时器2初始化  
*Calls: 无  
*Data Accessed: 无  
*Data Updated: 无    
*Input: 无
*Output: 无
*Return: 无     
*Others: 无    
*/
void timer2_config(void)
{
	NVIC_InitTypeDef nvic_init_structure;
	TIM_TimeBaseInitTypeDef timer2_init_structure;
	uint16_t cnt = 1000;

	TIM_DeInit(TIM2); 
    timer2_init_structure.TIM_CounterMode = TIM_CounterMode_Up;
    timer2_init_structure.TIM_ClockDivision = TIM_CKD_DIV1;
    timer2_init_structure.TIM_Period = cnt - 1;
    timer2_init_structure.TIM_Prescaler = 72 - 1; 	// 
    TIM_TimeBaseInit(TIM2, &timer2_init_structure);

	TIM_SetCounter(TIM2, 0);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}




/*
*Function: uart1_config      
*Description: 串口1初始化 
*Calls: 无  
*Data Accessed: 无  
*Data Updated: 无    








*Input: 无
*Output: 无
*Return: 无     
*Others: 无    
*/
void uart1_config(void)
{
	USART_InitTypeDef uart_init_structure;
	 
	USART_DeInit(USART1);

	uart_init_structure.USART_BaudRate = 9600;						//
  	uart_init_structure.USART_WordLength = USART_WordLength_8b;			//
  	uart_init_structure.USART_StopBits = USART_StopBits_1;				//
  	uart_init_structure.USART_Parity = USART_Parity_No;					//
  	uart_init_structure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   	//
  	uart_init_structure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//
	/* Configure USART1 */
  	USART_Init(USART1, &uart_init_structure);							//

	// UART 
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

   	/* Enable the USART1 */
  	USART_Cmd(USART1, ENABLE);
}

void spi2_init(void)
{
	SPI_InitTypeDef spi_init_structure;	
	
	SPI_I2S_DeInit(SPI2);
	
	spi_init_structure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;	//通信方式（全双工，半双工，串行发串行收）
	spi_init_structure.SPI_Mode = SPI_Mode_Master;		//模式选择，主机还是从机
	spi_init_structure.SPI_DataSize = SPI_DataSize_8b;	//数据帧长度选择，8位或16位
	spi_init_structure.SPI_CPOL = SPI_CPOL_Low;			//时钟极性
	spi_init_structure.SPI_CPHA = SPI_CPHA_1Edge;		//时钟相位，串行时钟第一个跳变沿采样数据，或第二个跳变沿~~SPI_CPHA_2Edge
	spi_init_structure.SPI_NSS = SPI_NSS_Soft;			// NSS信号由硬件控制还是软件控制，这里SPI_NSS_Soft
	spi_init_structure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;	//设置SPI波特率预分频值，也就是决定SPI的时钟的参数，从不分频道256分频8个可选值，初始化的时候我们选择256分频值SPI_BaudRatePrescaler_256, 传输速度为36M/256=140.625KHz
	spi_init_structure.SPI_FirstBit = SPI_FirstBit_MSB;	//数据传输顺序，MSB在前或LSB在前
	spi_init_structure.SPI_CRCPolynomial = 7;			//是用来设置CRC校验多项式，提高通信可靠性，大于1即可
	SPI_Init(SPI2, &spi_init_structure);
	
	SPI_Cmd(SPI2, ENABLE);
}



/*
*Function: nvic_config      
*Description: 中断向量配置  
*Calls: 无  
*Data Accessed: 无  
*Data Updated: 无    
*Input: 无
*Output: 无
*Return: 无     
*Others: 无    
*/
void nvic_config(void)
{
	NVIC_InitTypeDef nvic_init_structure;

	NVIC_DeInit();		// 自己写的函数
	
 	NVIC_SetVectorTable(NVIC_VectTab_FLASH, NVIC_VECTOR_ADDR);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	// timer2
	nvic_init_structure.NVIC_IRQChannel = TIM2_IRQn;
    nvic_init_structure.NVIC_IRQChannelPreemptionPriority = 10;    //
    nvic_init_structure.NVIC_IRQChannelSubPriority = 0;
    nvic_init_structure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init_structure);

	// UART1
	nvic_init_structure.NVIC_IRQChannel = USART1_IRQn;
    nvic_init_structure.NVIC_IRQChannelPreemptionPriority = 2;
    nvic_init_structure.NVIC_IRQChannelSubPriority = 0;
    nvic_init_structure.NVIC_IRQChannelCmd = ENABLE;	 
	NVIC_Init(&nvic_init_structure);
	
}

uint8_t get_port_val(uint8_t port)
{
	uint8_t val = 0;
	
	switch (port)
	{
		case LED_R_R:
			val = LED_R_R();
		break;
		
		case LED_G_R:
			val = LED_G_R();
		break;
		
		case RF_IRQ_R:
			val = RF_IRQ_R();
		break;
		
		case DIO0_R:
			val = DIO0_R();
		break;
		
		case DIO1_R:
			val = DIO1_R();
		break;
		
		case DIO2_R:
			val = DIO2_R();
		break;
		
		case DIO3_R:
			val = DIO3_R();
		break;
		
		case DIO4_R:
			val = DIO4_R();
		break;
		
		case DIO5_R:
			val = DIO5_R();
		break;
		
		default:
		break;			
	}

	return val;
}


void set_port_val(uint8_t port, u8 val)
{
	switch (port)
	{
		case LED_G:
			if (val == 1)
			{
				LED_G_H();
			}
			else
			{
				LED_G_L();
			}
		break;
		
		case LED_R:
			if (val == 1)
			{
				LED_R_H();
			}
			else
			{
				LED_R_L();
			}
		break;
			
		case SPI_SCN:
		if (val == 1)
		{
			SPI_SCN_H;
		}
		else
		{
			SPI_SCN_L;
		}		
		break;
		
		case RF_NREST:
		if (val == 1)
		{
			RF_NREST_H;
		}
		else
		{
			RF_NREST_L;
		}		
		break;
		
		default:
		break;			
	}

}



/*
*Function: bsp_init      
*Description: 底层初始化主函数  
*Calls: 无  
*Data Accessed: 无  
*Data Updated: 无    
*Input: 无
*Output: 无
*Return: 无     
*Others: 无    
*/
void bsp_init(void)
{
	rcc_config();
	nvic_config();
	systick_config();
	gpio_config();
	timer2_config();
	uart1_config();
	spi2_init();
}





