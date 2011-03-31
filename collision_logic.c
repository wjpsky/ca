/*
  . IR1(FRONT)

  IR3(LEFT) IR4(RIGHT)

  . IR2(BACK)

  {front, back, left, right,hover}


  /*****************************************************************************
  * Product: collision_logic.c
  * Version: 0.1
  * Creators: Jin, Amber
  * Created: March 29 2011
  * History:
  * March 30th, 2011 - Amber: Changed int types to unsigned char for booleans.
  *                           Changed to bitwise operation for changing values
  *                      Jin: Add method to get the final destination
  *
  * Movement/CA Group
  *****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "ca.h"

//the speed control variables
#define HOVERSPEED 5
#define SLOWSPEED 25
#define MEDIUMSPEED 50
#define FASTSPEED 75

//the dangerzone varibales according to the speed
#define HOVERZONE 20
#define SLOWZONE 50
#define MEDIUMZONE 75
#define FASTZONE 100
#define MADZONE 150

//the current flying directions
#define FRONT 1
#define BACK 2
#define LEFT 3
#define RIGHT 4
#define HOVER 0

#define PRINT printf("\n================================\n")


//*******************************************************************************'
// filter the dangerous zone for the quadrocopter to react according to the speed
// return the dangerous zone in "cm"
//*******************************************************************
int speed_filter(int speed)
{
  int dangerzone;

  if(speed<HOVERSPEED)
    dangerzone=HOVERZONE;
  else if(speed<SLOWSPEED && speed>=HOVERSPEED)
    dangerzone=SLOWZONE;
  else if(speed<MEDIUMSPEED&&speed>=SLOWSPEED)
    dangerzone=MEDIUMZONE;
  else if(speed<FASTSPEED&&speed>=MEDIUMSPEED)
    dangerzone=FASTZONE;
  else
    dangerzone = MADZONE;
  
  PRINT;
  printf("Quadrocopter travels at speed %d\n", speed);
  printf("dangerous zone is %d\n", dangerzone);

  return dangerzone;
}


//*********************************************************
// Decides if each ir is triggered or not
// take the distance the ir measured, and the distance of the dangerzone
// return 0 if the ir is NOT triggered, 1 as triggered
// return an array of irs.
//**********************************************************
unsigned char* distance_filter(int dangerzone,int ir1, int ir2, int ir3,int ir4)
{

  unsigned char irBoolean1 = 1;
  unsigned char irBoolean2 = 1;
  unsigned char irBoolean3 = 1;
  unsigned char irBoolean4 = 1;

  if(ir1>dangerzone)
    irBoolean1 ^= 1;

  if(ir2>dangerzone)
    irBoolean2 ^= 1;

  if(ir3>dangerzone)
    irBoolean3 ^= 1;

  if(ir4>dangerzone)
    irBoolean4 ^= 1;

  //Allocates an array of 4 unsigned characters
  unsigned char *irBooleans = calloc(4, sizeof(unsigned char)) ;
  *irBooleans=irBoolean1;
  *(irBooleans+1)=irBoolean2;
  *(irBooleans+2)=irBoolean3;
  *(irBooleans+3)=irBoolean4;
  
  //prints output for the objects detected
  PRINT;
  printf("Result for which ir is triggered: \n");
  outputIR(irBooleans);
  
  //returns the unsigned char array of 0 or 1 for each IR sensor
  return irBooleans;
}


//**********************************************************
// Filter the directions options for the quadrocopter
// according to the boolean value of four irs
// return the boolean value of 5 directions (front, back, left, right, hover)
//**********************************************************
unsigned char* ir_filter(unsigned char *irs)
{

  unsigned char front = 1;
  unsigned char back = 1;
  unsigned char left = 1;
  unsigned char right = 1;
  unsigned char hover = 1;
 

  //ir1 detects collision
  if (*irs==1)
    front ^= 1;

  //ir2 detects collision
  if(*(irs+1)==1)
    back ^= 1;

  //ir3 detects collision
  if(*(irs+2)==1)
    left ^= 1;

  //ir4 detects collsion
  if(*(irs+3)==1)
    right ^= 1;

  unsigned char *results = calloc(5, sizeof(unsigned char) );
  *results=front;
  *(results+1)=back;
  *(results+2)=left;
  *(results+3)=right;
  *(results+4)=hover;

  PRINT;
  printf("after filter the according to the irs\n\n");
  print_result(results);

  return results;
}


//**********************************************************
//Filter the direction options for the quadrocopter
//According to the direction the quadrocopter is flying towards
//return the boolean value of 5 directions (front, back, left, right, hover)
//**********************************************************
unsigned char *currentDirection_filter(int currentDirection,unsigned char *directions)
{

  unsigned char front = *(directions);
  unsigned char back = *(directions+1);
  unsigned char left = *(directions+2);
  unsigned char right = *(directions+3);
  unsigned char hover = *(directions+4);

  //face to sensor 1
  if(currentDirection==FRONT)
    back = 0;

  if(currentDirection==BACK)
    front = 0;

  if(currentDirection==LEFT)
    right = 0;

  if(currentDirection==RIGHT)
    left = 0;

  unsigned char *results = calloc(5, sizeof(unsigned char) );
  *results=front;
  *(results+1)=back;
  *(results+2)=left;
  *(results+3)=right;
  *(results+4)=hover;

  PRINT;
  printf("Quadrocopter heading towards ");
  outputdirection(currentDirection);

  PRINT;
  printf("after filter according to the heading directions\n");
  print_result(results);

  return results;
}


//*********************************************************
// Filter the direction options for the quadrocopter
// return the first available direction in the list
// return the integer, 1 front 2 back 3 left 4 right 0 hover
//**********************************************************
int final_direction(unsigned char *directions)
{
  int i;
  for (i=0;i<6;i++)
    {
      if(*(directions+i)==1){
	if(i==4)
	  return 0;
	else
	  return i+1;
      }	
    }
  return 6;
}


//**********************************************************
// translate the 0 and 1
// return 0 as not ok, 1 as ok
//**********************************************************
char * translate(int i)
{
  char *result;
  if (i==0)
    result ="not ok";
  else
    result ="ok";

  return result;
}

//**********************************************************
// translate the output of IR
//**********************************************************
void outputIR(unsigned char *result)
{

  printf("\n detects an object at ");
  if(*result == 1)
    printf("\n Front ");

  if(*(result + 1) == 1)
    printf("\n Back ");

  if(*(result + 2) == 1)
    printf("\n Left ");

  if(*(result + 3) == 1)
    printf("\n Right ");
}

//**********************************************************
//translate the current direction
//**********************************************************
void outputdirection(int direction)
{
  // {front, back, left, right,hover}
  switch (direction)
    {
    case 0:
      printf("Hover \n");
      break;
    case 1:
      printf("Front \n");
      break;
    case 2:
      printf("Back \n ");
      break;
    case 3:
      printf("Left \n ");
      break;
    case 4:
      printf("Right \n");
      break;
    default:
      printf("NO PLACE TO GO\n");
    }
}


//**********************************************************
//translate the result of the directions options
//**********************************************************
void print_result(unsigned char *result)
{
  int i;
  char *answer;

  for (i=0;i<5;i++)
    {
      answer=translate ( *(result+i));

      if (i==0)
	printf("Front is %s\n",answer);
      
      if (i==1)
	printf("Back is %s\n",answer);
      
      if (i==2)
	printf("Left is %s\n", answer);
      
      if (i==3)
	printf("Right is %s\n",answer);
      
      if (i==4)
	printf("Hover is %s\n", answer);
    }
}


//**********************************************************
// main method
//**********************************************************
int main(int argc, char* argv[])
{
  int ir1,ir2,ir3,ir4,flyingDir,speed;

  if(argc == 7)
    {
      ir1 = atoi(argv[1]);
      ir2 = atoi(argv[2]);
      ir3 = atoi(argv[3]);
      ir4 = atoi(argv[4]);
      flyingDir=atoi(argv[5]);
      speed=atoi(argv[6]);
  
      int dangerzone;
      dangerzone= speed_filter(speed);

      unsigned char * irboolean;
      irboolean =  distance_filter(dangerzone,ir1,ir2,ir3,ir4);

      unsigned char *ir_filter_result;  
      ir_filter_result=ir_filter(irboolean);

      unsigned char *currentDirection_filter_result;
      currentDirection_filter_result = currentDirection_filter(flyingDir,ir_filter_result);

      PRINT;
      printf("FINAL RESULT \n\n");
      print_result(currentDirection_filter_result);  

      int dir = final_direction(currentDirection_filter_result);

      PRINT; 
      printf("IF I HAVE TO PICK A DIRECTION\nI CHOOSE ");
      outputdirection(dir);
      PRINT; 
      return 1;
    }
  else
    {
      printf("too few argument\n");
      return 0;
    }
}


