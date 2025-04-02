#include <stdint.h>

#define COUNTER_DELAY 100000000  // might need to change based on real hardware
#define TIMER_BASE ((volatile uint32_t *)0xFF202000)
#define HEX_BASE1 ((volatile uint32_t *)0xff200020)
#define HEX_BASE2 ((volatile uint32_t *)0xff200030)

const uint8_t BIT_CODES[10] = {
    0b0111111, 0b0000110, 0b1011011, 0b1001111, 0b1100110,
    0b1101101, 0b1111101, 0b0000111, 0b1111111, 0b1100111,
};

void delay() {
  volatile uint32_t *timer = TIMER_BASE;
  timer[0] = 0;
  timer[2] = COUNTER_DELAY & 0xFFFF;
  timer[3] = (COUNTER_DELAY >> 16) & 0xFFFF;
  timer[1] = 0b0110;

  while (!(timer[0] & 0x1));
  timer[0] = 0;
}

void HEX_DISP(uint32_t value) {
  volatile uint32_t *hex1 = HEX_BASE1;
  volatile uint32_t *hex2 = HEX_BASE2;

  uint32_t display_value1 = BIT_CODES[0];
  if (value == 10) {
    display_value1 = BIT_CODES[1];
  }
  uint32_t display_value0 = BIT_CODES[value % 10];
  uint32_t display_value = display_value0 + (display_value1 << 8);
  *hex1 = display_value;
  *hex2 = 0;
}

int main() {
  uint32_t counter = 10;

  while (counter > 0) {
    HEX_DISP(counter);
    delay();
    counter--;
  }

  HEX_DISP(0);
  return 0;
}
