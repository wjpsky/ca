/*****************************************************************************
* Product: angle.c
* Version: 0.1
* Released: Apr 6 2011 
* Updated: 
* Created by: Sepideh Fazlmashhadi
*
* Copyright (C) 2002-2004 Quantum Leaps. All rights reserved.
*
* 
*
* IT University
*****************************************************************************/
#include <stdio.h> /* standard input and output */
#include <math.h>
#define PI 3.14159265

/* caculate the angle between 2 points */
void angle(double x,double y){ 
  double alpha;
  alpha =atan2 (y,x) * 180 / PI;
  printf("\n\n the angle is %f degree \n\n ",alpha);
}

/* main method  */
void main(){
  angle(30,100);
}
