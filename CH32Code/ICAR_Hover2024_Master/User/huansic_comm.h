/*
 * huansic_comm.h
 *
 *  Created on: May 21, 2024
 *      Author: ZonghuanWu
 */

#ifndef USER_HUANSIC_COMM_H_
#define USER_HUANSIC_COMM_H_

#include "ch32v30x.h"

typedef struct {
    int16_t front_dx;
    int16_t front_dy;
    int16_t rear_dx;
    int16_t rear_dy;
    uint32_t front_interval;
    uint32_t rear_interval;
} opt_data_typedef;

void huansic_subsys_init();
uint8_t get_opt_data_flag(void);
opt_data_typedef get_opt_data(void);
uint8_t get_subsys_data_flag(void);
uint8_t get_subsys_data(void);
void UART7_SendByte(uint8_t);

#endif /* USER_HUANSIC_COMM_H_ */
