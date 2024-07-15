#ifndef __IMG_PROCESS__H
#define __IMG_PROCESS__H

#include "ch32v30x.h"
#include "ov.h"

uint16_t GetOSTU (uint8_t tmImage[IMGH][IMGW]);

extern uint16_t threhold;
extern uint32_t Image_Gray_Address;
extern uint32_t Image_Gray_Address;

extern uint8_t  Image_Gray[IMGH][IMGW];
extern uint8_t  Image_Bin[IMGH][IMGW];
void threhold_update();
void Bin_Image_Filter();
int32_t get_err();  //×ó¼õÓÒ

#endif
