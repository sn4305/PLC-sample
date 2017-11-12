#ifndef __UART_INIT_H
#define	__UART_INIT_H

#include "stm8s.h"
#include "stm8s_clk.h"
#include "stm8s_gpio.h"
#include "stm8s_uart1.h"
#include <stdio.h>



void UART1_Configuration(void);  
void UART1_Send_byte(u8 byte);   
void UART1_Send_str(u8 *string, u16 len);
void UART1_rx_handler(uint8_t * pdata, uint8_t len);
u16 CRC16(u8 *pchMsg,u16 wDataLen);
void reply_to_server(void);

#endif