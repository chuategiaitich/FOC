/*
 * FOC.h
 *
 *  Created on: Nov 17, 2025
 *      Author: ADMIN
 */

#ifndef FOC_FOC_H_
#define FOC_FOC_H_

#include "FOC_Math.h"
#include "FOC_PID.h"
#include "stdint.h"

typedef enum
{
	OpenLoop	=	0,
	Velocity	=	1,
	Position	=	2,
	Torque		=	3,
	MIT			=	4,
	Calibration	=	5,
	Test		=	6
}Mode;

//enum Mode
//{
//	Open_Loop = 0,
//	Closed_Loop = 1
//};

typedef struct
{
    uint8_t pole_pairs;
    float voltage_limit;
    float current_limit;

    float open_loop_velocity;	//rad/s
    float electrical_angle;		//rad
    float voltage_q;
    float voltage_d;

    uint16_t pwm_period;
    float voltage_power_supply;

    Mode Control_Mode;
}hmotor;

void Motor_Init(hmotor *mt);
void update_openloop(float *theta, float *freq);

#endif /* FOC_FOC_H_ */
