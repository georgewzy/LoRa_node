
#include "systick.h"
#include "common.h"


uint32_t systick_cnt = 0;

void delay_us(uint32_t us)
{
	systick_cnt = us;		 
	while(systick_cnt != 0);					//等待延时时间到
}


void delay_ms(uint32_t ms)
{
	systick_cnt = ms*1000;		 
	while(systick_cnt != 0);					//等待延时时间到
}



void SysTick_Handler(void)
{

	if (systick_cnt != 0)
	{
		systick_cnt--;	
	}
	
}




