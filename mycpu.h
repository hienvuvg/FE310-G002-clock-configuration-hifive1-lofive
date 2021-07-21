#ifndef CPU_H__
#define CPU_H__

#include <stdint.h>

// METAL_SIFIVE_FE310_G000_PRCI_10008000_BASE_ADDRESS is defined in
// <metal/machine/platform.h> but that's not used here (who would
// want to use a decimal number for an address?)
#define PLLCFG          *(volatile uint32_t*)0x10008008
#define BITS(idx, val)  ((val) << (idx))

#define PLLR_2 1
#define PLLQ_2 1

// PLLCFG register bit indexes
#define PLLR_I        0U
#define PLLF_I        4U
#define PLLQ_I        10U
#define PLLSEL_I      16U
#define PLLREFSEL_I   17U
#define PLLBYPASS_I   18U
#define PLLLOCK_I     31U

uint32_t cpu_freq(void);
void delay(uint32_t counter);
int cpu_clock_config(int frequency);

#endif
