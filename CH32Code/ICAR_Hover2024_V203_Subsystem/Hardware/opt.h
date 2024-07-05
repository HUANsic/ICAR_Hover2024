#ifndef __OPT__H
#define __OPT__H

#include "ch32v20x.h"

typedef struct {
    int8_t front_dx;
    int8_t front_dy;
    int8_t rear_dx;
    int8_t rear_dy;
} opt_data_typedef;

void opt_init(void);
void fopt_resync();
void ropt_resync(void);
uint8_t fopt_id(void);
uint8_t ropt_id(void);
opt_data_typedef get_opt_data(void);

#endif
