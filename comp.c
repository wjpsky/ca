/*
Author: Alina Butko
Description: Reads data from magnetometer
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <math.h>

#include "comp.h"

#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif

void setup(){
#ifdef ARDUINO
  Serial.begin(9600);
  delay(5); // The HMC5843 needs 5ms before it will communicate
#elif defined PC
	printf("Start\n");
#endif
}

void loop() {
		int x,y,z;
		int pitch = 0;
		int roll = 0;
		float heading = calc_h(pitch, roll, x, y, z);
		getValues(&x,&y,&z);
#ifdef ARDUINO
  		Serial.print(x);
		Serial.print(", ");
		Serial.print(y);
		Serial.print(", ");
		Serial.println(z);
		Serial.print("Heading: ");
		Serial.println(heading);
#elif defined PC
   printf("%d, %d, %d\n")
#endif
		delay(1000);
}

int main(void){
//#ifdef ARDUINO
	init();
//#endif
	in();
	sei();
	setup();
	int i;
	for(i=0;i<10;i++){ loop();}
	return 0;
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

float calc_h(int pitch, int roll, int x, int y, int z){
	float xh, yh;
	xh = x*cos(pitch) + z*sin(pitch);
	yh = x*sin(roll)*sin(pitch) + y*cos(roll) - z*sin(roll)*cos(pitch);
	float h;
	h = atan(yh/xh);
	return h;
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
