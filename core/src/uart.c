#include "uart.h"

static ring_buffer_t uart_rb = {0U};
static uint8_t uart_buffer[RING_BUFFER_SIZE] = {0U};

void uart_setup(void)
{
  // Set up ring buffer
  ring_buffer_setup(&uart_rb, &uart_buffer, RING_BUFFER_SIZE - 1);

  /* Enable clocks for GPIO port A (for GPIO_USART2_TX) and USART2. */
  rcc_periph_clock_enable(RCC_USART2);
  rcc_periph_clock_enable(RCC_GPIOA);

  /* Setup GPIO pin GPIO_USART2_TX/GPIO9 on GPIO port A for transmit. */
  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2 | GPIO3);
  gpio_set_af(GPIOA, GPIO_AF7, GPIO2 | GPIO3);

  /* Setup UART parameters. */
  usart_set_baudrate(USART2, 115200);
  usart_set_databits(USART2, 8);
  usart_set_stopbits(USART2, USART_STOPBITS_1);
  usart_set_mode(USART2, USART_MODE_TX_RX);
  usart_set_parity(USART2, USART_PARITY_NONE);
  usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

  usart_enable_rx_interrupt(USART2);
  nvic_enable_irq(NVIC_USART2_IRQ);
  usart_enable(USART2);
}

void usart2_isr(void){
  if(usart_get_flag(USART2, USART_FLAG_ORE) || usart_get_flag(USART2, USART_FLAG_RXNE)){
    ring_buffer_write(&uart_rb, (uint8_t)usart_recv(USART2));
  }
}

void uart_write(uint8_t* data, const uint32_t length){
  for(uint32_t i = 0; i < length; i++){
    uart_write_byte(data[i]);
  }
}
void uart_write_byte(uint8_t data){
  usart_send_blocking(USART2, (uint16_t)data);
}
uint32_t uart_read(uint8_t* data, uint32_t length){
  if (length == 0){
    return 0;
  }

  for(uint32_t bytes_read = 0; bytes_read < length; bytes_read++){
    if(!ring_buffer_read(&uart_rb, &data[bytes_read])){

    }
  }

  return length;
}
uint8_t uart_read_byte(void){
  uint8_t byte = 0;
  uart_read(&byte, 1);
  return byte;
}
bool uart_data_available(void){
 return !ring_buffer_empty(&uart_rb); 
}