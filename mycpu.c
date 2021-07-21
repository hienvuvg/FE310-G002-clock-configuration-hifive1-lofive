#include <stdint.h>
#include <metal/machine.h>
#include "mycpu.h"

uint32_t cpu_freq(void)
{
    return metal_clock_get_rate_hz(&__metal_dt_clock_4.clock);
}

void delay(uint32_t counter)
{
    volatile uint32_t i = 0;
    while (i < counter) {
        i++;
    }
}

// Supported clock: 64, 128, 256, 320 MHz
int cpu_clock_config(int frequency) {

    uint32_t cfg_temp = 0;

    if (frequency != 64 && frequency != 128 && frequency != 256 && frequency != 320) return 0;

    if (frequency == 320){
		/* There is a 16 MHz crystal oscillator HFXOSC on the board */
		cfg_temp |= BITS(PLLREFSEL_I, 1);     // Drive PLL from 16 MHz HFXOSC
		cfg_temp |= BITS(PLLR_I, PLLR_2);     // Divide ratio. R=2 for 8 MHz out
		cfg_temp |= BITS(PLLF_I, 80/2 - 1U);  // Multiply ratio. 8 MHz x 40 is 640 MHz out
		cfg_temp |= BITS(PLLQ_I, PLLQ_2);     // Divide 640MHz with 2 to get 320 MHz
		// PLLSEL_I = 0    : PLL is not driving hfclk for now
		// PLLBYPASS_I = 0 : Enables PLL
		PLLCFG = cfg_temp;
    }
    else{
		/* There is a 16 MHz crystal oscillator HFXOSC on the board */
		cfg_temp |= BITS(PLLREFSEL_I, 1);     	// Drive PLL from 16 MHz HFXOSC.

		cfg_temp |= BITS(PLLR_I, 1U);     		// Divide ratio.
												// R="1U" is treated as a divide ratio of 2.
												// This gives 16MHz / 2 = 8MHz.
												// This is within range for refr.

		cfg_temp |= BITS(PLLF_I, 31U);  		// Multiply ratio.
												// F="31U" gives a multiply ratio of 2 * ("31U" + 1) = 64.
												// This gives 8MHz * 64 = 512MHz.
												// This is within range for vco.

		if (frequency == 256) cfg_temp |= BITS(PLLQ_I, 1U);     		// Divide again.
												// Q="2U" gives a division ratio of 4.
												// This gives 512MHz / 1 = 256MHz.
												// This is within range for pllout.
		if (frequency == 128) cfg_temp |= BITS(PLLQ_I, 2U);     		// Divide again.
												// Q="2U" gives a division ratio of 4.
												// This gives 512MHz / 4 = 128MHz.
												// This is within range for pllout.

		if (frequency == 64) cfg_temp |= BITS(PLLQ_I, 3U);     		// Divide again.
												// Q="3U" gives a division ratio of 8.
												// This gives 512MHz / 8 = 64MHz.
												// This is within range for pllout.
		PLLCFG = cfg_temp;
    }

    delay(1000);

    while ( PLLCFG & BITS(PLLLOCK_I, 1) == 0) {} // Wait until PLL locks
    PLLCFG |= BITS(PLLSEL_I, 1);          // Let PLL drive hfclk

    return 1;
}
