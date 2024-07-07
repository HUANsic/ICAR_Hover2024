/*
 * huansic_chronos.h
 *
 *  Created on: May 20, 2024
 *      Author: ZonghuanWu
 */

#ifndef USER_HUANSIC_CHRONOS_H_
#define USER_HUANSIC_CHRONOS_H_

#include "ch32v30x.h"

void huansic_chronos_init(void);

void huansic_delay_ms(uint32_t duration);

void huansic_delay_us(uint32_t duration);

uint32_t huansic_chronos_milliseconds(void);

int8_t huansic_chronos_schedule(uint32_t scheduled_ms, void (*thread)(uint32_t ms));

#endif /* USER_HUANSIC_CHRONOS_H_ */
