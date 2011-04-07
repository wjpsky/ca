/*****************************************************************************
 * Product: collision_main.c
 * Version: 0.1
 * Creators: Jin
 * Created: March 30 2011
 * History:
 * March 31st, 2011 -   Jin: fix the memory leak problem
 *                           add ifdefine for the entire code
 *
 * Movement/CA Group
 *****************************************************************************/
//#define  ENABLE_LIBARDUINO

#ifdef ENABLE_LIBARDUINO

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <libarduino.h>

#include <WProgram.h>

#define IRPIN1 0
#define IRPIN2 1
#define IRPIN3 3
#define IRPIN4 4

#endif


#include <stdlib.h>
#include <stdio.h>
#include "ca.h"
#define PRINT printf("\n================================\n")



#ifdef ENABLE_LIBARDUINO
//**********************************************************
// filter the direction according to the collision logic
// return the direction to go
//**********************************************************
int direction_filter(void)
{

  // get the distance
 int ir1=ir_distance(IRPIN1);
  printf ("ir1 = %d\n",ir1);
 int ir2=ir_distance(IRPIN2);
  printf ("ir2 = %d\n",ir2);
  int ir3=ir_distance(IRPIN3);
  printf ("ir3 = %d\n",ir3);
int ir4=ir_distance(IRPIN4);
  printf ("ir4 = %d\n",ir4);

  //SPEED -> DANGERZONE
  int dangerzone;
  dangerzone= speed_filter(get_speed());

  /* PRINT; */
  /* printf("Quadrocopter travels at speed %d\n", get_speed()); */
  /* printf("dangerous zone is %d\n", dangerzone); */


  //DANGERZONE+IR DISTANCE-> BOOLEANS
  unsigned char * irBooleans;// freed
  irBooleans =  distance_filter(dangerzone,ir1,ir2,ir3,ir4);

  /* PRINT; */
  /* printf("Result for which ir is triggered: \n"); */
  /* outputIR(irBooleans); */


  //BOOLEANS -> DIRECTION RESULTS
  unsigned char *result;  //freed
  result=ir_filter(irBooleans);

  free(irBooleans); 

  /* PRINT; */
  /* printf("after filter the according to the ir BOOLEANS\n\n"); */
  /* print_result(result); */


  //CURRENT DIRECTION -> DIRECTION RESULTS
  result = currentDirection_filter(get_dir(),result);

  /* PRINT; */
  /* printf("Quadrocopter heading towards "); */
  /* outputdirection(dir); */

  /* PRINT; */
  /* printf("after filter according to the heading directions\n\n"); */
  /* print_result(result); */


  int *distance_diff= calloc(4, sizeof(int) );
  *distance_diff=ir_distance(IRPIN1)-ir1;
  *(distance_diff+1)=ir_distance(IRPIN2)-ir2;
  *(distance_diff+2)=ir_distance(IRPIN3)-ir3;
  *(distance_diff+3)=ir_distance(IRPIN4)-ir4;
  
  //DISTANCE DIFFERENCE-> TOWARDS WHICH IR 
  unsigned char *moving_close = moving_closer(distance_diff);//freed
  free(distance_diff);

  /* PRINT; */
  /* printf("Result for which direction is moving closer \n"); */
  /* outputIR(moving_close); */

  // TOWARDS WHICH IR -> DIRECTION RESULT
  result=moving_closer_filter(moving_close,result);
  free(moving_close);

  /* PRINT; */
  /* printf("after filter according to the moving object\n"); */
  /* print_result(result); */

  /* PRINT; */
  /* printf("\nFINAL\n\n"); */
  /* print_result(result); */

  //RESULT -> PICK ONE DIRECTION
  int finalDir = final_direction(get_dir(),result);
  free(result);

  printf("\nIF I HAVE TO PICK A DIRECTION\nI CHOOSE ");
  outputdirection(finalDir);

  return finalDir;
}


#else

//**********************************************************
// filter the direction according to the collision logic
// return the direction to go
//**********************************************************
int direction_filter(int speed,int dir, 
		     int ir1, int ir2, int ir3, int ir4)
{
  //SPEED -> DANGERZONE
  int dangerzone;
  dangerzone= speed_filter(speed);

  PRINT;
  printf("Quadrocopter travels at speed %d\n", speed);
  printf("dangerous zone is %d\n", dangerzone);


  //DANGERZONE+IR DISTANCE-> BOOLEANS
  unsigned char *irBooleans;// freed
  irBooleans = distance_filter(dangerzone,ir1,ir2,ir3,ir4);

  PRINT;
  printf("Result for which ir is triggered: \n");
  outputIR(irBooleans);


  //BOOLEANS -> DIRECTION RESULTS
  unsigned char *result;  //freed
  result=ir_filter(irBooleans);

  free(irBooleans); 

  PRINT;
  printf("after filter the according to the ir BOOLEANS\n\n");
  print_result(result);


  //CURRENT DIRECTION -> DIRECTION RESULTS
  result = currentDirection_filter(dir,result);

  PRINT;
  printf("Quadrocopter heading towards ");
  outputdirection(dir);

  PRINT;
  printf("after filter according to the heading directions\n\n");
  print_result(result);

  int ir1_new, ir2_new, ir3_new,ir4_new;
  //change here
  ir1_new=100;
  ir2_new=100;
  ir3_new=100;
  ir4_new=100;
 

  int *distance_diff= calloc(4, sizeof(int) );//freed
  *distance_diff=ir1_new-ir1;
  *(distance_diff+1)=ir2_new-ir2;
  *(distance_diff+2)=ir3_new-ir3;
  *(distance_diff+3)=ir4_new-ir4;
  
  //DISTANCE DIFFERENCE-> TOWARDS WHICH IR 
  unsigned char *moving_close = moving_closer(distance_diff);//freed
  free(distance_diff);

  PRINT;
  printf("Result for which direction is moving closer \n");
  outputIR(moving_close);

  // TOWARDS WHICH IR -> DIRECTION RESULT
  result=moving_closer_filter(moving_close,result);
  free(moving_close);

  PRINT;
  printf("after filter according to the moving object\n");
  print_result(result);

  PRINT;
  printf("\nFINAL\n\n");
  print_result(result);

  //RESULT -> PICK ONE DIRECTION
  int finalDir = final_direction(get_dir(),result);
  free(result);

  PRINT;
  printf("\nIF I HAVE TO PICK A DIRECTION\nI CHOOSE ");
  outputdirection(finalDir);
  PRINT;

  return finalDir;
}
#endif


//**********************************************************
// return the flying speed.
//**********************************************************
int get_speed(void)
{
  return 20;
}


//**********************************************************
// return the current flying direction.
//**********************************************************
int get_dir(void)
{
  return 2;
}
