/*
 * FOC_Math.h
 *
 *  Created on: Nov 17, 2025
 *      Author: ADMIN
 */

#ifndef FOC_FOC_MATH_H_
#define FOC_FOC_MATH_H_

#include "FOC_fast_sincos.h"

#define T_SQRT3					1.732050808f
#define T_1_DEVIDE_SQRT3		0.577350269f
#define T_2_DEVIDE_SQRT3		1.154700538f
#define T_SQRT3_DEVIDE_2		0.866025404f

#define T_PI					3.141592653f
#define T_2PI					6.283185307f
#define T_PI_DEVIDE_2			1.570796326f
#define T_PI_DEVIDE_4			0.785398163f
#define T_2PI_DEVIDE_3			2.094395102f
#define T_3PI_DEVIDE_2			4.712388980f

#define CLAMP(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

//typedef struct {
//    float ia, ib, ic;
//    float ialpha, ibeta;
//    float id, iq;
//    float angle_el;
//    float sin, cos;
//} Current_t;

void Transform_Clarke(float I_a, float I_b, float *I_alpha, float *I_beta);
void Transform_Inverse_Clarke(float I_alpha, float I_beta, float *I_a,
		float *I_b, float *I_c);
void Transform_Park(float I_alpha, float I_beta, float *I_d, float *I_q,
		float sin_theta, float cos_theta);
void Transform_Inverse_Park(float I_d, float I_q, float *I_alpha, float *I_beta,
		float sin_theta, float cos_theta);

#endif /* FOC_FOC_MATH_H_ */
