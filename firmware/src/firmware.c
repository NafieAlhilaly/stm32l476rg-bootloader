#include "firmware.h"

static void usart_setup(void)
{
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

  /* Finally enable the USART. */
  usart_enable(USART2);
}

int _write(int file, char *ptr, int len)
{
  int i;

  if (file == 1)
  {
    for (i = 0; i < len; i++)
    {
      if (ptr[i] == '\n')
      {
        usart_send_blocking(USART2, '\r');
      }
      usart_send_blocking(USART2, ptr[i]);
    }
    return i;
  }
  errno = EIO;
  return -1;
}


void vector_setup(void){
  SCB_VTOR = BL_SIZE;
}

static volatile uint64_t ticks = 0;

void sys_tick_handler(void)
{
  ticks++;
}

static void systick_setup(void)
{
  systick_set_frequency(SYSTICK_FREQ, CPU_FREQ);
  systick_counter_enable();
  systick_interrupt_enable();
}

uint64_t get_ticks(void)
{
  return ticks;
}

void delay_ms(uint64_t milleseconds)
{
  uint64_t end_time = get_ticks() + milleseconds;
  while (get_ticks() < end_time)
    ;
}

void clock_setup()
{
  rcc_clock_setup_pll(&rcc_hsi16_configs[RCC_CLOCK_VRANGE1_80MHZ]);
}
int main(void)
{
  vector_setup();
  clock_setup();
  usart_setup();
  printf("Start main \n");
  while (1)
  {
    printf("Firmware is running! \n");
    delay_ms(5000);
  }
  return 0;
}