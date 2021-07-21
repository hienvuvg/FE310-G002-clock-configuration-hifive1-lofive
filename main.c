/* Copyright 2019 SiFive, Inc */
/* SPDX-License-Identifier: Apache-2.0 */

#include <stdio.h>

#include <metal/machine.h>
#include <metal/gpio.h>
#include "mycpu.h"
#include "myuart.h"

#define GPIO_PIN_9 9
#define GPIO_PIN_18 18
#define GPIO_PIN_22 22

struct metal_gpio *gpio;

unsigned int cpu_clock;
int print_mode = 0, count = 0;


void GPIOSetup(){
	gpio = metal_gpio_get_device(0);

	metal_gpio_disable_input(gpio, GPIO_PIN_9);
	metal_gpio_disable_input(gpio, GPIO_PIN_18);
	metal_gpio_disable_output(gpio, GPIO_PIN_22);

	metal_gpio_disable_pinmux(gpio, GPIO_PIN_9);
	metal_gpio_disable_pinmux(gpio, GPIO_PIN_18);
	metal_gpio_disable_pinmux(gpio, GPIO_PIN_22);

	metal_gpio_enable_output(gpio, GPIO_PIN_9);
	metal_gpio_enable_output(gpio, GPIO_PIN_18);
	metal_gpio_enable_input(gpio, GPIO_PIN_22);
}

int main() {
	cpu_clock_config(64);
	uart_init(BAUDRATE_115200);
	
	cpu_clock = metal_clock_get_rate_hz(&__metal_dt_clock_4.clock);
	printf("Clock frequency: %d\n", cpu_clock);
				
	GPIOSetup();

	while(1){


		if(!metal_gpio_get_input_pin(gpio, GPIO_PIN_22)){
			while(!metal_gpio_get_input_pin(gpio, GPIO_PIN_22));

			print_mode++;
			if (print_mode > 1) print_mode = 0;

			if (print_mode == 1){
				cpu_clock_config(320);
				uart_init(BAUDRATE_115200);
				cpu_clock = metal_clock_get_rate_hz(&__metal_dt_clock_4.clock);
				printf("Clock frequency: %d\n", cpu_clock);
			}
		}

		metal_gpio_toggle_pin(gpio, GPIO_PIN_9);
		count++;
		if (count > 10000){
			count = 0;
			metal_gpio_toggle_pin(gpio, GPIO_PIN_18);

			printf("Test\n");
		}

	}
}
