#include "DC_DC.h"
#include "main.h"

/* -------- private variables --------- */

typedef enum  {
	DRMOS_STAGE,
	_0V9_1V2_1V8_STAGE,
	_3V3_STAGE,
	DDR_STAGE
} pwup_seq_stage;

pwup_seq_stage power_up_sequence_stage;

typedef enum {
	curcuit_5V,			// NCP711 (enable, power good); NCP302035 ( temperature)
	curcuit_0V9,			// NCP4200
	curcuit_1V2,			// FAN23SV10MAMPX
	curcuit_1V8,			// NCP51402
	curcuit_3V3,			// NCP51402
	curcuit_DDR_VTT0,	// NCP51402
	curcuit_DDR_VTT1,	// NCP51402
	curcuit_DDR0,		// LD39100
	curcuit_DDR1		// LD39100
} power_management_curcuit;

/* declarations */
void init_dc_dc_setup(void);

static void handle_PG_OK(uint16_t GPIO_Pin);
static void handle_PG_failed(uint16_t GPIO_Pin);

static void handle_temperature_OK();
static void handle_temperature_not_OK();

static void handle_ALERTn_FAULTn();
static void handle_ALERT_FAULT();

static void enable_first_pwup_seq_stage();
static void enable_power_curcuit(power_management_curcuit curcuit);

/* ------- methods ------- */

void init_dc_dc_setup(void){
	enable_first_pwup_seq_stage();
}

/* TODO: eliminate repeating code*/

static void handle_PG_OK(uint16_t GPIO_Pin){
	/*1) get the power-up sequence stage
	 * 2) set next power-up sequence stage
	 */

}

static void handle_PG_failed(uint16_t GPIO_Pin){
	/*1) get the power-up sequence stage
	 * 2) run reversed order set up
	 */
}

static void handle_temperature_OK(){
	/*1) get the power-up sequence stage
	 * 2) set next power-up sequence stage
	 */
}

static void handle_temperature_not_OK(){
	/*1) get the power-up sequence stage
	 * 2) run reversed order set up
	 */
}

static void handle_ALERTn_FAULTn(){
	/*1) get the power-up sequence stage
	 * 2) set next power-up sequence stage
	 */
}

static void handle_ALERT_FAULT(){
	/*1) get the power-up sequence stage
	 * 2) set next power-up sequence stage
	 */
}

static void enable_first_pwup_seq_stage(){
	power_up_sequence_stage = DRMOS_STAGE;
	enable_power_curcuit(curcuit_5V);
}

static void enable_power_curcuit(power_management_curcuit curcuit){
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
		HAL_GPIO_WritePin(_3V_3_PG_GPIO_Port, _3V_3_PG_Pin, GPIO_PIN_SET);
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
