#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sdata;
extern uint32_t _sidata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern int main(void);
extern void SysTick_Handler(void);
void Reset_Handler(void);

uint32_t vectors[16] __attribute__((section(".isr_vector"))) = {
    (uint32_t) &_estack, (uint32_t) Reset_Handler, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (uint32_t)SysTick_Handler
};


void Reset_Handler(void) {
  uint32_t* data_ram_ptr = &_sdata;
  uint32_t* data_flash_ptr = &_sidata;

  while (data_ram_ptr < &_edata) {
    *data_ram_ptr = *data_flash_ptr;
    data_ram_ptr++;
    data_flash_ptr++;
  }

  uint32_t* bss_ptr = &_sbss;

  while (bss_ptr < &_ebss) {
    *bss_ptr = 0;
    bss_ptr++;
  }

  main();
}