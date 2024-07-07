#ifndef __OPT__H
#define __OPT__H

#include "ch32v20x.h"

typedef struct {
    int16_t front_dx;
    int16_t front_dy;
    int16_t rear_dx;
    int16_t rear_dy;
    uint32_t front_interval;
    uint32_t rear_interval;
} opt_data_typedef;

void opt_init(void);
void fopt_resync();
void ropt_resync(void);
uint8_t fopt_id(void);
uint8_t ropt_id(void);
void refresh_opt_data(void);
void reset_opt_data(void);
opt_data_typedef get_opt_data(void);

#endif
