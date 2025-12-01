/*
 * FOC.c
 *
 *  Created on: Nov 17, 2025
 *      Author: ADMIN
 */

#include "FOC.h"

void Motor_Init(hmotor *mt) {

}

void update_openloop(float *theta, float freq)
{
    *theta += TWO_PI * freq * PWM_PERIOD;
    if (*theta > TWO_PI) *theta -= TWO_PI;

    float Vref = mod_index * VDC * MAX_MOD;
    float V_alpha = Vref * LUT_Cos(*theta);
    float V_beta = Vref * LUT_Sin(*theta);

    // Normalize
    float U = sqrt(3) * V_alpha / VDC;
    float V = sqrt(3) * V_beta / VDC;
    float W = -U - V;  // Vì U+V+W=0

    // Sau đó dùng U,V,W để tính sector và thời gian
}
