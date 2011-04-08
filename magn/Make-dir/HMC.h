#include "WProgram.h"
#include <Wire.h>

#ifndef HMC_h
#define HMC_h

#define HMC5843_ADDR 0x1E // 7 bit address of the HMC5843 used with the Wire library
#define HMC_POS_BIAS 1
#define HMC_NEG_BIAS 2
// HMC5843 register map. For details see HMC5843 datasheet
#define HMC5843_R_CONFA 0
#define HMC5843_R_CONFB 1
#define HMC5843_R_MODE 2
#define HMC5843_R_XM 3
#define HMC5843_R_XL 4
#define HMC5843_R_YM 5
#define HMC5843_R_YL 6
#define HMC5843_R_ZM 7
#define HMC5843_R_ZL 8
#define HMC5843_R_STATUS 9
#define HMC5843_R_IDA 10
#define HMC5843_R_IDB 11
#define HMC5843_R_IDC 12

class HMC5843 {
  public:
    HMC5843();
    void init(bool setmode);
    void init(int address, bool setmode);
    void getValues(int *x,int *y,int *z);
    void getValues(float *x,float *y,float *z);
    void getValues(float *xyz);
    void calibrate(unsigned char gain);
    void setMode(unsigned char mode);
    void setDOR(unsigned char DOR);
    void setGain(unsigned char gain);
  private:
    void writeReg(unsigned char reg, unsigned char val);
    float x_scale,y_scale,z_scale,x_max,y_max,z_max;
};
#endif // HMC_h

