#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <libarduino.h>
#include <WProgram.h>
#include <HMC.h>

int main (void){

	uint16_t x,y,z;
	serial_init();
	fdevopen(serial_putchar, serial_getchar);
	_delay_ms(5); // The HMC5843 needs 5ms before it will communicate
	//	hmc_init();
	HMC.init();
	sei(); /* enable interrupts */

	while (1) {
		HMC.getValues(&x,&y,&z);
//		y = hmc_get(1);
//		z = hmc_get(2);
		printf("x: %d\ny: %d\nz: %d\n", x, y, z);
		_delay_ms(100); // There will be new values every 100ms
	}
  return 1;
}
