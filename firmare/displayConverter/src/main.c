
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "firmware.h"


/** 
 * this is the SPI send buffer
 */
char buffer[20];
volatile char telegram[20];
volatile int bufferPointer = 0;
volatile int hasComma = 0;
volatile int newTelegram = 0;



/** 
 * 
 * ISR to recieve data from SPI 
 */
ISR (SPI_STC_vect) {
  char x = SPDR;
  buffer[bufferPointer++] = convert(x);

  if (x == 0x2E) {
    hasComma = 1;
  } else if ( (!hasComma && bufferPointer  >= 11) || bufferPointer >= 12) {
		// store recieved message
    strncpy(telegram, &buffer[hasComma ? 2 : 1], 13);
    memset(buffer, 0, 20);

		// reset parsing engine
    bufferPointer = 0;
    hasComma = 0;

		// inform about newly recieved message
    newTelegram = 1;
  }
}


/** 
 * starting point of the firmware
 */
int main(void)
{
 	// init UART and SPI-Slave
	uart_init();
	spi_init();

	_delay_ms(3000);

	// initial message: so that we get to see something.
	uart_sendString("\r\nConnected!");

  sei();

	// loop forever here.
	while (1) {
		int k;

    if (newTelegram != 0) {
  		// send to the new VF-Display
	  	uart_sendString("\r\n");
      
		  for (k = 0; k < 10; k++) {
		  	uart_sendByte(telegram[k]);
		  }

      newTelegram = 0;
		}
	}
} 


