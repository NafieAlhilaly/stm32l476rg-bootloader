#include "commons-include.h"
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>

#define CPU_FREQ      (84000000)
#define SYSTICK_FREQ  (1000)

void sys_tick_handler(void);
void systick_setup(void);
uint64_t get_ticks(void);
void delay_ms(uint64_t milleseconds);