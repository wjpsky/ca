#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <libarduino.h>
#include <WProgram.h>

#include "comp.h"

int main(void){
	init();
	in();
	sei();
	while(1) {
		int x,y,z;
		getValues(&x,&y,&z);	
		printf("X= %d\tY= %d\tZ= %d\n", x, y, z);
		delay(1000);
	}
	return 1;
}

void in(void){
	PORTC = 0b00110000;
	// Formula from 21.5.2 in ATmega168 datasheet.
	TWSR &= ~((1<<TWPS1)&(1<<TWPS0));
	TWBR = (unsigned char)(F_CPU/200000l-8);
	// Put the HMC5843 into continuous mode
	sendStart();
	sendByte(0x3C);
	sendByte(0x02);
	sendByte(0x00);
	sendStop();
	delay(100);
}

void getValues(int *x, int *y, int *z) {
	unsigned char xin, yin, zin;
	sendStart();
	sendByte(0x3D);
	xin = receiveByte();
	*x = (xin<<8)|receiveByte();
	yin = receiveByte();
	*y = (yin<<8)|receiveByte();
	zin = receiveByte();
	*z = (zin<<8)|receiveByte();
	sendByte(0x3D);
	sendStop();
}

void sendStart(void) {
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
}

void sendStop(void) {
	waitForReady();
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void sendByte(unsigned char data) {
	waitForReady();
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
}

unsigned char receiveByte(void) {
	waitForReady();
	TWCR = ((TWCR&0x0F)|(1<<TWINT)|(1<<TWEA));
	waitForReady();
	return(TWDR);
}

unsigned char readStatus() {
	waitForReady();
	return(TWSR);
}

void waitForReady(void) {
	int timeout = 200;
	while ((!(TWCR & (1<<TWINT))) && (timeout--));
}
