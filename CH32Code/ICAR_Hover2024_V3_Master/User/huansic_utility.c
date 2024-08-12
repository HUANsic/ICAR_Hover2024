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

#if defined SYSCLK_FREQ_96MHz_HSE
static void HUANsic_SetSysClockTo96_HSE(void);
#elif defined SYSCLK_FREQ_120MHz_HSE
static void HUANsic_SetSysClockTo120_HSE(void);
#elif defined SYSCLK_FREQ_144MHz_HSE
static void HUANsic_SetSysClockTo144_HSE(void);
#endif

void Utility_Init(void) {
	//	copied from system_ch32v30x.c -> SystemInit(void)
	RCC->CTLR |= (uint32_t) 0x00000001;
	RCC->CFGR0 &= (uint32_t) 0xF0FF0000;
	RCC->CTLR &= (uint32_t) 0xFEF6FFFF;
	RCC->CTLR &= (uint32_t) 0xFFFBFFFF;
	RCC->CFGR0 &= (uint32_t) 0xFF00FFFF;
	RCC->CTLR &= (uint32_t) 0xEBFFFFFF;
	RCC->INTR = 0x00FF0000;
	RCC->CFGR2 = 0x00000000;

#if defined SYSCLK_FREQ_96MHz_HSE
	HUANsic_SetSysClockTo96_HSE();
#elif defined SYSCLK_FREQ_120MHz_HSE
	HUANsic_SetSysClockTo120_HSE();
#elif defined SYSCLK_FREQ_144MHz_HSE
	HUANsic_SetSysClockTo144_HSE();
#endif

	SystemCoreClockUpdate();

	Utility_Time_Init();
	Utility_Serial_Init();
	Utility_LED_Init();
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
	uint32_t i;
	/*
	 li      a5,0
	 0000027e:   bltu    a5,a0,0x284 <Utility_Time_DelayUs+8>
	 00000282:   ret
	 48       		__asm__("nop");
	 00000284:   nop
	 49       		__asm__("nop");
	 00000286:   nop
	 50       		__asm__("nop");
	 00000288:   nop
	 0000028a:   addi    a5,a5,1
	 0000028c:   andi    a5,a5,255
	 00000290:   j       0x27e <Utility_Time_DelayUs+2>
	 */
	for (i = 0; i < duration; i++) {
		// 4 instruction cycles in the "for" loop frame
		// so there should be SystemClock (in MHz) - 4 number of nop if i is not uint32
		// if i is uint32, then SystemClock (in MHz) - 3 number of nop
		// for some reason, it's only 2/3 of the duration
//		__asm__("nop");
//		__asm__("nop");
//		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
//		__asm__("nop");
//		__asm__("nop");
//		__asm__("nop");		// for some reasons we lost three cycles... maybe lost in branching

		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

#if !(defined( SYSCLK_FREQ_48MHz_HSE) || defined(SYSCLK_FREQ_48MHz_HSI))
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

#if !(defined( SYSCLK_FREQ_56MHz_HSE) || defined(SYSCLK_FREQ_56MHz_HSI))
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

#if !(defined( SYSCLK_FREQ_72MHz_HSE) || defined(SYSCLK_FREQ_72MHz_HSI))
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

#if !(defined( SYSCLK_FREQ_96MHz_HSE) || defined(SYSCLK_FREQ_96MHz_HSI))
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

#if !(defined( SYSCLK_FREQ_120MHz_HSE) || defined(SYSCLK_FREQ_120MHz_HSI))
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");
		__asm__("nop");

#if !(defined( SYSCLK_FREQ_144MHz_HSE) || defined(SYSCLK_FREQ_144MHz_HSI))
#error "Delay_us not supported. HSI and HSE are not supported. Please define SYSCLK_FREQ_... in ch32v30x_conf.h."
#endif	// #if !(defined( SYSCLK_FREQ_144MHz_HSE) || defined(SYSCLK_FREQ_144MHz_HSI))
#endif	// #if !(defined( SYSCLK_FREQ_120MHz_HSE) || defined(SYSCLK_FREQ_120MHz_HSI))
#endif	// #if !(defined( SYSCLK_FREQ_96MHz_HSE) || defined(SYSCLK_FREQ_96MHz_HSI))
#endif	// #if !(defined( SYSCLK_FREQ_72MHz_HSE) || defined(SYSCLK_FREQ_72MHz_HSI))
#endif	// #if !(defined( SYSCLK_FREQ_56MHz_HSE) || defined(SYSCLK_FREQ_56MHz_HSI))
#endif	// #if !(defined( SYSCLK_FREQ_48MHz_HSE) || defined(SYSCLK_FREQ_48MHz_HSI))
	}
}

#if defined SYSCLK_FREQ_96MHz_HSE

/*********************************************************************
 * @fn      SetSysClockTo96_HSE
 *
 * @brief   Sets System clock frequency to 96MHz and configure HCLK, PCLK2 and PCLK1 prescalers.
 *
 * @return  none
 */
static void HUANsic_SetSysClockTo96_HSE(void)
{
	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;

	RCC->CTLR |= ((uint32_t)RCC_HSEON);

	/* Wait till HSE is ready and if Time out is reached exit */
	do
	{
		HSEStatus = RCC->CTLR & RCC_HSERDY;
		StartUpCounter++;
	}while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

	if ((RCC->CTLR & RCC_HSERDY) != RESET)
	{
		HSEStatus = (uint32_t)0x01;
	}
	else
	{
		HSEStatus = (uint32_t)0x00;
	}

	if (HSEStatus == (uint32_t)0x01)
	{
		/* HCLK = SYSCLK */
		RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;
		/* PCLK2 = HCLK */
		RCC->CFGR0 |= (uint32_t)RCC_PPRE2_DIV1;
		/* PCLK1 = HCLK */
		RCC->CFGR0 |= (uint32_t)RCC_PPRE1_DIV2;

		/*  PLL configuration: PLLCLK = HSE * 8 = 96 MHz */
		RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC | RCC_PLLXTPRE |
						RCC_PLLMULL));

#ifdef CH32V30x_D8
		RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL8);
#else
		RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL8_EXTEN);
#endif

		/* Enable PLL */
		RCC->CTLR |= RCC_PLLON;
		/* Wait till PLL is ready */
		while((RCC->CTLR & RCC_PLLRDY) == 0)
		{
		}
		/* Select PLL as system clock source */
		RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
		RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;
		/* Wait till PLL is used as system clock source */
		while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08)
		{
		}
	}
	else
	{
		/*
		 * If HSE fails to start-up, the application will have wrong clock
		 * configuration. User can add here some code to deal with this error
		 */
	}
}

#elif defined SYSCLK_FREQ_120MHz_HSE

/*********************************************************************
 * @fn      SetSysClockTo120_HSE
 *
 * @brief   Sets System clock frequency to 120MHz and configure HCLK, PCLK2 and PCLK1 prescalers.
 *
 * @return  none
 */
static void HUANsic_SetSysClockTo120_HSE(void)
{
	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;

	RCC->CTLR |= ((uint32_t)RCC_HSEON);

	/* Wait till HSE is ready and if Time out is reached exit */
	do
	{
		HSEStatus = RCC->CTLR & RCC_HSERDY;
		StartUpCounter++;
	}while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

	if ((RCC->CTLR & RCC_HSERDY) != RESET)
	{
		HSEStatus = (uint32_t)0x01;
	}
	else
	{
		HSEStatus = (uint32_t)0x00;
	}

	if (HSEStatus == (uint32_t)0x01)
	{
		/* HCLK = SYSCLK */
		RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;
		/* PCLK2 = HCLK */
		RCC->CFGR0 |= (uint32_t)RCC_PPRE2_DIV1;
		/* PCLK1 = HCLK */
		RCC->CFGR0 |= (uint32_t)RCC_PPRE1_DIV2;

		/*  PLL configuration: PLLCLK = HSE * 10 = 120 MHz */
		RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC | RCC_PLLXTPRE |
						RCC_PLLMULL));

#ifdef CH32V30x_D8
		RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL10);
#else
		RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL10_EXTEN);
#endif

		/* Enable PLL */
		RCC->CTLR |= RCC_PLLON;
		/* Wait till PLL is ready */
		while((RCC->CTLR & RCC_PLLRDY) == 0)
		{
		}
		/* Select PLL as system clock source */
		RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
		RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;
		/* Wait till PLL is used as system clock source */
		while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08)
		{
		}
	}
	else
	{
		/*
		 * If HSE fails to start-up, the application will have wrong clock
		 * configuration. User can add here some code to deal with this error
		 */
	}
}

#elif defined SYSCLK_FREQ_144MHz_HSE

/*********************************************************************
 * @fn      SetSysClockTo144_HSE
 *
 * @brief   Sets System clock frequency to 144MHz and configure HCLK, PCLK2 and PCLK1 prescalers.
 *
 * @return  none
 */
static void HUANsic_SetSysClockTo144_HSE(void)
{
	__IO uint32_t StartUpCounter = 0, HSEStatus = 0;

	RCC->CTLR |= ((uint32_t) RCC_HSEON);

	/* Wait till HSE is ready and if Time out is reached exit */
	do
	{
		HSEStatus = RCC->CTLR & RCC_HSERDY;
		StartUpCounter++;
	} while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

	if ((RCC->CTLR & RCC_HSERDY) != RESET)
			{
		HSEStatus = (uint32_t) 0x01;
	}
	else
	{
		HSEStatus = (uint32_t) 0x00;
	}

	if (HSEStatus == (uint32_t) 0x01)
			{
		/* HCLK = SYSCLK */
		RCC->CFGR0 |= (uint32_t) RCC_HPRE_DIV1;
		/* PCLK2 = HCLK */
		RCC->CFGR0 |= (uint32_t) RCC_PPRE2_DIV1;
		/* PCLK1 = HCLK */
		RCC->CFGR0 |= (uint32_t) RCC_PPRE1_DIV2;

		/*  PLL configuration: PLLCLK = HSE * 12 = 144 MHz */
		RCC->CFGR0 &= (uint32_t) ((uint32_t) ~(RCC_PLLSRC | RCC_PLLXTPRE |
		RCC_PLLMULL));

#ifdef CH32V30x_D8
		RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL12);
#else
		RCC->CFGR0 |= (uint32_t) (RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL12_EXTEN);
#endif

		/* Enable PLL */
		RCC->CTLR |= RCC_PLLON;
		/* Wait till PLL is ready */
		while((RCC->CTLR & RCC_PLLRDY) == 0)
		{
		}
		/* Select PLL as system clock source */
		RCC->CFGR0 &= (uint32_t) ((uint32_t) ~(RCC_SW));
		RCC->CFGR0 |= (uint32_t) RCC_SW_PLL;
		/* Wait till PLL is used as system clock source */
		while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08)
		{
		}
	}
	else
	{
		/*
		 * If HSE fails to start-up, the application will have wrong clock
		 * configuration. User can add here some code to deal with this error
		 */
	}
}
#endif

void SysTick_Handler(void) {
	SysTick->SR = 0;
	millis++;
}

/**
 * 		Serial communication via CH340 to computer
 */

uint8_t* _util_serial_rx_ptr, *_util_serial_tx_ptr;
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

void Utility_LED_Init(void) {
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

void Utility_LED_Set(LED_INDEX_E leds, float bri) {
	if (bri < 0)
		bri = 0;
	if (bri > 1)
		bri = 1;
	if (leds & LED1)
		TIM3->CH3CVR = (uint16_t) (bri * 1000);
	if (leds & LED2)
		TIM3->CH4CVR = (uint16_t) (bri * 1000);
}
