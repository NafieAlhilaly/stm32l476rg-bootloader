#include "system.h"

static volatile uint64_t ticks = 0;

void sys_tick_handler(void)
{
  ticks++;
}

void systick_setup(void)
{
  systick_set_frequency(SYSTICK_FREQ, CPU_FREQ);
  systick_counter_enable();
  systick_interrupt_enable();
}

uint64_t get_ticks(void)
{
  return ticks;
}

void delay_ms(uint64_t milleseconds)
{
  uint64_t end_time = get_ticks() + milleseconds;
  while (get_ticks() < end_time)
    ;
}