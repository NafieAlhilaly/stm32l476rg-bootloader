# STM32L4 Bootloader

Bootloader implementation for the STM32L4 microcontroller using Libopencm3. It facilitates firmware updates via UART by receiving, validating, and programming firmware images into the device's flash memory.

## Overview
- **UART**: The bootloader communicates over UART to receive firmware images in chunks.
- **Packet Protocol**: A packet-based protocol ensures data integrity during transmission over UART. Each packet is checked for correctness before processing.
- **CRC**: The bootloader verifies the integrity of the entire firmware image using a CRC check to ensure it is free from corruption.
- **Flash Memory Programming**: Validated firmware chunks are sequentially written to the microcontroller's flash memory.

## References
- [STM32L4 Reference Manual](https://www.st.com/resource/en/reference_manual/rm0351-stm32l47xxx-stm32l48xxx-stm32l49xxx-and-stm32l4axxx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [Libopencm3 Documentation](https://github.com/libopencm3/libopencm3)
- [Bare-Metal Programming series on Youtube](https://www.youtube.com/playlist?list=PLP29wDx6QmW7HaCrRydOnxcy8QmW0SNdQ)