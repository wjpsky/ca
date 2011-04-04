/*****************************************************************************
 * Product: ca.h
 * Version: 0.1
 * Created: March 30 2011
 *
 * Movement/CA Group
 *****************************************************************************/


/*******************
 * collision_logic.c
 *******************/
// filter the dangerous zone for the quadrocopter to react according to the speed
// return the dangerous zone in "cm"
int speed_filter(int speed);

// Decides if each ir is triggered or not
// take the distance the ir measured, and the distance of the dangerzone 
// return 0 if the ir is NOT triggered, 1 as triggered
// return an array of irs.
unsigned char* distance_filter(int dangerzone,int ir1, int ir2, int ir3,int ir4);

// filter the directions options for the quadrocopter
// according to the boolean value of four irs
// return the boolean value of 5 directions (front, back, left, right, hover)
unsigned char* ir_filter(unsigned char *irs);

// Filter the direction options for the quadrocopter
// According to the direction the quadrocopter is flying towards
// return the boolean value of 5 directions (front, back, left, right, hover)
unsigned char *currentDirection_filter(int currentDirection,unsigned char *directions);

//Filter the direction options for the quadrocopter
//According to the objects which is moving towards
//return the boolean value of 5 directions (front, back, left, right, hover)
unsigned char *moving_closer_filter(unsigned char *is_moving, unsigned char*directions);

// Filter the direction options for the quadrocopter
// return the first available direction in the list
// return the integer, 1 front 2 back 3 left 4 right 0 hover
int final_direction(int currentDir, unsigned char *directions);

// for print the data
char * translate(int i);
void outputIR(unsigned char *result);
void outputdirection(int direction);
void print_result(unsigned char *result);

/*******************
 * collision_main.c
 *******************/
void loop();
void loop(int ir1, int ir2, int ir3, int ir4);
int direction_filter(int speed,int dir, 
		     int ir1, int ir2, int ir3, int ir4);
int get_speed();
int get_dir();





/*******************
 * collision_sensor.c
 *******************/
float ir_distance(unsigned char irpin);
float sonar_distance(int sonarPin);




/*******************
 *object_calculations.c
 *******************/
unsigned char* moving_closer (unsigned char* irDistances);
