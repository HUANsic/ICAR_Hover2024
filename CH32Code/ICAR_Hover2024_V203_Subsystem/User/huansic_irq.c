/*
 * huansic_irq.c
 *
 *  Created on: May 20, 2024
 *      Author: ZonghuanWu
 */

#include "huansic_irq.h"

void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void SysTick_Handler() {
	SysTick->SR = 0;
	__huansic_systick_update_irq();
}
