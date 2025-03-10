#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/vector.h>


#define BOOTLOADER_SIZE (0x8000U)
#define FIRMWARE_START_ADDRESS (FLASH_BASE + BOOTLOADER_SIZE)