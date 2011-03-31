
  /*****************************************************************************
  * Product: object_calculations.c
  * Version: 0.1
  * Creators: Amber
  * Created: March 21, 2011
  * History:
  * 
  *
  *Description: calculations involved with objects movements detected.
  * Movement/CA Group
  *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "ca.h"

#define IGNORINGLITTLECHANGE 10



//*******************************************************************************'
// Receives array of differences where values are [Value2 - Value1, Value2 - Value1, Value2 - Value1]
// where value1 is the first measurement and value2 is the second measurement. 
//0 is moving closer
//1 is moving farther away
//*******************************************************************
unsigned char* moving_closer (unsigned char* irDistances)
{
  
  //an array of 4 values 0 or 1, to be returned
  unsigned char *movements = calloc(5, sizeof(unsigned char) );


  unsigned char i;
  for(i = 0; i < 5; i++)
    {
      if(*(irDistances + i) + IGNORINGLITTLECHANGE <= 0) //** The IGNORINGLITTLECHANGE helps ignore sensor variations
      *(movements + i)= 1;	
      else
	*(movements + i) = 0;
    }

  return movements;
}
