#ifndef __USART2_H
#define __USART2_H

#include "ch32v20x.h"
#include "opt.h"

void USART2_Init(uint32_t baudrate);
uint8_t USART2_GetRxFlag(void);
uint8_t USART2_GetRxData(void);

void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_SendByte(uint8_t Byte);
void Serial_SendByteData(uint8_t Byte);
void Serial_SendSensorData(opt_data_typedef opt_data);
#endif
