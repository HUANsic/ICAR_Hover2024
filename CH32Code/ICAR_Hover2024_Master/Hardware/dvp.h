#ifndef __DVP_H
#define __DVP_H

#include <ov.h>
#include "ch32v30x.h"

void DVP_Init(void);
uint8_t GetReadingFlag(void);
u8 GetGray_RGB565(u8 href, u8 row);
u8 GetGray_YUV422(u8 href, u8 row);
uint32_t get_fps_count();
void binarization(void);
void OLED_ShowCam();

#endif
