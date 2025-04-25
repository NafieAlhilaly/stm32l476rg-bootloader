#!/bin/bash
# 
# Dump flash memory content to a `DUMP_FILE_NAME` using `OpenOCD`.
#

INTERFACE="interface/stlink.cfg"
TARGET_DEVICE="target/stm32l4x.cfg"
DUMP_FILE_NAME="flash_dump.bin"
START_ADDRESS="0x0808000"
SIZE="0x800"
DUMP_COMMAND="dump_image $DUMP_FILE_NAME $START_ADDRESS  $SIZE"

echo "Info : running 'openocd -f $INTERFACE -f $TARGET_DEVICE -c "init" -c '$DUMP_COMMAND' -c "exit"'"
openocd -f $INTERFACE -f $TARGET_DEVICE -c "init" -c "$DUMP_COMMAND" -c "exit"