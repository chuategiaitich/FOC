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

typedef enum {
	OpenLoop = 0,
	Velocity = 1,
	Position = 2,
	Torque = 3,
	MIT = 4,
	Calibration = 5,
	Test = 6
} Mode;

//enum Mode
//{
//	Open_Loop = 0,
//	Closed_Loop = 1
//};

typedef struct {
    // Motor specs
    uint8_t pole_pairs;           // Số cặp cực (VD: 7)

    // Control limits
    float voltage_limit;          // Giới hạn điện áp (V)
    float velocity_limit;         // Giới hạn vận tốc (rad/s)

    // System parameters
    float v_bus;                  // Điện áp bus DC (V)
    float pwm_period;             // PWM period (ARR value)
    float control_period;         // Control loop period (seconds)

    // Open-loop state
    float target_velocity;        // Vận tốc đặt (rad/s)
    float electrical_angle;       // Góc điện hiện tại (rad)

    // Voltage setpoints (dq frame)
    float voltage_q;              // q-axis voltage (torque)
    float voltage_d;              // d-axis voltage (flux) - thường = 0

    // Status
    uint8_t enabled;              // Motor enable flag

} Motor_t;

void Motor_Init(hmotor *mt);
//void update_openloop(float *theta, float *freq);

uint16_t Electric_Angle(uint16_t angle);

void Motor_SetOpenLoopVelocity(Motor_t *m, float velocity_rad_s);

// Đặt điện áp open-loop
void Motor_SetOpenLoopVoltage(Motor_t *m, float voltage);

uint8_t SVPWM_get_sector(float V_alpha, float V_beta);
void SpaceVectorPWM();

#endif /* FOC_FOC_H_ */
