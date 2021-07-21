# FE310-G002-clock-configuration
Clock configuration for RISC-V FE310-G002 Freedom Studio

Supported clock: 64, 128, 256, 320 MHz

UART baudrate needs to be reconfigured after setting a new clock frequency:

Example:
  cpu_clock_config(320);
  uart_init(BAUDRATE_115200);
