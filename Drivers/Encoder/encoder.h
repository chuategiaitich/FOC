/*
 * encoder.h
 *
 *  Created on: Nov 17, 2025
 *      Author: ADMIN
 */

//	Datasheet:	https://www.mouser.com/datasheet/2/588/AS5048_DS000298_4-00-1100510.pdf		(as5048a)
/*
 *	SPI common package:
 *	bit | msb | 14 | 13 | 12 | 11 | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | lsb
 *   0  | par | RW | 13 | 12 | 11 | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | lsb
 *  {
 *		RW=0 (write), RW=1 (read)
 *      Par (even)
 *      Adress code: From bit 13 to bit  0 (lsb)
 *  }
 */

#ifndef ENCODER_ENCODER_H_
#define ENCODER_ENCODER_H_

#include "stm32f4xx_hal.h"
#include <math.h>

typedef struct {
	uint16_t _cs_pin;
	GPIO_TypeDef *_cs_port;
	SPI_HandleTypeDef *_hspi;

	uint16_t register_NOP;
	uint16_t register_clear_error_flag;
	uint16_t register_programming_control;
	uint16_t register_zero_position_high;
	uint16_t register_zero_position_low;
	uint16_t register_AGC;
	uint16_t register_magnitude;
	uint16_t register_angle;

	uint16_t resolution;
} encoder_config;

typedef struct {
	encoder_config _config;
	uint8_t error;

	uint16_t previous_raw_data;
	uint32_t previous_tick;

	uint16_t current_raw_data;
	int16_t current_rotation;
	int16_t current_position_degree;
	float current_position_rad;
	float current_velocity;
} encoder;

extern encoder_config as5048a;
extern encoder encoder_value;

void encoder_init(encoder *enc, encoder_config *config, uint16_t cs_pin,
		GPIO_TypeDef *cs_port, SPI_HandleTypeDef *hspi);
// void 				encoder_close();
// void 				encoder_write();
uint8_t parity_count(uint16_t package_value);
void encoder_update(encoder *enc);
void update_state(encoder *enc, uint16_t raw);
uint16_t encoder_read_from_register(encoder *enc, uint16_t _register);
uint16_t encoder_read_raw_data(encoder *enc);
int8_t encoder_read_rotation(encoder *enc);
int16_t encoder_read_position_degree(encoder *enc);
int16_t encoder_read_position_rad(encoder *enc);
int32_t encoder_read_accumulate_position_degree(encoder *enc);
float encoder_read_accumulate_position_rad(encoder *enc);
float encoder_read_velocity(encoder *enc);

#endif /* ENCODER_ENCODER_H_ */
