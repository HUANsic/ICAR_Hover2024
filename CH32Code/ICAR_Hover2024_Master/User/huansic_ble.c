/*
 * huansic_comm.c
 *
 *  Created on: May 21, 2024
 *      Author: ZonghuanWu
 */

#include "huansic_ble.h"

void huansic_ble_init() {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	USART_InitTypeDef USART_InitStructure = { 0 };
	NVIC_InitTypeDef NVIC_InitStructure = { 0 };

	// apply changes
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);

	// set up TX and RX GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
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
	USART_Init(UART7, &USART_InitStructure);

	// enable reception interrupt
	USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);

	// set up NVIC
	NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	// 2nd highest priority
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			// highest sub-priority
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	// apply changes
	NVIC_Init(&NVIC_InitStructure);

	// start UART
	USART_Cmd(UART7, ENABLE);
}

void huansic_ble_AT(uint8_t enter) {
	GPIO_WriteBit(GPIOE, GPIO_Pin_2, enter ? Bit_RESET : Bit_SET);		// LOW for AT mode
}

void huansic_ble_send(uint8_t *str, uint8_t len) {

}

void __huansic_ble_received(uint8_t data) {

}

uint8_t __huansic_ble_sent() {
	return 0;	// todo
}

__attribute__((interrupt("WCH-Interrupt-fast"))) void UART7_IRQHandler() {
	if (USART_GetITStatus(UART7, USART_IT_ORE)) {
		USART_ReceiveData(UART7);
		USART_ReceiveData(UART7);
		USART_ClearFlag(UART7, USART_FLAG_ORE);
	} else if (USART_GetITStatus(UART7, USART_IT_RXNE)) {
		__huansic_ble_received(USART_ReceiveData(UART7) & 0x0FF);
		USART_ClearFlag(UART7, USART_FLAG_RXNE);
	} else if (USART_GetITStatus(UART7, USART_IT_TXE)) {
		USART_ClearFlag(UART7, USART_FLAG_TXE);
	}
}
