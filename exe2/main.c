#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int LED_R = 4;
volatile int flag_press;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    flag_press = 1;
  } else if (events == 0x8) { // rise edge 
  }
}

int main() {
  stdio_init_all();
  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);
  gpio_set_irq_enabled_with_callback(
    BTN_PIN_R, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  
  gpio_init(LED_R);
  gpio_set_dir(LED_R, GPIO_OUT);

  int led_status = 0;
  while (true) {
    if (flag_press) {
      flag_press = 0;
      led_status = !led_status;
      gpio_put(LED_R, led_status);
    }

  }
}
