#include <stdint.h>

volatile unsigned int* rcc_register = (volatile unsigned int*)0x40023830;
volatile unsigned int* gpioa_moder = (volatile unsigned int*)0x40020000;
volatile unsigned int* gpioa_odr = (volatile unsigned int*)0x40020014;
volatile unsigned int* stk_reg = (volatile unsigned int*)0xE000E010;
volatile unsigned int* stk_load = (volatile unsigned int*)0xE000E014;

int main(void) {
  *rcc_register |= 0x00000001;
  *gpioa_moder |= (1 << 10);
  *gpioa_odr |= (1 << 5);

  *stk_load = 16000000;
  *stk_reg |= (1) | (1 << 2);

  while (1) {
    *gpioa_odr ^= (1 << 5);
    while (((*stk_reg >> 16) & 0x01) == 0) {
    }
  }
  return 0;
}