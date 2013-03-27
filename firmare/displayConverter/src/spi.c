
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

/** 
 * inits the hardware spi as a slave
 */
void spi_init() {
	/* Set MISO output, all others input */
	DDRB |= (1 << DDB4);

	/* Enable SPI */
	SPCR = _BV(SPE) | _BV(SPIE);
}

/** 
 * read a character from SPI.
 */
char spi_read() {
	/* Wait for reception complete */
	while(!(SPSR & _BV(SPIF)))
		;

	/* Return Data Register */
	return SPDR;
}



