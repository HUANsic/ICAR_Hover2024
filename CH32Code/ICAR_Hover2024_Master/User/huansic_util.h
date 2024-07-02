/*
 * huansic_util.h
 *
 *  Created on: May 21, 2024
 *      Author: ZonghuanWu
 */

#ifndef USER_HUANSIC_UTIL_H_
#define USER_HUANSIC_UTIL_H_

#include "ch32v30x.h"

int32_t huansic_map(int32_t input, int32_t old_floor, int32_t old_ceil, int32_t new_floor, int32_t new_ceil);

void huansic_led_init();

void huansic_led1_set(float bri);

void huansic_led2_set(float bri);

void huansic_led3_set(float bri);

void huansic_led4_set(float bri);

void huansic_led5_set(float bri);

void huansic_led6_set(float bri);

void huansic_led7_set(float bri);

#endif /* USER_HUANSIC_UTIL_H_ */
