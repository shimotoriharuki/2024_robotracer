/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SPI2_MISO_GP_Pin GPIO_PIN_2
#define SPI2_MISO_GP_GPIO_Port GPIOC
#define SPI2_MOSI_GP_Pin GPIO_PIN_3
#define SPI2_MOSI_GP_GPIO_Port GPIOC
#define ADC1_IN0_SENSOR0_Pin GPIO_PIN_0
#define ADC1_IN0_SENSOR0_GPIO_Port GPIOA
#define ADC1_IN1_SENSOR1_Pin GPIO_PIN_1
#define ADC1_IN1_SENSOR1_GPIO_Port GPIOA
#define ADC1_IN2_SENSOR2_Pin GPIO_PIN_2
#define ADC1_IN2_SENSOR2_GPIO_Port GPIOA
#define ADC1_IN3_SENSOR3_Pin GPIO_PIN_3
#define ADC1_IN3_SENSOR3_GPIO_Port GPIOA
#define ADC1_IN4_SENSOR_L_Pin GPIO_PIN_4
#define ADC1_IN4_SENSOR_L_GPIO_Port GPIOA
#define ADC1_IN5_SENSOR_R_Pin GPIO_PIN_5
#define ADC1_IN5_SENSOR_R_GPIO_Port GPIOA
#define ADC1_IN6_BATT_Pin GPIO_PIN_6
#define ADC1_IN6_BATT_GPIO_Port GPIOA
#define GPIO_INPUT_SW0_Pin GPIO_PIN_7
#define GPIO_INPUT_SW0_GPIO_Port GPIOA
#define GPIO__INPUT_SW1_Pin GPIO_PIN_4
#define GPIO__INPUT_SW1_GPIO_Port GPIOC
#define GPIO_INPUT_SW2_Pin GPIO_PIN_5
#define GPIO_INPUT_SW2_GPIO_Port GPIOC
#define GPIO_INPUT_SW3_Pin GPIO_PIN_0
#define GPIO_INPUT_SW3_GPIO_Port GPIOB
#define GPIO_INPUT_SW4_Pin GPIO_PIN_1
#define GPIO_INPUT_SW4_GPIO_Port GPIOB
#define I2C2_SCL_LCD_Pin GPIO_PIN_10
#define I2C2_SCL_LCD_GPIO_Port GPIOB
#define I2C2_SDA_LCD_Pin GPIO_PIN_11
#define I2C2_SDA_LCD_GPIO_Port GPIOB
#define SPI2_SCK_GP_Pin GPIO_PIN_13
#define SPI2_SCK_GP_GPIO_Port GPIOB
#define TIM12_CH1_BZ_Pin GPIO_PIN_14
#define TIM12_CH1_BZ_GPIO_Port GPIOB
#define TIM12_CH2_GP_Pin GPIO_PIN_15
#define TIM12_CH2_GP_GPIO_Port GPIOB
#define TIM3_CH1_ENC2_Pin GPIO_PIN_6
#define TIM3_CH1_ENC2_GPIO_Port GPIOC
#define TIM3_CH2_ENC2_Pin GPIO_PIN_7
#define TIM3_CH2_ENC2_GPIO_Port GPIOC
#define TIM8_CH4_SENSOR_PWM_Pin GPIO_PIN_9
#define TIM8_CH4_SENSOR_PWM_GPIO_Port GPIOC
#define TIM1_CH1_MOTOR1_Pin GPIO_PIN_8
#define TIM1_CH1_MOTOR1_GPIO_Port GPIOA
#define TIM1_CH3_MOTOR2_Pin GPIO_PIN_10
#define TIM1_CH3_MOTOR2_GPIO_Port GPIOA
#define GPIO_INPUT_SD_Pin GPIO_PIN_15
#define GPIO_INPUT_SD_GPIO_Port GPIOA
#define TIM4_CH1_ENC1_Pin GPIO_PIN_6
#define TIM4_CH1_ENC1_GPIO_Port GPIOB
#define TIM4_CH2_ENC1_Pin GPIO_PIN_7
#define TIM4_CH2_ENC1_GPIO_Port GPIOB
#define I2C1_SCL_IMU_Pin GPIO_PIN_8
#define I2C1_SCL_IMU_GPIO_Port GPIOB
#define I2C1_SDA_IMU_Pin GPIO_PIN_9
#define I2C1_SDA_IMU_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
