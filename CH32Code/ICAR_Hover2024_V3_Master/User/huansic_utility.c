/*
 * huansic_utility.c
 *
 *  Created on: Aug 11, 2024
 *      Author: ZonghuanWu
 */

#include "huansic_utility.h"

void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void UART8_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/*
 * 		Time flow control
 */

volatile uint32_t millis;

void Utility_Init(void) {
	Utility_Time_Init();
	Utility_Serial_Init();
}

void Utility_Time_Init(void) {
	millis = 0;
	// clear status register and counter
	SysTick->SR = 0;
	SysTick->CNT = 0;
	// update every millisecond
	SysTick->CMP = SystemCoreClock / 1000 - 1;
	// start SysTick
	SysTick->CTLR = 0xF;
	// enable interrupt
	NVIC_SetPriority(SysTicK_IRQn, 1);
	NVIC_EnableIRQ(SysTicK_IRQn);
}

void Utility_Time_DelayMs(uint32_t duration) {
	uint32_t start = millis;
	while(millis - start < duration);
}

void Utility_Time_DelayUs(uint32_t duration) {
	uint8_t i;
	for (i = 0; i < duration; i++) {
		// TODO check disassembly for instruction cycle count
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
	}
}

void SysTick_Handler(void) {
	SysTick->SR = 0;
	millis++;
}

/**
 * 		Serial communication via CH340 to computer
 */

uint8_t* _util_serial_rx_ptr, _util_serial_tx_ptr;
uint8_t _util_serial_rx_cnt, _util_serial_tx_cnt;

void Utility_Serial_Init(void) {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	USART_InitTypeDef USART_InitStructure = { 0 };
	NVIC_InitTypeDef NVIC_InitStructure = { 0 };

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

	/* UART8 TX-->C.4   RX-->C.5 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(UART8, &USART_InitStructure);
	USART_ITConfig(UART8, USART_IT_RXNE, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = UART8_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(UART8, ENABLE);
}

void Utility_Serial_SendBytes(uint8_t* dptr, uint8_t count) {
	_util_serial_tx_ptr = dptr;
	_util_serial_tx_cnt = count;
	UART8->CTLR1 |= USART_CTLR1_TXEIE;		// enable continuous transfer
}

void Utility_Serial_ReceiveBytes(uint8_t* dptr, uint8_t count) {
	_util_serial_rx_ptr = dptr;
	_util_serial_rx_cnt = count;
	UART8->CTLR1 |= USART_CTLR1_RXNEIE;		// enable continuous transfer
}

uint8_t Utility_Serial_ReadyToSend(void) {
	return (USART2->STATR & USART_STATR_TXE) ? 1 : 0;
}

uint8_t Utility_Serial_ReadyToReceive(void) {
	return (USART2->STATR & USART_STATR_RXNE) ? 0 : 1;
}

uint8_t Utility_Serial_AbortSend(void) {
	uint8_t tmp = _util_serial_tx_cnt;
	_util_serial_tx_cnt = 0;
	UART8->CTLR1 &= !USART_CTLR1_TXEIE;		// disable TXE interrupt
	return tmp;		// number of bytes remaining
}

uint8_t Utility_Serial_AbortReceive(void) {
	uint8_t tmp = _util_serial_rx_cnt;
	_util_serial_rx_cnt = 0;
	UART8->CTLR1 &= !USART_CTLR1_RXNEIE;		// disable RXNE interrupt
	return tmp;		// number of bytes remaining
}

__attribute__((__weak__)) void User_Serial_RxComplete(void) {
	return;
}

void UART8_IRQHandler(void) {
	// if a new byte is received and the interrupt is enabled
	if ((USART2->STATR & USART_STATR_RXNE) && (USART2->CTLR1 & USART_CTLR1_RXNEIE)) {
		if (_util_serial_rx_cnt) {
			_util_serial_rx_cnt--;
			if (_util_serial_rx_ptr)
				*_util_serial_rx_ptr = UART8->DATAR & 0x0FF;	// USART_ReceiveData(USART2);
			if (!_util_serial_rx_cnt) {
				UART8->CTLR1 &= !USART_CTLR1_RXNEIE;		// disable RXNE interrupt
				User_Serial_RxComplete();
			}
		}
	}

	// if a byte of data is transferred into the shift register and the interrupt is enabled
	if ((USART2->STATR & USART_STATR_TXE) && (USART2->CTLR1 & USART_CTLR1_TXEIE)) {
		if (_util_serial_tx_cnt) {
			_util_serial_tx_cnt--;
			if (_util_serial_tx_ptr)
				UART8->DATAR = (*_util_serial_tx_ptr) & 0x0FF;	// USART_SendData(USART2);
			if (!_util_serial_rx_cnt)
				UART8->CTLR1 &= !USART_CTLR1_TXEIE;		// disable TXE interrupt
		}
	}
}

/**
 * 		On-board LEDs
 */
