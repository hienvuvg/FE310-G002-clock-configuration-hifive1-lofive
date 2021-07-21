#ifndef UART_H__
#define UART_H__

#include <stdint.h>

#define DELAY           20000000
#define SPICLOCK_80KHZ  80000
#define STR_LEN         1024
#define BUF_LEN         4096
#ifdef __ICCRISCV__
#define fflush(a)
#endif

void uart_send(const char *str_p);
void uart_init(uint32_t baudrate);
int uart_putchar(char c);
int uart_getchar(void);

#endif
