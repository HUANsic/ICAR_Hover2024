/*
 * huansic_comm.c
 *
 *  Created on: May 21, 2024
 *      Author: ZonghuanWu
 */

#include "huansic_comm.h"

void huansic_subsys_init() {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	USART_InitTypeDef USART_InitStructure = { 0 };
	NVIC_InitTypeDef NVIC_InitStructure = { 0 };

	// apply changes
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART6, ENABLE);

	// set up AT GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	// set up TX and RX GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// set up UART
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	// apply changes
	USART_Init(UART6, &USART_InitStructure);

	// enable overrun error and reception and TX empty interrupt
	USART_ITConfig(UART6, USART_IT_ORE | USART_IT_RXNE | USART_IT_TXE, ENABLE);

	// set up NVIC
	NVIC_InitStructure.NVIC_IRQChannel = UART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;	// 3rd highest priority
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			// highest sub-priority
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	// apply changes
	NVIC_Init(&NVIC_InitStructure);

	// start UART
	USART_Cmd(UART6, ENABLE);
}

void __huansic_subsys_received(uint8_t data){
//    printf("%d\n", data);
}

void UART6_IRQHandler() {
	if (USART_GetITStatus(UART6, USART_IT_ORE)) {
		USART_ReceiveData(UART6);
		USART_ReceiveData(UART6);
		USART_ClearFlag(UART6, USART_FLAG_ORE);
	} else if (USART_GetITStatus(UART6, USART_IT_RXNE)) {
		__huansic_subsys_received(USART_ReceiveData(UART6) & 0x0FF);
		USART_ClearFlag(UART6, USART_FLAG_RXNE);
	}
}
