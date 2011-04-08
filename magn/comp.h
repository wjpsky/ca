void getValues(int *x, int *y, int *z);
void sendStart(void);
void sendStop(void);
void sendByte(unsigned char data);
unsigned char receiveByte(void);
unsigned char readStatus(void);
void waitForReady(void);
