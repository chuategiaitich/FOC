/*
 * FOC_fast_sincos.c
 *
 *  Created on: Nov 23, 2025
 *      Author: tue
 */


#include "FOC_fast_sincos.h"
#include <math.h>

const int16_t sinLUT[LUT_SIZE] = {
    #include "sin_lt_values.inc"
};

const int16_t cosLUT[LUT_SIZE] = {
    #include "cos_lt_values.inc"
};

float LUT_Sin(uint16_t raw_angle) {
	raw_angle %= LUT_SIZE;
//    if (angle < 0) angle += LUT_SIZE;
    return (float)sinLUT[raw_angle]/32767.0f;
}

float LUT_Cos(uint16_t raw_angle) {
	raw_angle %= LUT_SIZE;
//    if (raw_angle < 0) angle += LUT_SIZE;
    return (float)cosLUT[raw_angle]/32767.0f;
}
