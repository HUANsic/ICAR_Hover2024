#ifndef __DVP_H
#define __DVP_H

#include <ov.h>
#include "ch32v30x.h"
#include "uart5.h"

void DVP_Init(void);
u8 GetGray_RGB565(u8 href, u8 row);
u8 GetGray_YUV422(u8 href, u8 row);

#endif
