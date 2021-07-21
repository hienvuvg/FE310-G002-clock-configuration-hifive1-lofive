# Clock configuration for RISC-V FE310-G002 Freedom Studio (Freedom metal library)

Supported clock: 64, 128, 256, 320 MHz

Boards: LoFive R1, HiFive1 rev b with FE310-G002

UART baudrate needs to be reconfigured after setting a new clock frequency:

Example:

cpu_clock_config(320);

uart_init(115200);

Reference: https://github.com/kjarvel/hifive1revb_wifi
