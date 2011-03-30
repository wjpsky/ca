char * translate(int i);
void outputIR(unsigned char *result);
void outputdirection(int direction);
void print_result(unsigned char *result);
int speed_filter(int speed);
unsigned char* distance_filter(int dangerzone,int ir1, int ir2, int ir3,int ir4);
unsigned char* ir_filter(unsigned char *irs);
 unsigned char *currentDirection_filter(int currentDirection,unsigned char *directions);

