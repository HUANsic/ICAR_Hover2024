/*
 * huansic_irq.h
 *
 *  Created on: May 20, 2024
 *      Author: ZonghuanWu
 */

#ifndef USER_HUANSIC_IRQ_H_
#define USER_HUANSIC_IRQ_H_

#include "huansic_config.h"

#if defined(_HUAN_USE_V20X)
#include "ch32v20x.h"
#elif defined(_HUAN_USE_V30X)
#include "ch32v30x.h"
#endif

void __huansic_systick_update_irq(void);

#endif /* USER_HUANSIC_IRQ_H_ */
