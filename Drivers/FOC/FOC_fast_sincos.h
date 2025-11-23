/*
 * FOC_fast_sincos.h
 *
 *  Created on: Nov 23, 2025
 *      Author: tue
 */

#ifndef FOC_FOC_FAST_SINCOS_H_
#define FOC_FOC_FAST_SINCOS_H_

#include <stdint.h>
//#include "as5048a_lut_14bit.h"

#define LUT_SIZE 16384
#define USE_DEGREES

float LUT_Sin(uint16_t raw_angle);
float LUT_Cos(uint16_t raw_angle);

#endif /* FOC_FOC_FAST_SINCOS_H_ */
