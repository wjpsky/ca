char * translate(int i);
void outputIR(int *result);
void outputdirection(int direction);
void print_result(int *result);
int speed_filter(int speed);
int* distance_filter(int dangerzone,int ir1, int ir2, int ir3,int ir4);
int* ir_filter(int *irs);
int *currentDirection_filter(int currentDirection,int *directions);