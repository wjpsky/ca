/*****************************************************************************
 * Product: movementInterface.c
 * Version: 0.1
 * Created: April 7, 2011
 * History:
 *          
 *
 *
 * Movement/CA Group
 *****************************************************************************/

#include "movement.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef ARDUINO
//************************************************************
// ARDUINO
// All movement preperation goes here.
//************************************************************
void init()
{
  //start magnetometer


}


//************************************************************
// ARDUINO
// Movement is started here
//************************************************************
void run()
{
  



}
#endif



#ifdef PC
//************************************************************
// PC
//  All movement preperation goes here.
//************************************************************
void init()
{
  



}

//************************************************************
// PC
// Movement is started here
//************************************************************
void run()
{



}
#endif

#ifndef ARDUINO
#ifndef PC 
int main(int argc, char* argv[])
{
  //Receive the message through protocol from Navigation
  //Char order (1 start or 0 Stop)
  //int height
  // int direction
  
  //simulated test data
  /*char order  = atoi(argv[1]);
  int  height  = atoi(argv[2]);
  int direction = atoi(argv[3]);*/

  //read from magnetometer (x,y,z) and calculate the current heading

  //calculate the Y angle between the received instruction from navigation and the current heading
  

  //send out the commands through protocoll to filter group


  //TEMP TESTING SUPPORT
  /*char msg = to_AffectedMotorBinary(1,0,1,1);
     msg = to_MotorMessage(1,0,msg);

     printf("MESSAGE %d \n", msg);
     print_char_to_Binary(msg);*/
}

#endif
#endif
