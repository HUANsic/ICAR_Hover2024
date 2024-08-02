#include "ch32v30x.h"
#include "huansic_util.h"

void delay(uint16_t ms);

void main(void) {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();

	util_init();

	while(1) {
		util_led_set(LED2, 1);
		delay(500);
		util_led_set(LED2, 0);
		delay(500);
	}
}

void delay(uint16_t ms) {
	uint32_t i, j;
	for (i = 0; i < ms; i++) {
		for (j = 0; j < 19800 - 1; j++) {
			__asm__("nop");		// assume 5-cycle for loop
		}
	}
}

