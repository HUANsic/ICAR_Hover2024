/*
 * huansic_chronos.c
 *
 *  Created on: May 20, 2024
 *      Author: ZonghuanWu
 */

#include "huansic_chronos.h"

volatile uint32_t milliseconds;
volatile uint32_t microseconds;

struct Reminder {
	uint32_t scheduled_ms;
	void (*thread)(uint32_t ms);
};

#define	REMINDER_LENGTH	32
struct Reminder reminders[REMINDER_LENGTH];
uint8_t wheel[REMINDER_LENGTH];		// will be set to 255 if there's no upcoming reminder
uint8_t next;
void (*fp)(uint32_t ms);

void huansic_chronos_init(void) {
	uint8_t i;
	milliseconds = 1;
	next = 0;
	for (i = 0; i < REMINDER_LENGTH; i++) {
		wheel[i] = 255;
		reminders[i].thread = 0;
		reminders[i].scheduled_ms = 0;
	}

	// clear status register and counter
	SysTick->SR = 0;
	SysTick->CNT = 0;
	// update every millisecond
//	SysTick->CMP = SystemCoreClock / 1000 - 1;
	SysTick->CMP = SystemCoreClock / 1000000 - 1;
	// start SysTick
	SysTick->CTLR = 0xF;
	// enable interrupt
	NVIC_SetPriority(SysTicK_IRQn, 1);
	NVIC_EnableIRQ(SysTicK_IRQn);
}

void huansic_delay_ms(uint32_t duration) {
	uint32_t start = milliseconds;
	while(milliseconds - start < duration);
}

//void huansic_delay_us(uint16_t duration) {
//	uint32_t temp = duration, i=0;
//	temp *= SystemCoreClock / 1000000;	// total CPU cycles
//	if (temp < 30)
//		return;		// can't make it that precise, probably already elapsed
//	temp -= 30;		// idk, feel like it
//	temp /= 5;		// for loop count
//
//	for (i = 0; i < temp; i++)
//		;
//}

//void huansic_delay_us(u16 time)
//{
//   u16 i=0;
//   while(time--)
//   {
//      i=10;
//      while(i--) ;
//   }
//}

void huansic_delay_us(uint32_t duration) {
    uint32_t start_ms = milliseconds;
    uint16_t duration_ms = duration / 1000;
    uint16_t duration_us = duration % 1000;
    while(milliseconds - start_ms < duration_ms);
    uint32_t start_us = 0; microseconds = 0;
    while(microseconds - start_us < duration_us);
}

uint32_t huansic_chronos_milliseconds() {
	return milliseconds;
}

int8_t huansic_chronos_schedule(uint32_t scheduled_ms, void (*thread)(uint32_t ms)) {
	// if time already elapsed, return -1
	if (scheduled_ms <= milliseconds)
		return -1;

	// find a place to hold the information
	uint8_t i, target = 255, replc = 255, temp, holding;
	for (i = 0; i < REMINDER_LENGTH; i++) {
		if (!reminders[i].thread) {
			target = i;
			break;
		}
	}
	// if there's no place for it, return -2
	if (target == 255)
		return -2;

	// add the reminder
	reminders[target].scheduled_ms = scheduled_ms;
	reminders[target].thread = thread;

	// insert into the time wheel
	for (i = 0; i < REMINDER_LENGTH; i++) {
		// if it is empty
		if (wheel[(next + i) % REMINDER_LENGTH] == 255) {
			wheel[(next + i) % REMINDER_LENGTH] = target;
			return target;
		}

		// otherwise find the one to be inserted before
		if (reminders[wheel[(next + i) % REMINDER_LENGTH]].scheduled_ms <= scheduled_ms)
			continue;
		replc = (next + i) % REMINDER_LENGTH;
	}
	if (replc == 255)
		return -3;
	// shift everything after it backwards
	i = 0;
	holding = target;
	while(holding != 255) {		// only break when an empty slot is replaced
		// if somehow it reached a loop, return -3
		if((replc + i) % REMINDER_LENGTH == next) {
			return -4;
		}

		// replace
		temp = wheel[(replc + i) % REMINDER_LENGTH];
		wheel[(replc + i) % REMINDER_LENGTH] = holding;
		holding = temp;
		i++;
	}

	// return index on success
	return target;
}

void __huansic_systick_update_irq(void) {
    microseconds++;
    if(microseconds >= 1000){
        milliseconds++;
        microseconds = 0;
    }
	// push the wheel
	if (wheel[next] < REMINDER_LENGTH) {
		while (reminders[wheel[next]].scheduled_ms <= milliseconds) {
			fp = reminders[wheel[next]].thread;		// store the function pointer
			// condition the reminder
			reminders[wheel[next]].thread = 0;
			reminders[wheel[next]].scheduled_ms = 0;
			wheel[next] = 255;
			next = (next + 1) % REMINDER_LENGTH;
			// call the thread
			if (fp) {
				fp(milliseconds);}
		}
	}
}


__attribute__((interrupt("WCH-Interrupt-fast"))) void SysTick_Handler(void) {
	if (SysTick->SR) {
		SysTick->SR = 0;
		__huansic_systick_update_irq();
	}
}
