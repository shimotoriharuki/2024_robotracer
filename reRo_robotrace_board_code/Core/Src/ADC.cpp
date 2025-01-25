/*
 * ADC.cpp
 *
 *  Created on: Jun 25, 2023
 *      Author: SHIMOTORI Haruki
 */

#include "ADC.hpp"
#include "main.h"

ADConverter::ADConverter()
{
	for(auto &av : analog_val_){
		av = 0;
	}

}

void ADConverter::init()
{
	HAL_TIM_PWM_Start_IT(&htim5, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
	__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, 8999);

}

void ADConverter::start()
{
	//HAL_ADC_Start_DMA(&hadc1, (uint32_t *) analog_val_, ADC_DATA_SIZE);

	HAL_ADC_Start_DMA(&hadc1, (uint32_t *) analog_val_, 4);
}


