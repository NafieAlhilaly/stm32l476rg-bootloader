#include "bl.flash.h"

void bl_flash_erase_firmware(void)
{
    flash_unlock();
    for(uint8_t i = FIRMAWARE_PAGE_START; i <= FIRMAWARE_PAGE_END; i++){
        flash_erase_page(i);
    }
    flash_lock();
}
void bl_flash_write(const uint32_t address, uint8_t *data, uint32_t length)
{
    flash_unlock();
    flash_program(address, data, length);
    flash_lock();
}