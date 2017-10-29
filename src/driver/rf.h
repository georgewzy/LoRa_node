
#ifndef __RF_H
#define __RF_H
#include <stm32f10x.h>

extern uint16_t send_cnt, rev_cnt;
extern uint8_t send_buf[128];
extern uint8_t rev_buf[128];

void rf_init(void);
void rf_rx_mode(void);
uint8_t rf_rev_data(uint8_t *buf);
uint8_t rf_send_data(uint8_t *buf, uint8_t size);


#endif
