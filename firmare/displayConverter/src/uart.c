
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

/** 
 * inits the hardware uart on the atmega to a given baudrate.
 */
void uart_init() {
  DDRD   |= _BV(1);						// enable UART Pin on PORTD
  UBRR0   = (F_CPU / 16 / BAUD) - 1;

  UCSR0A = 0x00; 
  UCSR0B = _BV(TXEN0) | _BV(RXEN0);										// enable for read & write
  UCSR0C = _BV(USBS0) | _BV(UCSZ01) |_BV(UCSZ00); 	 	// enable for async transfer 8N1
}

/** 
 * send a single byte through UART 
 */
void uart_sendByte(char x) {
  while (!(UCSR0A & (1<<UDRE0)));
  
  UDR0 = x;
}

/** 
 * sends a complete string through UART
 */
void uart_sendString(char* x) {
  while(*x) {
    uart_sendByte(*x);
	x++;
  }
}

/** 
 * read a byte from UART
 */
char uart_recvByte() {
  while(!(UCSR0A & (1<<RXC0)));

  return UDR0;
}

/** 
 * returns nonzero when UART has a byte to be read
 */
char uart_rtr() {
  return (!(UCSR0A & (1<<RXC0)));
}



