#ifndef __PID_H
#define __PID_H

#include "ch32v30x.h"

float pid(int32_t now);
float pid_prop_update(int32_t goal, int32_t now);

#endif
