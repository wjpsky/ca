/*****************************************************************************
 * Product: movementInterface.c
 * Version: 0.1
 * Created: April 7, 2011
 * History:
 *          
 *
 * Movement/CA Group
 *****************************************************************************/

#include "ca.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef ARDUINO
//************************************************************
// ARDUINO
// All collision preperation goes here.
//************************************************************
void collision_init()
{

}


//************************************************************
// ARDUINO
// Collision is started here
//************************************************************
void collision_run()
{
  init();

  /* //init the serial output */
  // serial_init();
  // fdevopen(serial_putchar, serial_getchar);

  int i=0;
  while(i<1000)
    {
      direction_filter();
      i++;
    }

  return 1;

}


#elif defined PC
//************************************************************
// PC
//  All movement preperation goes here.
//************************************************************
void collision_init()
{
  



}

//************************************************************
// PC
// Movement is started here
//************************************************************
void collision_run(int ir1, int ir2, int ir3, int ir4)
{

  int i=0;
  while (i<5){
    direction_filter(get_speed(),get_dir(),ir1, ir2, ir3, ir4);
    i++;
  }

}


#endif


//**********************************************************
// main method
//**********************************************************

int main(int argc, char* argv[])
{

  int ir1,ir2,ir3,ir4;

  ir1 = atoi(argv[1]);
  ir2 = atoi(argv[2]);
  ir3 = atoi(argv[3]);
  ir4 = atoi(argv[4]);
  int i=0;
  while (i<5){
    direction_filter(get_speed(),get_dir(),ir1, ir2, ir3, ir4);
    i++;
}

  return 1;

}
