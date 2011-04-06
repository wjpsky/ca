/*****************************************************************************
 * Product: movement.h
 * Version: 0.1
 * Created: April 4 2011
 *
 * Movement/CA Group
 *****************************************************************************/



void print_char_to_Binary(char bin);
void pWrite(char msg);
void print_char_to_Binary(char bin);
char to_MotorMessage(char increasing, char panicMode, char motors);
char to_AffectedMotorBinary(char motor1, char motor2, char motor3, char motor4);
