/*
 * FOC_Math.c
 *
 *  Created on: Nov 17, 2025
 *      Author: ADMIN
 */

#include "FOC_Math.h"

void Transform_Clarke(float I_a, float I_b, float *I_alpha, float *I_beta)
{
	*I_alpha	=	I_a;
	*I_beta 	=	ONE_DEVIDE_SQRT_THREE * I_a	+	TWO_DEVIDE_SQRT_THREE * I_b;
}
void Transform_Inverse_Clarke(float I_alpha, float I_beta, float *I_a, float *I_b, float *I_c)
{
	*I_a	=	I_alpha;
	*I_b	=	-0.5 * I_alpha	+	SQRT_THREE_DEVIDE_TWO * I_beta;
	*I_c	=	-0.5 * I_alpha	-	SQRT_THREE_DEVIDE_TWO * I_beta;
}

void Transform_Park(float I_alpha, float I_beta, float *I_d, float *I_q, float sin_theta, float cos_theta)
{
	*I_d	=	I_alpha * cos_theta		+	I_beta * sin_theta;
	*I_q	=	-I_alpha * sin_theta	+	I_beta * cos_theta;
}
void Transform_Inverse_Park(float I_d, float I_q, float *I_alpha, float *I_beta, float sin_theta, float cos_theta)
{
	*I_alpha	=	I_d * cos_theta	-	I_q * sin_theta;
	*I_beta		=	I_d * sin_theta	+	I_q * cos_theta;
}
void SpaceVectorPWM()
{

}
