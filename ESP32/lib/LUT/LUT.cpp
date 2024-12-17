#include "LUT.h"

float sinLUT[LUT_SIZE];
float cosLUT[LUT_SIZE];
float asinLUT[LUT_SIZE];
float acosLUT[LUT_SIZE];
float atanLUT[LUT_SIZE];

void initLUT()
{
    for(int i = 0;i < LUT_SIZE;i++)
    {
        float angle = i * PI / 1800;
        sinLUT[i] = sin(angle);
        cosLUT[i] = cos(angle);
        asinLUT[i] = asin(angle);
        acosLUT[i] = acos(angle);
        atanLUT[i] = atan(angle);
    }
}