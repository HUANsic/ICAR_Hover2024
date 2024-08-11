/*
 * huansic_uitl.c
 *
 *  Created on: May 21, 2024
 *      Author: ZonghuanWu
 */

#include "huansic_util.h"

void util_init() {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOB, &GPIO_InitStructure);

	TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = SystemCoreClock / 1000000 - 1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit( TIM3, &TIM_TimeBaseInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;	// turn off for now
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init( TIM3, &TIM_OCInitStructure);
	TIM_OC4Init( TIM3, &TIM_OCInitStructure);

	TIM_CtrlPWMOutputs(TIM3, ENABLE);
	TIM_OC3PreloadConfig( TIM3, TIM_OCPreload_Disable);
	TIM_OC4PreloadConfig( TIM3, TIM_OCPreload_Disable);
	TIM_ARRPreloadConfig( TIM3, ENABLE);
	TIM_Cmd( TIM3, ENABLE);
}

void util_led1_set(float bri) {
	if (bri < 0)
		bri = 0;
	if (bri > 1)
		bri = 1;
	TIM3->CH3CVR = (uint16_t) (bri * 1000);
}

void util_led2_set(float bri) {
	if (bri < 0)
		bri = 0;
	if (bri > 1)
		bri = 1;
	TIM3->CH4CVR = (uint16_t) (bri * 1000);
}
