/*
 * encoder2.h
 *
 *  Created on: Nov 16, 2025
 *      Author: tue
 */

#ifndef INC_ENCODER2_H_
#define INC_ENCODER2_H_

#include "stm32f4xx_hal.h"
#include <math.h>

#define set_cs_high HAL_GPIO_WritePin(_cs_port, _cs_pin, GPIO_PIN_SET);
#define set_cs_low HAL_GPIO_WritePin(_cs_port, _cs_pin, GPIO_PIN_RESET);

struct encoder_config
{
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
};
extern encoder_config as5048a;

class encoder2
{
public:
	encoder2(encoder_config config, uint16_t cs_pin, GPIO_TypeDef *cs_port, SPI_HandleTypeDef *hspi);

	void encoder_init();
	// void 				encoder_close();
	// void 				encoder_write();
	uint16_t encoder_read_from_register(uint16_t _register);
	uint16_t encoder_read_raw_data();
	void encoder_update();

	int8_t encoder_read_rotation();

	int16_t encoder_read_position_degree();
	int16_t encoder_read_position_rad();

	int32_t encoder_read_accumulate_position_degree();
	float encoder_read_accumulate_position_rad();

	float encoder_read_velocity();

	uint16_t _cs_pin;
	GPIO_TypeDef *_cs_port;
	SPI_HandleTypeDef *_hspi;
	encoder_config _config;

	uint8_t error = 0;

private:
	uint8_t parity_count(uint16_t package_value);

	void update_state(uint16_t current_raw);

	uint16_t previous_raw_data = 0;
	uint32_t previous_tick = 0;

	uint16_t current_raw_data = 0;
	int16_t current_rotation = 0;
	int16_t current_position_degree = 0;
	float current_position_rad = 0.0000f;
	float current_velocity = 0.0000f;
};


#endif /* INC_ENCODER2_H_ */
