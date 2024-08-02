/*
 * huansic_comm.c
 *
 *  Created on: May 21, 2024
 *      Author: ZonghuanWu
 */

#include "huansic_serial.h"

void serial_init() {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	USART_InitTypeDef USART_InitStructure = { 0 };
	NVIC_InitTypeDef NVIC_InitStructure = { 0 };

	// apply changes
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);

	// set up TX and RX GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// set up UART
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	// apply changes
	USART_Init(USART2, &USART_InitStructure);

	// enable reception interrupt
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	// set up NVIC
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	// 2nd highest priority
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			// highest sub-priority
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	// apply changes
	NVIC_Init(&NVIC_InitStructure);

	// start UART
	USART_Cmd(USART2, ENABLE);
}

void __huansic_subsys_received(uint8_t data) {
	USART_SendData(USART2, data);
}

__attribute__((interrupt("WCH-Interrupt-fast"))) void USART2_IRQHandler() {
	if (USART_GetITStatus(USART2, USART_IT_ORE)) {
		USART_ReceiveData(USART2);
		USART_ReceiveData(USART2);
		USART_ClearFlag(USART2, USART_FLAG_ORE);
	} else if (USART_GetITStatus(USART2, USART_IT_RXNE)) {
		__huansic_subsys_received(USART_ReceiveData(USART2) & 0x0FF);
		USART_ClearFlag(USART2, USART_FLAG_RXNE);
	}
}
