/*   
     .        IR1(FRONT)

     IR3(LEFT)         IR4(RIGHT)

     .        IR2(BACK)

     {front, back, left, right,hover}

*/

#include <stdlib.h>
#include <stdio.h>

#define PRINT printf("\n================================\n")

//translate the 0 and 1
char * translate(int i){
  char *result;
  if (i==0){
    result ="not ok";
  }
  else 
    result ="ok";

  return result;
}

// translate the output of IR
void outputIR(int *result)
{
printf("\n detects an object at ");
if(*result ==  1)
  printf("\n Front ");

 if(*(result + 1) == 1)
  printf("\n Back ");

 if(*(result + 2) == 1)
  printf("\n Left ");

 if(*(result + 3) == 1)
  printf("\n Right ");
}

//translate the current direction
void outputdirection(int direction)
{
  // {front, back, left, right,hover}
switch (direction) {
  case 0:
printf("\n Hover ");
    break;
  case 1:
printf("\n Front ");
    break;
  case 2:
printf("\n Back ");
    break;
  case 3:
printf("\n Left ");
    break;  
case 4:
printf("\n Right ");
    break;  
 }
}


void print_result(int *result){
  int i;
  char *answer;
  for (i=0;i<5;i++){
    answer=translate ( *(result+i));
    if (i==0){
      printf("Front is %s\n",answer);
    }
    if (i==1){
      printf("Back is %s\n",answer);
    }
    if (i==2){
      printf("Left is %s\n", answer);
    }
    if (i==3){
      printf("Right is %s\n",answer);
    }
    if (i==4){
      printf("Hover is %s\n", answer);
    }
  }
}



int speed_filter(int speed){
  int dangerzone;
  //hoving 
  if(speed<5){
    dangerzone=20;
  }
  //slow
  else if(speed<30&&speed>=5){
    dangerzone=50;
  }
  //meduim
  else if(speed<50&&speed>=30){
    dangerzone=75;
  }
  //fast
  else if(speed<75&&speed>=50){

    dangerzone=100;
  }
  //whoooooot!!!
  else{
    dangerzone = 150;
  }
  printf("Quadrocopter travels at speed %d\n", speed);
  printf("dangerous zone is %d\n", dangerzone);
  return dangerzone;
}

int* distance_filter(int dangerzone,int ir1, int ir2, int ir3,int ir4){
  if(ir1>dangerzone)
    ir1=1;   
  else    
    ir1=0;

  if(ir2>dangerzone)
    ir2=1;   
  else    
    ir2=0;

  if(ir3>dangerzone)
    ir3=1;   
  else    
    ir3=0;

  if(ir4>dangerzone)
    ir4=1;   
  else    
    ir4=0;

  int *irs = calloc(4, sizeof(int)) ;
  *irs=ir1;
  *(irs+1)=ir2;
  *(irs+2)=ir3;
  *(irs+3)=ir4;

  outputIR(irs);

  return irs;
}

int* ir_filter(int *irs)
{
  int ir1 = *irs;
  int ir2 = *(irs+1);
  int ir3 = *(irs+2);
  int ir4 = *(irs+3);

  int front=1;
  int back=1;
  int left=1;
  int right=1;
  int hover=1;

  //ir1 detects collision
  if (ir1==1)
    {
      front=0;
    }

  //ir2 detects collision
  if(ir2==1)
    { 
      back=0;
    }

  //ir3 detects collision
  if(ir3==1)
    {
      left=0;
    }

  //ir4 detects collsion
  if(ir4==1)
    {
      right=0;
    }

  int *results = calloc(5, sizeof(int)) ;
  *results=front;
  *(results+1)=back;
  *(results+2)=left;
  *(results+3)=right;
  *(results+4)=hover;
  PRINT;
  printf("after filter the according to the irs\n\n");
  print_result(results);
  PRINT;
  return results;
}


int *currentDirection_filter(int currentDirection,int *directions)
{
  int front = *directions;
  int back = *(directions+1);
  int left = *(directions+2);
  int right = *(directions+3);
  int hover = *(directions+4);

  //face to sensor 1
  if(currentDirection==1)
    {
      back=0;
    }

  if(currentDirection==2)
    {
      front=0;
    }
  if(currentDirection==3)
    {
      right=0;
    }
  if(currentDirection==4)
    {
      left=0;
    }

  int *results = calloc(5, sizeof(int)) ;
  *results=front;
  *(results+1)=back;
  *(results+2)=left;
  *(results+3)=right;
  *(results+4)=hover;

  PRINT;
  printf("Quadrocopter heading towards");
  outputdirection(currentDirection);
  printf("after filter according to the heading directions\n\n");
  print_result(results);
  PRINT;

  return results;
}


int main(int argc, char* argv[]){

  int ir1,ir2,ir3,ir4,direction,speed;

  if(argc == 7)
    {
      ir1 = atoi(argv[1]);
      ir2 = atoi(argv[2]);
      ir3 = atoi(argv[3]);
      ir4 = atoi(argv[4]);
      direction=atoi(argv[5]);
      speed=atoi(argv[6]);
    }

  int *result;
  result =  currentDirection_filter(direction,ir_filter(distance_filter(speed_filter(speed),ir1,ir2,ir3,ir4)));
  print_result(result);
  PRINT;
  
}
