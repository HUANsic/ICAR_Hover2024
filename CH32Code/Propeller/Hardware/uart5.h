#ifndef __UART5_H
#define __UART5_H

#include "ch32v30x.h"



void UART5_Init(uint32_t baudrate);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_SendByte(uint8_t Byte);
uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);

#endif
