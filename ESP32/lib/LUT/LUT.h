#include <Arduino.h>
#include <math.h>

#define LUT_SIZE 3600

extern float sinLUT[LUT_SIZE];
extern float cosLUT[LUT_SIZE];
extern float asinLUT[LUT_SIZE];
extern float acosLUT[LUT_SIZE];
extern float atanLUT[LUT_SIZE];

void initLUT();