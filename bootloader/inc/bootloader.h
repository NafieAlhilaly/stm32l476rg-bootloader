#include <libopencm3/stm32/rcc.h>
#include <libopencm3/cm3/scb.h>


#define BOOTLOADER_SIZE (0x8000U)
#define FIRMWARE_START_ADDRESS (FLASH_BASE + BOOTLOADER_SIZE)
#define VECTOR_TABLE_ENTRY_LENGTH (4U)

typedef void (*void_fn)(void);
void jump_to_firmware(void);