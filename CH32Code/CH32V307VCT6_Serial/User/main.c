#include "ch32v30x.h"
#include "huansic_util.h"
#include "huansic_chronos.h"
#include "huansic_serial.h"

void main(void) {
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();

	util_init();
	chronos_init();
	serial_init();

	while(1) {
		util_led_set(LED2, 1);
		delay_ms(500);
		util_led_set(LED2, 0);
		delay_ms(500);
	}
}
