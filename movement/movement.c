 /*****************************************************************************
  * Product: movement.c
  * Version: 0.1
  * Created: April 4 2011
  * History:
  *              
  *
  * Movement/CA Group
  *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "movement.h"




//************************************************************
// This function is used for showing a char as 0s and 1s
//
//************************************************************
void print_char_to_Binary(char bin)
{
  char counter,temp,bit;

  counter =sizeof(bin) * 8;

  for(counter = counter - 1; counter >= 0; counter--)
    {
      temp = 1 << counter;
      bit = temp & bin;
      if( bit == 0)
	printf("0");
      else
	printf("1");
    }

  printf("\n");
}


//************************************************************
//Receives if the message is increasing(boolean), is in panic mode(boolean) 
//and the integer representing the binary of the 4 affected motors 
//
// returns the 8 bits as a char , representing the message
//************************************************************
char to_MotorMessage(char Increasing, char PanicMode, char Motors)
{


}


//************************************************************
// Receives 0 or 1 status for 4 motors.
// Returns the 4 bits as the end part of 8 bits of a char
//
//************************************************************
char to_AffectedMotorBinary(char motor1, char motor2, char motor3, char motor4)
{


} 


int main(int argc, char* argv[])
{
 short int bin  = atoi(argv[1]);
 print_char_to_Binary(bin);
}
