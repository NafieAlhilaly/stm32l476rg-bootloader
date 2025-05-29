#include "commons-include.h"
#include <libopencm3/stm32/l4/flash.h>

#define FIRMWARE_PAGE_START  16 // Page is 2 KB (16 pages = 32 KB which is Bootloader size)
#define FIRMWARE_PAGE_END    500

void bl_flash_erase_firmware(void);
void bl_flash_write(const uint32_t address, uint8_t* data, uint32_t length);