/*
 * pwr_control_lowlvl.c
 *
 *  Created on: Sep 10, 2021
 *      Author: leana
 */
#include "main.h"
#include "pwr_control_lowlvl.h"

// TODO: try to make more compact
void enable_power_curcuit(power_management_curcuit curcuit){
	/* switch-case considered harmful, avoid */

	if (curcuit == curcuit_5V){
		HAL_GPIO_WritePin(_5V_DRMOS_EN_GPIO_Port, _5V_DRMOS_EN_Pin, GPIO_PIN_SET);
	}
	else if(curcuit == curcuit_0V9){
		HAL_GPIO_WritePin(_0V9_EN_GPIO_Port, _0V9_EN_Pin, GPIO_PIN_SET);
	}
	else if(curcuit == curcuit_1V2){
		HAL_GPIO_WritePin(_1V2_EN_GPIO_Port, _1V2_EN_Pin, GPIO_PIN_SET);
	}
	else if(curcuit == curcuit_1V8){
		HAL_GPIO_WritePin(_1V8_EN_GPIO_Port, _1V8_EN_Pin, GPIO_PIN_SET);
	}
	else if(curcuit == curcuit_3V3){
		HAL_GPIO_WritePin(_3V_3_PG_GPIO_Port, _3V3_EN_Pin, GPIO_PIN_SET);
	}
	else if(curcuit == curcuit_DDR_VTT0){
		HAL_GPIO_WritePin(DDR_VTT0_EN_GPIO_Port, DDR_VTT0_EN_Pin, GPIO_PIN_SET);
	}
	else if(curcuit == curcuit_DDR_VTT1){
		HAL_GPIO_WritePin(DDR_VTT1_EN_GPIO_Port, DDR_VTT1_EN_Pin, GPIO_PIN_SET);
	}
	else if(curcuit == curcuit_DDR0){
		HAL_GPIO_WritePin(DDR0_VPP_EN_GPIO_Port, DDR0_VPP_EN_Pin, GPIO_PIN_SET);
	}
	else if(curcuit == curcuit_DDR1){
		HAL_GPIO_WritePin(DDR1_VPP_EN_GPIO_Port, DDR1_VPP_EN_Pin, GPIO_PIN_SET);

	}
}

static void disable_power_curcuit(power_management_curcuit curcuit){
	/* switch-case considered harmful, avoid */

	if (curcuit == curcuit_5V){
		HAL_GPIO_WritePin(_5V_DRMOS_EN_GPIO_Port, _5V_DRMOS_EN_Pin, GPIO_PIN_RESET);
	}
	else if(curcuit == curcuit_0V9){
		HAL_GPIO_WritePin(_0V9_EN_GPIO_Port, _0V9_EN_Pin, GPIO_PIN_RESET);
	}
	else if(curcuit == curcuit_1V2){
		HAL_GPIO_WritePin(_1V2_EN_GPIO_Port, _1V2_EN_Pin, GPIO_PIN_RESET);
	}
	else if(curcuit == curcuit_1V8){
		HAL_GPIO_WritePin(_1V8_EN_GPIO_Port, _1V8_EN_Pin, GPIO_PIN_RESET);
	}
	else if(curcuit == curcuit_3V3){
		HAL_GPIO_WritePin(_3V_3_PG_GPIO_Port, _3V3_EN_Pin, GPIO_PIN_RESET);
	}
	else if(curcuit == curcuit_DDR_VTT0){
		HAL_GPIO_WritePin(DDR_VTT0_EN_GPIO_Port, DDR_VTT0_EN_Pin, GPIO_PIN_RESET);
	}
	else if(curcuit == curcuit_DDR_VTT1){
		HAL_GPIO_WritePin(DDR_VTT1_EN_GPIO_Port, DDR_VTT1_EN_Pin, GPIO_PIN_RESET);
	}
	else if(curcuit == curcuit_DDR0){
		HAL_GPIO_WritePin(DDR0_VPP_EN_GPIO_Port, DDR0_VPP_EN_Pin, GPIO_PIN_RESET);
	}
	else if(curcuit == curcuit_DDR1){
		HAL_GPIO_WritePin(DDR1_VPP_EN_GPIO_Port, DDR1_VPP_EN_Pin, GPIO_PIN_RESET);

	}
}

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin){

	if (GPIO_Pin != _0V9_ALERTn_FAULTn_Pin && GPIO_Pin != _5V_DRMOS_THWN_Pin) {
		handle_PG_OK(GPIO_Pin);
	}
	else if (GPIO_Pin == _0V9_ALERTn_FAULTn_Pin){
		handle_ALERTn_FAULTn();
	}
	else if (GPIO_Pin == _5V_DRMOS_THWN_Pin){
		handle_temperature_OK();
	}
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin){

	if (GPIO_Pin != _0V9_ALERTn_FAULTn_Pin && GPIO_Pin != _5V_DRMOS_THWN_Pin) {
		handle_PG_failed(GPIO_Pin) ;
	}
	else if (GPIO_Pin == _0V9_ALERTn_FAULTn_Pin){
		handle_ALERT_FAULT();
	}
	else if (GPIO_Pin == _5V_DRMOS_THWN_Pin){
		handle_temperature_not_OK();
	}
}
