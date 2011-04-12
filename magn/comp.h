void in(void);
float calc_h(int pitch, int roll, int x, int y, int z);
void getValues(int *x, int *y, int *z);
void sendStart(void);
void sendStop(void);
void sendByte(unsigned char data);
unsigned char receiveByte(void);
unsigned char readStatus(void);
void waitForReady(void);
