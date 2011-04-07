/*****************************************************************************
* Product: calculation.c renamed from(angle.c)
* Version: 0.1
* Released: Apr 6 2011 
* Updated:  April 7th - removed main and added as a part of movement.
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
#include "movement.h"

#define PI 3.14159265

/* caculate the angle between 2 points */
double angle(double x,double y){ 
  double alpha;
  alpha =atan2 (y,x) * 180 / PI;
  //printf("\n\n the angle is %f degree \n\n ",alpha);
  return alpha;
}

double third_side(int a, int b){
  double c = (a * a) + (b * b);
  c = pow(c,.5);
  //printf("\n\n third side %f  \n\n ",c);
  return c;
}

/*
void main(){
  angle(30,100);
  third_side(5,5);
}
*/
