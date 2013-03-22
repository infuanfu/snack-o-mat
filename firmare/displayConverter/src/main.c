
#include <util/delay.h>
#include "firmware.h"

/** 
 * starting point of the firmware
 */
int main(void)
{
 	// init UART and SPI-Slave
	uart_init();
	spi_init();

	int i;
	for (i=0;i<3;i++) {
	  _delay_ms(1000);
	}

	// initial message: so that we get to see something.
	uart_sendString("\r\nConnected!");

	// loop forever here.
	while (1) {
		char buffer[13];
		int i, j, k;
		int hasComma = 0;

		memset(buffer, 0, 13);

		// read the data from SPI
		for (i = 0, j = 0; i < 11; i++, j++) {
			char x = spi_read();

			buffer[j] = convert( x );
			if (x == 0x2E) {
				hasComma = 1;
				i--;
			}
		}

		// send to the new VF-Display-
		uart_sendString("\r\n");
		for (k = hasComma ? 2 : 1; k < 12; k++) {
			uart_sendByte(buffer[k]);
		}
	} 
} 


