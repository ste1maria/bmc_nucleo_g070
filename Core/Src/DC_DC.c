#include "DC_DC.h"
#include "main.h"

void init_dc_dc_setup(void);

static void handle_PG_OK(uint16_t GPIO_Pin);
static void handle_PG_failed(uint16_t GPIO_Pin);

static void handle_temperature_OK();
static void handle_temperature_not_OK();

static void handle_ALERTn_FAULTn();
static void handle_ALERT_FAULT();

void init_dc_dc_setup(void){

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

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin){

	if (GPIO_Pin != _0V9_ALERTn_FAULTn_Pin && GPIO_Pin != _5V_DRMOS_THWN_Pin) {
		handle_PG_failed(GPIO_Pin);
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
			handle_PG_OK(GPIO_Pin) ;
	}
	else if (GPIO_Pin == _0V9_ALERTn_FAULTn_Pin){
		handle_ALERT_FAULT();
	}
	else if (GPIO_Pin == _5V_DRMOS_THWN_Pin){
		handle_temperature_not_OK();
	}
}
