  /*****************************************************************************
  * Product: collision_sensor.c
  * Version: 0.1
  * Creators: Jin
  * Created: March 30 2011
  * History:
  *
  * Movement/CA Group
  *****************************************************************************/
//#define ENABLE_LIBARDUINO

#ifdef ARDUINO
#include <WProgram.h>
#include <stdio.h>
#include <math.h>
#include "ca.h"


int ir_distance(int irpin)
{
  int value=analogRead(irpin);
  // printf ("value is %d \n",value);

  // value convert to volts
  // value from sensor * (5/1024)
  // if running 3.3.volts then change 5 to 3.3

  //convert to the distance according to the formula from luckylarry.co.uk
  int distance = 65*pow(value*0.0048828125, -1.10);
  return distance; 
}


/* float sonar_distance(int sonarPin) */
/* { */
/*   // establish variables for duration of the ping, */
/*   // and the distance result in inches and centimeters: */
/*   long duration; */

/*   // The PING))) is triggered by a HIGH pulse of 2 or more microseconds. */
/*   // Give a short LOW pulse beforehand to ensure a clean HIGH pulse: */
/*   pinMode(sonarPin, OUTPUT); */
/*   digitalWrite(sonarPin, LOW); */
/*   _delay_ms(2); */
/*   digitalWrite(sonarPin, HIGH); */
/*   _delay_ms(5); */
/*   digitalWrite(sonarPin, LOW); */

/*   // The same pin is used to read the signal from the PING))): a HIGH */
/*   // pulse whose duration is the time (in microseconds) from the sending */
/*   // of the ping to the reception of its echo off of an object. */
/*   pinMode(sonarPin, INPUT); */
/*   duration = pulseIn(sonarPin, HIGH); */

/*   // The speed of sound is 340 m/s or 29 microseconds per centimeter. */
/*   // The ping travels out and back, so to find the distance of the */
/*   // object we take half of the distance travelled. */
/*   float distance= duration/29/2; */

/*   return distance; */
/* } */
#endif
