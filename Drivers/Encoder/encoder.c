/*
 * encoder.c
 *
 *  Created on: Nov 17, 2025
 *      Author: ADMIN
 */

#include "encoder.h"

encoder encoder_value;

encoder_config as5048a = { .register_NOP = 0x0000, .register_clear_error_flag =
		0x0001, .register_programming_control = 0x0003,
		.register_zero_position_high = 0x0016, .register_zero_position_low =
				0x0017, .register_AGC = 0x3FFD, .register_magnitude = 0x3FFE,
		.register_angle = 0x3FFF, .resolution = 16384 // 0 to 16383 (full=16384=2^14)
		};

uint8_t parity_count(uint16_t package_value) {
	package_value ^= package_value >> 8;
	package_value ^= package_value >> 4;
	package_value ^= package_value >> 2;
	package_value ^= package_value >> 1;
	return package_value & 1;
}

void encoder_init(encoder *enc, encoder_config *config, uint16_t cs_pin,
		GPIO_TypeDef *cs_port, SPI_HandleTypeDef *hspi) {
	if (cs_pin == 0 || cs_port == NULL || hspi == NULL) {
		return;
	}

	enc->_config = *config;
	enc->_config._cs_pin = cs_pin;
	enc->_config._cs_port = cs_port;
	enc->_config._hspi = hspi;

	HAL_GPIO_WritePin(enc->_config._cs_port, enc->_config._cs_pin,
			GPIO_PIN_SET);

	encoder_update(enc);

	enc->previous_raw_data = enc->current_raw_data;
	enc->previous_tick = HAL_GetTick();
}

void encoder_update(encoder *enc) {
	enc->current_raw_data = encoder_read_raw_data(enc);
	update_state(enc, enc->current_raw_data);
	enc->current_position_degree = (int16_t) ((enc->current_raw_data * 360UL)
			/ (uint32_t) enc->_config.resolution);
	enc->current_position_rad = (enc->current_raw_data
			/ (float) enc->_config.resolution) * 2.0000f * (float) M_PI;
}

uint16_t encoder_read_from_register(encoder *enc, uint16_t _register) {
	uint8_t data[2];
	uint16_t command = 0b0100000000000000; // PAR=0 R/W=R
	command = command | _register;

	// Add a parity bit on the the MSB
	command |= ((uint16_t) parity_count(command) << 15);

	// Split the command into two bytes
	data[1] = command & 0xFF;
	data[0] = (command >> 8) & 0xFF;

	HAL_GPIO_WritePin(enc->_config._cs_port, enc->_config._cs_pin,
			GPIO_PIN_RESET);

	HAL_SPI_Transmit(enc->_config._hspi, (uint8_t*) &data, 2, 0xFFFF);
	while (HAL_SPI_GetState(enc->_config._hspi) != HAL_SPI_STATE_READY) {
	}

	HAL_GPIO_WritePin(enc->_config._cs_port, enc->_config._cs_pin,
			GPIO_PIN_SET);

	HAL_GPIO_WritePin(enc->_config._cs_port, enc->_config._cs_pin,
			GPIO_PIN_RESET);
	HAL_SPI_Receive(enc->_config._hspi, (uint8_t*) &data, 2, 0xFFFF);
	while (HAL_SPI_GetState(enc->_config._hspi) != HAL_SPI_STATE_READY) {
	}

	HAL_GPIO_WritePin(enc->_config._cs_port, enc->_config._cs_pin,
			GPIO_PIN_SET);

	if (data[1] & 0x40) {
		enc->error = 1;
	} else {
		enc->error = 0;
	}

	// Return the data, stripping the parity and error bits
	return (((data[1] & 0xFF) << 8) | (data[0] & 0xFF)) & ~0xC000;
}

uint16_t encoder_read_raw_data(encoder *enc) {
	return encoder_read_from_register(enc, enc->_config.register_angle);
}

void update_state(encoder *enc, uint16_t raw) {
	int32_t delta = (int32_t) raw - (int32_t) enc->previous_raw_data;

	if (delta < -(int32_t) enc->_config.resolution / 2) {
		enc->current_rotation++;
		delta += 16384;
	} else if (delta > (int32_t) enc->_config.resolution / 2) {
		enc->current_rotation--;
		delta -= 16384;
	}

	uint32_t current_tick = HAL_GetTick();
	uint32_t delta_time_ms = current_tick - enc->previous_tick;
	if (delta_time_ms > 0) {
		float delta_rad = (delta / (float) enc->_config.resolution) * 2.0000f
				* (float) M_PI;
		float delta_time_s = delta_time_ms / 1000.0000f;
		enc->current_velocity = delta_rad / delta_time_s;
	}

	enc->previous_raw_data = raw;
	enc->previous_tick = current_tick;
}

int8_t encoder_read_rotation(encoder *enc) {
	return enc->current_rotation;
}

int16_t encoder_read_position_degree(encoder *enc) {
	return enc->current_position_degree;
}

int16_t encoder_read_position_rad(encoder *enc) {
	return enc->current_position_rad;
}

float encoder_read_velocity(encoder *enc) {
	return enc->current_velocity;
}

int32_t encoder_read_accumulate_position_degree(encoder *enc) {
	return (int32_t) (enc->current_position_degree + enc->current_rotation * 360);
}

float encoder_read_accumulate_position_rad(encoder *enc) {
	return (float) (enc->current_position_rad
			+ enc->current_rotation * 2.0000f * (float) M_PI);
}
