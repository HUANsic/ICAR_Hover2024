/*
 * huansic_utility.h
 *
 *  Created on: Aug 11, 2024
 *      Author: ZonghuanWu
 */

#ifndef USER_HUANSIC_UTILITY_H_
#define USER_HUANSIC_UTILITY_H_

#include <ch32v30x.h>

void Utility_Init(void);

/*
 * 		Time related
 */
void Utility_Time_Init(void);

void Utility_Time_DelayMs(uint32_t duration);

void Utility_Time_DelayUs(uint32_t duration);

/*
 * 		Serial communication with CH340 related
 */
void Utility_Serial_Init(void);

void Utility_Serial_SendBytes(uint8_t* dptr, uint8_t count);

void Utility_Serial_ReceiveBytes(uint8_t* dptr, uint8_t count);

uint8_t Utility_Serial_ReadyToSend(void);

uint8_t Utility_Serial_ReadyToReceive(void);

uint8_t Utility_Serial_AbortSend(void);

uint8_t Utility_Serial_AbortReceive(void);

/***		Define Your Own Method Below In YOUR Code!!!		***/
void User_Serial_RxComplete(void);

#endif /* USER_HUANSIC_UTILITY_H_ */
