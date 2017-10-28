
#ifndef __SPI_H
#define __SPI_H
#include <stm32f10x.h>







uint8_t spi_exchange_byte(uint8_t ch);
void sx1278_write(uint8_t addr, uint8_t data);
void sx1278_read(uint8_t addr, uint8_t *data);
uint8_t spi_read(uint8_t addr);
void spi_write(uint16_t data);
void spi_write_buff(uint8_t addr, uint8_t *buff, uint8_t size);
void spi_read_buff(uint8_t addr, uint8_t *buff, uint8_t size);
void spi_write_fifo(uint8_t *buff, uint8_t size);
void spi_read_fifo(uint8_t *buff, uint8_t size);
#endif

