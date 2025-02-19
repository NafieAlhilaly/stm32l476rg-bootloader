#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/scb.h>
#include <stdio.h>
#include <errno.h>


#define BL_SIZE (0x8000U)


// States
#define DETECTING 0
#define LIGHT_ON 1
#define LIGHT_OFF 2

#define CPU_FREQ      (84000000)
#define SYSTICK_FREQ  (1000)
#define SENSOR_PIN_ID GPIO0
#define MOTION_SENSOR_PIN_ID GPIO9
#define RELAY_PIN GPIO7



void change_state(uint8_t new_state);