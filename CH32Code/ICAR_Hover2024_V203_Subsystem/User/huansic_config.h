/*
 * huansic_config.h
 *
 *  Created on: May 21, 2024
 *      Author: ZonghuanWu
 */

#ifndef USER_HUANSIC_CONFIG_H_
#define USER_HUANSIC_CONFIG_H_

#define _HUAN_USE_V20X

#if defined(_HUAN_USE_V20X)
#include "ch32v20x.h"
#elif defined(_HUAN_USE_V30X)
#include "ch32v30x.h"
#endif


#endif /* USER_HUANSIC_CONFIG_H_ */
