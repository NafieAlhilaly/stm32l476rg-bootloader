#include "bootloader.h"


void jump_to_firmware(){
  uint32_t* reset_vector_entry = (uint32_t*)(FIRMWARE_START_ADDRESS + VECTOR_TABLE_ENTRY_LENGTH);
  uint32_t* reset_vector       = (uint32_t*)(*reset_vector_entry);
  void_fn jump_fn              = (void_fn)reset_vector;
  jump_fn();
}

int main(void){
  jump_to_firmware();
  return 0;
}