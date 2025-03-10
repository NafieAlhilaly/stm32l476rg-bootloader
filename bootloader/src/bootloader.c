#include "bootloader.h"


int main(void){
  vector_table_t* reset_vector = (vector_table_t*)FIRMWARE_START_ADDRESS;
  reset_vector->reset();  
  return 0;
}