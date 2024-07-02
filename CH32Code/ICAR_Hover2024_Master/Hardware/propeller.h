#ifndef __PROPELLER_H
#define __PROPELLER_H

#include "ch32v30x.h"

void Propeller_Init(void);
void Propeller_Enable(void);
void Propeller1_Duty(int16_t duty);
void Propeller2_Duty(int16_t duty);

#endif
