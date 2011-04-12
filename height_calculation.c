/*
Author: Alina Butko
Moving directions: UP, DOWN, HOVER
Moving: 1 - OK, 0 - BAD
Detecting: 1 - BAD, 0 - OK
*/


#include <stdlib.h>
#include <stdio.h>

#define MINHEIGHT 0
#define MIDHEIGHT 25
#define MAXHEIGHT 50
#define UP 5
#define DOWN 6
#define HOVER 0
#define CRASH 666
#define PRINT printf("\n===================================\n")

int duration_to_cm(long duration){
	return duration/29/2;
}

int height_filter(int distance){
	if(distance == MINHEIGHT || (distance > MINHEIGHT && distance < MIDHEIGHT)){
		return UP;	
	}
	else if(distance == MIDHEIGHT){
		return HOVER;
	}
	else if(distance == MAXHEIGHT || (distance > MIDHEIGHT && distance < MAXHEIGHT)){
		return DOWN;
	}
	else return CRASH;
}

int height_calculation_main(int argc, char* argv[]){
	long duration;
	int cm;
	
	if(argc == 2){
		duration = atoi(argv[1]);
		cm = duration_to_cm(duration);
		PRINT;
		printf("CM: %d", cm);
		PRINT;
		int action;
		action = height_filter(cm);
		switch(action){
			case UP:
				printf("Me go UP :)");
				break;
			case DOWN:
				printf("Me go DOWN :)");
				break;
			case HOVER:
				printf("Me do nothing, me just HOVER :)");
				break;
			case CRASH:
				printf("Me CRASH :'(");
				break;
			default:
				printf("Me donno what to do '?.?'");
		}
		PRINT;		
	}
	else printf("Enter the distance!");
}


/*******************
 *return the height difference
 *******************/
int height_calc(int height_order, int height_sensor)
{
  return height_sensor-height_order;
}
