/*
 * encoder2.cpp
 *
 *  Created on: Nov 16, 2025
 *      Author: tue
 */
#include "encoder2.h"

encoder_config as5048a = {
	.register_NOP = 0x0000,
	.register_clear_error_flag = 0x0001,
	.register_programming_control = 0x0003,
	.register_zero_position_high = 0x0016,
	.register_zero_position_low = 0x0017,
	.register_AGC = 0x3FFD,
	.register_magnitude = 0x3FFE,
	.register_angle = 0x3FFF,
	.resolution = 16384 // 0 to 16383 (full=16384=2^14)
};

encoder2::encoder2(encoder_config config, uint16_t cs_pin, GPIO_TypeDef *cs_port, SPI_HandleTypeDef *hspi)
{
	_config = config;
	_cs_pin = cs_pin;
	_cs_port = cs_port;
	_hspi = hspi;
}

uint8_t encoder2::parity_count(uint16_t package_value)
{
	package_value ^= package_value >> 8;
	package_value ^= package_value >> 4;
	package_value ^= package_value >> 2;
	package_value ^= package_value >> 1;
	return package_value & 1;
}

void encoder2::encoder_init()
{
	if (_cs_pin == 0 || _cs_port == NULL || _hspi == NULL)
	{
	}
	else
		set_cs_high;
	encoder_update();
	previous_raw_data = current_raw_data;
	previous_tick = HAL_GetTick();
}

void encoder2::encoder_update()
{
	current_raw_data = encoder_read_raw_data();
	update_state(current_raw_data);
	current_position_degree = (int16_t)((current_raw_data * 360UL) / (uint32_t)_config.resolution);
	current_position_rad = (current_raw_data / (float)_config.resolution) * 2.0000f * (float)M_PI;
}

uint16_t encoder2::encoder_read_from_register(uint16_t _register)
{
	uint8_t data[2];

	uint16_t command = 0b0100000000000000; // PAR=0 R/W=R
	command = command | _register;

	// Add a parity bit on the the MSB
	command |= ((uint16_t)parity_count(command) << 15);

	// Split the command into two bytes
	data[1] = command & 0xFF;
	data[0] = (command >> 8) & 0xFF;

	set_cs_low;
	HAL_SPI_Transmit(_hspi, (uint8_t *)&data, 2, 0xFFFF);
	while (HAL_SPI_GetState(_hspi) != HAL_SPI_STATE_READY)
	{
	}
	set_cs_high;

	set_cs_low;
	HAL_SPI_Receive(_hspi, (uint8_t *)&data, 2, 0xFFFF);
	while (HAL_SPI_GetState(_hspi) != HAL_SPI_STATE_READY)
	{
	}
	set_cs_high;

	if (data[1] & 0x40)
	{
		error = 1;
	}
	else
	{
		error = 0;
	}

	// Return the data, stripping the parity and error bits
	return (((data[1] & 0xFF) << 8) | (data[0] & 0xFF)) & ~0xC000;
}

uint16_t encoder2::encoder_read_raw_data()
{
	return encoder::encoder_read_from_register(_config.register_angle);
}

void encoder2::update_state(uint16_t raw)
{
	int32_t delta = (int32_t)raw - (int32_t)previous_raw_data;

	if (delta < -(int32_t)_config.resolution / 2)
	{
		current_rotation++;
		delta += 16384;
	}
	else if (delta > (int32_t)_config.resolution / 2)
	{
		current_rotation--;
		delta -= 16384;
	}

	uint32_t current_tick = HAL_GetTick();
	uint32_t delta_time_ms = current_tick - previous_tick;
	if (delta_time_ms > 0)
	{
		float delta_rad = (delta / (float)_config.resolution) * 2.0000f * (float)M_PI;
		float delta_time_s = delta_time_ms / 1000.0000f;
		current_velocity = delta_rad / delta_time_s;
	} // Giữ velocity cũ nếu delta_time = 0

	previous_raw_data = raw;
	previous_tick = current_tick;
}

int8_t encoder2::encoder_read_rotation()
{
	return current_rotation;
}

int16_t encoder2::encoder_read_position_degree()
{
	return current_position_degree; //(0-359)
}

int16_t encoder2::encoder_read_position_rad()
{
	return current_position_rad; //(0-2π)
}

float encoder2::encoder_read_velocity()
{
	return current_velocity;
}

int32_t encoder2::encoder_read_accumulate_position_degree()
{
	return (int32_t)(current_position_degree + current_rotation * 360);
}

float encoder2::encoder_read_accumulate_position_rad()
{
	return (float)(current_position_rad + current_rotation * 2.0000f * (float)M_PI);
}
