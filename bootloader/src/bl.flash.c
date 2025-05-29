#include "bl.flash.h"

void bl_flash_erase_firmware(void) {
    flash_unlock();
    for(uint32_t i = FIRMWARE_PAGE_START; i <= FIRMWARE_PAGE_END; i++) {
        flash_erase_page(i);
        if (FLASH_SR & (FLASH_SR_PROGERR | FLASH_SR_WRPERR)) {
            flash_clear_status_flags();
        }
    }
    flash_lock();
}
void bl_flash_write(const uint32_t address, uint8_t *data, uint32_t length)
{
    flash_unlock();
    flash_program(address, data, length);
    flash_lock();
}