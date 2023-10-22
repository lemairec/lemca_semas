#ifndef LEMCA_UART_H_
#define LEMCA_UART_H_

#ifdef __cplusplus
extern "C" {
#endif

void uart_init();

void uart_loop();

void uart_send_loop_message(int millis);

void uart_send_message_aux(int touch);

void uart_send_message(char *);

#ifdef __cplusplus
}
#endif

#endif