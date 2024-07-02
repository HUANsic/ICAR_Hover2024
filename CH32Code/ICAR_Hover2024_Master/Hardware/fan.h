#ifndef __FAN_H
#define __FAN_H

#include "ch32v30x.h"

void Fan_Init();
void Fan1_Duty(uint8_t duty);
void Fan2_Duty(uint8_t duty);

#endif
