#ifndef __USART2_H
#define __USART2_H

#include "ch32v30x.h"

void USART2_Init(uint32_t baudrate);
uint8_t USART2_GetRxFlag(void);
uint8_t USART2_GetRxData(void);

void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_SendByte(uint8_t Byte);

#endif
