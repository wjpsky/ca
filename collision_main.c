/*****************************************************************************
 * Product: collision_main.c
 * Version: 0.1
 * Creators: Jin
 * Created: March 30 2011
 * History:
 *
 * Movement/CA Group
 *****************************************************************************/
//#define ENABLE_LIBARDUINO

#ifdef ENABLE_LIBARDUINO
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <libarduino.h>

#define IRPIN1 0
#define IRPIN2 1
#define IRPIN3 3
#define IRPIN4 4
#endif

#include <stdlib.h>
#include <stdio.h>

#include "ca.h"

//**********************************************************
// main method
//**********************************************************

int main(int argc, char* argv[])
{

#ifdef ENABLE_LIBARDUINO
  serial_init();
  fdevopen(serial_putchar, serial_getchar);
  loop();
  return 1;	

#else

  int ir1,ir2,ir3,ir4;

  if(argc == 5)
    {
      ir1 = atoi(argv[1]);
      ir2 = atoi(argv[2]);
      ir3 = atoi(argv[3]);
      ir4 = atoi(argv[4]);

      loop(ir1, ir2, ir3, ir4);

      return 1;
    }
  else
    {
      printf("too few argument\n");
      return 0;
    }

#endif
}

//**********************************************************
//loooop
//**********************************************************
#ifdef ENABLE_LIBARDUINO
void loop()
{

  // get the distance
  int ir1=ir_distance(IRPIN1);
  int ir2=ir_distance(IRPIN2);
  int ir3=ir_distance(IRPIN3);
  int ir4=ir_distance(IRPIN4);

  int dir= direction_filter(get_speed(),get_dir(),ir1,ir2,ir3,ir4);
  printf("IF I HAVE TO PICK A DIRECTION\nI CHOOSE ");
  outputdirection(dir);
}
#else

void loop(int ir1, int ir2, int ir3, int ir4)
{
  int dir= direction_filter(get_speed(),get_dir(),ir1,ir2,ir3,ir4);
  printf("IF I HAVE TO PICK A DIRECTION\nI CHOOSE ");
  outputdirection(dir);
}
#endif


//**********************************************************
// filter the direction according to the collision logic
// return the direction to go
//**********************************************************
int direction_filter(int speed,int dir, 
		     int ir1, int ir2, int ir3, int ir4)
{
  int dangerzone;
  dangerzone= speed_filter(speed);

  unsigned char * irboolean;
  irboolean =  distance_filter(dangerzone,ir1,ir2,ir3,ir4);

  unsigned char *direction_result;  
  direction_result=ir_filter(irboolean);
  free(irboolean);

  direction_result = currentDirection_filter(dir,direction_result);

  printf("\nFINAL RESULT \n");
  print_result(direction_result);  

  int finalDir = final_direction(dir,direction_result);
  free(direction_result);

  return finalDir;
}


//**********************************************************
// return the flying speed.
//**********************************************************
int get_speed()
{
  return 20;
}


//**********************************************************
// return the current flying direction.
//**********************************************************
int get_dir()
{
  return 2;
}
