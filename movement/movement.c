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
// 
//
//************************************************************

int main(int argc, char* argv[])
{
 short int bin  = atoi(argv[1]);
 print_char_to_Binary(bin);
}
