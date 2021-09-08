/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32g0xx_hal.h"

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
#define _0V9_PG_Pin GPIO_PIN_11
#define _0V9_PG_GPIO_Port GPIOC
#define BMC_FAN1_TACH_Pin GPIO_PIN_12
#define BMC_FAN1_TACH_GPIO_Port GPIOC
#define _5V_DRMOS_EN_Pin GPIO_PIN_14
#define _5V_DRMOS_EN_GPIO_Port GPIOC
#define _0V9_EN_Pin GPIO_PIN_15
#define _0V9_EN_GPIO_Port GPIOC
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOF
#define _1V2_EN_Pin GPIO_PIN_0
#define _1V2_EN_GPIO_Port GPIOC
#define _1V2_PG_Pin GPIO_PIN_2
#define _1V2_PG_GPIO_Port GPIOC
#define _0V9_ALERTn_FAULTn_Pin GPIO_PIN_3
#define _0V9_ALERTn_FAULTn_GPIO_Port GPIOC
#define _1V8_EN_Pin GPIO_PIN_0
#define _1V8_EN_GPIO_Port GPIOA
#define LED_GREEN_Pin GPIO_PIN_5
#define LED_GREEN_GPIO_Port GPIOA
#define DDR_VTT0_PG_Pin GPIO_PIN_4
#define DDR_VTT0_PG_GPIO_Port GPIOC
#define DDR_VTT1_PG_Pin GPIO_PIN_5
#define DDR_VTT1_PG_GPIO_Port GPIOC
#define DDR_VTT0_EN_Pin GPIO_PIN_13
#define DDR_VTT0_EN_GPIO_Port GPIOB
#define DDR_VTT1_EN_Pin GPIO_PIN_14
#define DDR_VTT1_EN_GPIO_Port GPIOB
#define DDR0_VPP_EN_Pin GPIO_PIN_15
#define DDR0_VPP_EN_GPIO_Port GPIOB
#define DDR1_VPP_EN_Pin GPIO_PIN_8
#define DDR1_VPP_EN_GPIO_Port GPIOA
#define BMC_FAN1_PWM_Pin GPIO_PIN_6
#define BMC_FAN1_PWM_GPIO_Port GPIOC
#define _5V_DRMOS_THWN_Pin GPIO_PIN_7
#define _5V_DRMOS_THWN_GPIO_Port GPIOC
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define _3V3_EN_Pin GPIO_PIN_15
#define _3V3_EN_GPIO_Port GPIOA
#define DDR0_VPP_PG_Pin GPIO_PIN_8
#define DDR0_VPP_PG_GPIO_Port GPIOC
#define _1V8_PG_Pin GPIO_PIN_0
#define _1V8_PG_GPIO_Port GPIOD
#define _3V3_PG_Pin GPIO_PIN_1
#define _3V3_PG_GPIO_Port GPIOD
#define _5V_DRMOS_PG_Pin GPIO_PIN_5
#define _5V_DRMOS_PG_GPIO_Port GPIOB
#define DDR1_VPP_PG_Pin GPIO_PIN_10
#define DDR1_VPP_PG_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
