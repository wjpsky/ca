#include "../ca/ca.h"
#include "../ca/collision_logic.c"


/* Set up and clean up test suite */

int init_suite(void) {
  return 0;
}

int clean_suite(void) {
  return 0;
}

void testCase1(void) {
 	int dangerzone;
  	dangerzone=speed_filter(134515328);
  	CU_ASSERT(dangerzone==150);

}
 void testCase2(void) {
	 int * irboolean;
 	 irboolean =  distance_filter(150,0,1,0,0);
         CU_ASSERT(*irboolean== (0,1,0,0));
        
}
 void testCase3(void) {
	int * irboolean;
 	irboolean =  distance_filter(150,0,1,0,0);
	int *ir_filter_result;
	ir_filter_result=ir_filter(irboolean);	
        CU_ASSERT(*ir_filter_result== (1,1,1,1,1));
}
 void testCase4(void) {
	int * irboolean;
 	irboolean =  distance_filter(150,0,1,0,0);
	int *ir_filter_result;
	ir_filter_result=ir_filter(irboolean);	
	int *currentDirection_filter_result;
	currentDirection_filter_result = currentDirection_filter(1,ir_filter_result);
	CU_ASSERT(*currentDirection_filter_result== (1,1,1,1,1));
}

