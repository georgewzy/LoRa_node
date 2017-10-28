
#include "rf.h"
#include "bsp.h"
#include "uart.h"

#include "timer.h"
#include "systick.h"
#include "spi.h"

uint16_t send_cnt = 0, rev_cnt = 0;
uint8_t rev_buf[128];
uint8_t send_buf[128];

void sx1278_reset(void)
{
	uint8_t i=0;
	set_port_val(RF_NREST, L);
	set_port_val(SPI_SCN, L);
	for(i=100; i!=0; i--)
	{
		delay_us(10);
	}
	
	set_port_val(RF_NREST, H);
	set_port_val(SPI_SCN, H);
	for(i=250; i!=0; i--)
	{
		delay_us(10);
	}
	
	
}



void sx1278_sleep(void)
{
	
}


void rf_rx_mode(void)
{
//	RFM96_LoRaEntryRx();
}


uint8_t rf_rev_data(uint8_t *buf)
{
	uint8_t len = 0;
	
	if(get_port_val(RF_IRQ_R))
	{
		USART_OUT(USART1, "george\r\n");
	
		rf_rx_mode();
	}
	
	if(len > 0)
	{
		rev_cnt++;
	}
	
	return len;
}



uint8_t rf_send_data(uint8_t *buf, uint8_t size)
{
	int ret = 0;

	delay_1ms(10);
	rf_rx_mode();
	
	
	if(ret > 0)
	{
		send_cnt++;
	}
	
	return ret;
}



