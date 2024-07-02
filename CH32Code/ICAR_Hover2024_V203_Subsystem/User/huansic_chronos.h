/*
 * huansic_chronos.h
 *
 *  Created on: May 20, 2024
 *      Author: ZonghuanWu
 */

#ifndef USER_HUANSIC_CHRONOS_H_
#define USER_HUANSIC_CHRONOS_H_

#include "huansic_config.h"
#include "huansic_irq.h"

void huansic_chronos_init(void);

void huansic_delay_ms(uint16_t duration);

void huansic_delay_us(uint16_t duration);

uint32_t huansic_chronos_seconds(void);

uint32_t huansic_chronos_milliseconds(void);

int8_t huansic_chronos_schedule(uint32_t scheduled_second, uint16_t scheduled_ms, void (*thread)(uint32_t sec, uint16_t ms));

#endif /* USER_HUANSIC_CHRONOS_H_ */
