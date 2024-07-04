/*
 * huansic_util.h
 *
 *  Created on: May 21, 2024
 *      Author: ZonghuanWu
 */

#ifndef USER_HUANSIC_UTIL_H_
#define USER_HUANSIC_UTIL_H_

#include "huansic_config.h"

#if defined(_HUAN_USE_V20X)
#include "ch32v20x.h"
#elif defined(_HUAN_USE_V20X)
#include "ch32v30x.h"
#endif

int32_t huansic_map(int32_t input, int32_t old_floor, int32_t old_ceil, int32_t new_floor, int32_t new_ceil);

void huansic_led_init();

void huansic_led1_set(float bri);

void huansic_led2_set(float bri);

void huansic_led1_turn();

void huansic_led2_turn();

#endif /* USER_HUANSIC_UTIL_H_ */
