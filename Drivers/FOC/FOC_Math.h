/*
 * FOC_Math.h
 *
 *  Created on: Nov 17, 2025
 *      Author: ADMIN
 */

#ifndef FOC_FOC_MATH_H_
#define FOC_FOC_MATH_H_

#include "FOC_fast_sincos.h"

#define ONE_DEVIDE_SQRT_THREE	0.577350269f
#define TWO_DEVIDE_SQRT_THREE	1.154700538f
#define SQRT_THREE_DEVIDE_TWO	0.866025404f

//typedef struct {
//    float ia, ib, ic;
//    float ialpha, ibeta;
//    float id, iq;
//    float angle_el;
//    float sin, cos;
//} Current_t;

void Transform_Clarke(float I_a, float I_b, float *I_alpha, float *I_beta);
void Transform_Inverse_Clarke(float I_alpha, float I_beta, float *I_a, float *I_b, float *I_c);
void Transform_Park(float I_alpha, float I_beta, float *I_d, float *I_q, float sin_theta, float cos_theta);
void Transform_Inverse_Park(float I_d, float I_q, float *I_alpha, float *I_beta, float sin_theta, float cos_theta);
void SpaceVectorPWM();


#endif /* FOC_FOC_MATH_H_ */
