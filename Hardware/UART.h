#ifndef __UART_H
#define __UART_H

#include <stdio.h>

void UART_Init(void);
void UART_SendByte(uint8_t);
uint8_t UART_GetRxData(void);
uint8_t UART_GetRxFlag(void);

#endif
