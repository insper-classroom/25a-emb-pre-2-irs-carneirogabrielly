#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int BTN_PIN_G = 26;
const int LED_R = 4;
const int LED_G = 6;
volatile int FLAG_R;
volatile int FLAG_G;


void btn_callback(uint gpio, uint32_t events)
{
  if (events == 0x4)
  { // fall edge
    if (gpio == BTN_PIN_R)
    {
      FLAG_R = 1;
    }
  }
  else if (events == 0x8)
  { // rise edge
    if (gpio == BTN_PIN_G)
    {
      FLAG_G = 1;
    }
  }
}

int main()
{
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  // callback led r (first)
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);

  // callback led g (nao usar _with_callback)
  gpio_set_irq_enabled_with_callback(BTN_PIN_G, GPIO_IRQ_EDGE_RISE, true, &btn_callback);

  gpio_init(LED_R);
  gpio_set_dir(LED_R, GPIO_OUT);
  gpio_init(LED_G);
  gpio_set_dir(LED_G, GPIO_OUT);

  int led_status_r = 0;
  int led_status_g = 0;

  while (true)
  {
    if (FLAG_R)
    {
      led_status_r = !led_status_r;
      gpio_put(LED_R, led_status_r);
      FLAG_R = 0;
    }
    if (FLAG_G)
    {
      led_status_g = !led_status_g;
      gpio_put(LED_G, led_status_g);
      FLAG_G = 0;
    }
  }
}
