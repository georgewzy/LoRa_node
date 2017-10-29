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
#ifndef _TIMER_H
#define _TIMER_H
#include <stm32f10x.h>

/*!
 * \brief Timer object description
 */
typedef struct TimerEvent_s
{
    uint32_t Timestamp;         //! Current timer value
    uint32_t ReloadValue;       //! Timer delay value
    bool IsRunning;             //! Is the timer currently running
    void ( *Callback )( void ); //! Timer IRQ callback function
    struct TimerEvent_s *Next;  //! Pointer to the next Timer object.
}TimerEvent_t;


typedef uint32_t TimerTime_t;




enum timer
{
    tim1_cnt,
    tim2_cnt,
	tim_led_g,
	tim_uart1,
	tim_rxpacket,
	tim_at,
	tim_max
};




//
// #define IS_TIMEOUT_1MS(index, count)    ((g_tim_cnt[(uint8_t)(index)] >= (count)) ?  	\
//                                         ((g_tim_cnt[(uint8_t)(index)] = 0) == 0) : 0)



extern volatile uint32_t g_tim_cnt[(uint8_t)tim_max];
void delay_1ms(uint32_t ms);
uint8_t is_timeout_1ms(uint8_t type, uint32_t count);



#endif

