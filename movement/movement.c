 /*****************************************************************************
  * Product: movement.c
  * Version: 0.1
  * Created: April 4 2011
  * History:
  *          
  *
  *
  * Movement/CA Group
  *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "movement.h"


// BitMasking example http://www.indiabix.com/technical/c/bits-and-bytes/
#define BIT_POS(N)               ( 1U << (N) )
#define SET_FLAG(N, F)        ( (N) |= (F) )
#define CLR_FLAG(N, F)        ( (N) &= -(F) )



//Movement Command received from CA or Navigation
struct MoveCommand 
{
  char order;
  int  height;
  int direction;
};


//************************************************************
// 
// 0100 0000 (start)
//************************************************************
void start_motors()
{
  char msg = 0;
  SET_FLAG(msg, BIT_POS(6));
  pWrite(msg);
}

//************************************************************
//
//  0000 0000 (stop)
//************************************************************
void stop_motors()
{
  char msg = 0;
  pWrite(msg);
}


//************************************************************
//
//  1111 1111 (hover)
//************************************************************
void hover()
{
  char msg = 0;
  msg = ~msg;
  pWrite(msg);
}

//************************************************************
//
//Go Left without turning (Strafe)
//0110 1100 (left, decreases left motor and increases right motor)
//************************************************************
void go_left_no_strafe()
{
  char msg = to_AffectedMotorBinary(1,1,0,0);
  SET_FLAG(msg, BIT_POS(6));
  msg = to_MotorMessage(1,0,msg);
  pWrite(msg);
}


//************************************************************
//
//Go Right without turning (Strafe)
//0100 1100 (right, increases left motor and decreases right motor)
//************************************************************
void go_right_no_strafe()
{
  char msg = to_AffectedMotorBinary(1,1,0,0);
  SET_FLAG(msg, BIT_POS(6));
  msg = to_MotorMessage(0,0,msg);
  pWrite(msg);
}


//************************************************************
//Go Forwards
//
//0110 0011 (forward, decreases front motor and increases rear motor)
//************************************************************
void go_forwards()
{
  char msg = to_AffectedMotorBinary(0,0,1,1);
  SET_FLAG(msg, BIT_POS(6));
  msg = to_MotorMessage(1,0,msg);
  pWrite(msg);
}

//************************************************************
//Go Backwards
//
//0100 0011 (forward, decreases front motor and increases rear motor)
//************************************************************
void go_backwards()
{

 char msg = to_AffectedMotorBinary(0,0,1,1);
  SET_FLAG(msg, BIT_POS(6));
  msg = to_MotorMessage(0,0,msg);
  pWrite(msg);
}


//************************************************************
//Receives if the message is increasing(boolean), is in panic mode(boolean) 
//and the char representing the binary of the 4 affected motors 
//
// returns the 8 bits as a char , representing the message
//
//Example:
//<<46>> or 00100110
//<<protocol:2 = 0, increase/decrease:1 = 1, mode:1 = 0, motors:4 = 6>>
//************************************************************
char to_MotorMessage(char increasing, char panicMode, char motors)
{
  if(increasing == 1)
   SET_FLAG(motors, BIT_POS(5));

  if(panicMode == 1)
  SET_FLAG(motors, BIT_POS(4));
  
  return motors;
}


//************************************************************
//
// Receives 0 or 1 status for 4 motors.
// Returns the 4 bits as the end part of 8 bits of a char
// 
//************************************************************
char to_AffectedMotorBinary(char motor1, char motor2, char motor3, char motor4)
{
  char motors = 0;
 
  if(motor1 == 1) 
  SET_FLAG(motors, BIT_POS(3));

 if(motor2 == 1)
   SET_FLAG(motors, BIT_POS(2));

if(motor3 == 1) 
  SET_FLAG(motors, BIT_POS(1)) ;

if(motor4 == 1)
   SET_FLAG(motors, BIT_POS(0)) ;

   return motors;
} 



//*******TEST METHODS
void pWrite(char msg)
{
  printf("\nProtocol has this written to it: ");
  print_char_to_Binary(msg);
}

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

//************End of Testing methods


int main(int argc, char* argv[])
{

  //Receive the message through protocol from Navigation
  //Char order (1 start or 0 Stop)
  //int height
  // int direction
  
  //simulated test data
  char order  = atoi(argv[1]);
  int  height  = atoi(argv[2]);
  int direction = atoi(argv[3]);

  struct MoveCommand movement = {order,height,direction};

  /* start_motors();
  stop_motors(); 
  hover();
  go_forwards();
  go_backwards();
  go_right_no_strafe();
  go_left_no_strafe();*/

  //read from magnetometer (x,y,z) and calculate the current heading

  //calculate the Y angle between the received instruction from navigation and the current heading
  

  //send out the commands through protocoll to filter group


 //TEMP TESTING SUPPORT
 /* char msg = to_AffectedMotorBinary(1,0,1,1);
 msg = to_MotorMessage(1,0,msg);

 printf("MESSAGE %d \n", msg);
 print_char_to_Binary(msg);*/

}
