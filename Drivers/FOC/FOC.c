/*
 * FOC.c
 *
 *  Created on: Nov 17, 2025
 *      Author: ADMIN
 */

#include "FOC.h"

Motor_t motor;

void Motor_Init(hmotor *mt) {

}

void Motor_SetOpenLoopVelocity(Motor_t *m, float velocity_rad_s) {
	m->open_loop_velocity = velocity_rad_s;
}

uint16_t Electric_Angle(uint16_t angle)
{
	uint16_t electric_angle = angle * motor.pole_pairs;
	return electric_angle;
}

// Đặt điện áp open-loop
void Motor_SetOpenLoopVoltage(Motor_t *m, float voltage) {
	m->voltage_limit = CLAMP(voltage, 0.0f, m->voltage_power_supply / 2.0f);
}

uint8_t SVPWM_get_sector(float V_alpha, float V_beta) {
	int VectorA = (V_beta > 0) ? 1 : 0;
	int VectorB = (T_SQRT3 * V_alpha - V_beta > 0) ? 1 : 0;
	int VectorC = (-T_SQRT3 * V_alpha - V_beta > 0) ? 1 : 0;
	return VectorA + 2 * VectorB + 4 * VectorC;  // Sector 1-6
}
void SpaceVectorPWM() {

}
//void SpaceVectorPWM()
//{
//    // Tính điện áp 3 pha
//    float U_dc = m->voltage_power_supply;
//    float sqrt3 = 1.732050808f;
//
//    // Inverse Clarke Transform (Modified SVPWM)
//    float U_a = V_alpha;
//    float U_b = -0.5f * V_alpha + 0.866025404f * V_beta;  // sqrt(3)/2
//    float U_c = -0.5f * V_alpha - 0.866025404f * V_beta;
//
//    // Normalize về duty cycle [0, 1]
//    float duty_a = (U_a / U_dc) + 0.5f;
//    float duty_b = (U_b / U_dc) + 0.5f;
//    float duty_c = (U_c / U_dc) + 0.5f;
//
//    // Clamp về [0, 1]
//    duty_a = CLAMP(duty_a, 0.0f, 1.0f);
//    duty_b = CLAMP(duty_b, 0.0f, 1.0f);
//    duty_c = CLAMP(duty_c, 0.0f, 1.0f);
//
//    // Ghi vào PWM registers
//    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (uint16_t)(duty_a * m->pwm_period));
//    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, (uint16_t)(duty_b * m->pwm_period));
//    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (uint16_t)(duty_c * m->pwm_period));
//}

//void update_openloop(float *theta, float freq)
//{
//    *theta += TWO_PI * freq * PWM_PERIOD;
//    if (*theta > TWO_PI) *theta -= TWO_PI;
//
//    float Vref = mod_index * VDC * MAX_MOD;
//    float V_alpha = Vref * LUT_Cos(*theta);
//    float V_beta = Vref * LUT_Sin(*theta);
//
//    // Normalize
//    float U = sqrt(3) * V_alpha / VDC;
//    float V = sqrt(3) * V_beta / VDC;
//    float W = -U - V;  // Vì U+V+W=0
//
//    // Sau đó dùng U,V,W để tính sector và thời gian
//}
