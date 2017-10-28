


#include "bsp.h"
#include "spi.h"
#include "stm32f10x_spi.h"




uint8_t spi_exchange_byte(uint8_t ch)
{

		/* Loop while DR register in not emplty */
  while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI2, ch);

  /* Wait to receive a byte */
  while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI2);	

}

void sx1278_write(uint8_t addr, uint8_t data)
{
	spi_write_buff(addr, &data, 1);
}

void sx1278_read(uint8_t addr, uint8_t *data)
{
	spi_read_buff(addr, data, 1);
}


uint8_t spi_read(uint8_t addr)
{
	uint8_t tmp = 0;
	
	set_port_val(SPI_SCN, 0);
	
	spi_exchange_byte(addr&0x7F);
	tmp = spi_exchange_byte(0xFF);
	
	set_port_val(SPI_SCN, 1);
	
	return tmp;
}

void spi_write(uint16_t data)
{
	data |= 0x8000;
	
	set_port_val(SPI_SCN, 0);
	
	spi_exchange_byte(data >> 8);
	spi_exchange_byte((uint8_t)data);
	
	set_port_val(SPI_SCN, 1);
}




void spi_write_buff(uint8_t addr, uint8_t *buff, uint8_t size)
{
	uint8_t i = 0;
	
	set_port_val(SPI_SCN, 0);
	spi_exchange_byte(addr | 0x80);
	
	for (i=0; i<size; i++)
	{
		spi_exchange_byte(buff[i]);
	}

	set_port_val(SPI_SCN, 1);
}

void spi_read_buff(uint8_t addr, uint8_t *buff, uint8_t size)
{
	uint8_t i = 0;
	
	set_port_val(SPI_SCN, 0);
	spi_exchange_byte(addr & 0x7F);
	
	for (i=0; i<size; i++)
	{
		buff[i] = spi_exchange_byte(0);
	}

	set_port_val(SPI_SCN, 1);
	
}

void spi_write_fifo(uint8_t *buff, uint8_t size)
{
	spi_write_buff(0, buff, size);
}

void spi_read_fifo(uint8_t *buff, uint8_t size)
{
	spi_read_buff(0, buff, size);
}









