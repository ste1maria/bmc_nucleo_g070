/*
 * fan.c
 *
 *  Created on: Sep 8, 2021
 *      Author: leana
 */
#include "main.h"
#include "fan.h"

#define TIM_PWM_CHANNEL_FAN_POWER TIM_CHANNEL_1
#define TIM_FAN_CHANNEL_FAN_CHECK TIM_CHANNEL_1
#define FAN_POWER_100_PERCENT 100
#define FAN_POWER_MAX	FAN_POWER_100_PERCENT

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim14;

void init_fan(void);
static void start_fan_power();
static void start_is_fan_okay_control();
static void set_fan_power(uint8_t pwm_duty_cycle);
void start_PWM_generation();

void init_fan(){
	start_fan_power();
	start_is_fan_okay_control();
}

static void start_fan_power(){
	start_pwm_generation();
	set_fan_power(FAN_POWER_MAX);
}

//TODO: find out average rpm
static void fan_check_running(){
	/*
	static uint16_t prev_capture;
	static uint8_t slow_fan_counter = FAN_SLOW_FILTER;
	uint16_t curr_capture = 0;
	FanCaptureCounter = CAPTURE_TIMEOUT;

	if(htim->Instance == TIM3) {
		curr_capture = HAL_TIM_ReadCapturedValue(&htim3, TIM_CHANNEL_1);

		if(curr_capture > prev_capture) {
			fan_rotation_period = curr_capture - prev_capture;
		}
		else {
			fan_rotation_period = (htim3.Instance->ARR - prev_capture) + curr_capture;				// average is no more than 12-13 ms
		}
		prev_capture = curr_capture;

		if(fan_rotation_period > MAX_ROTATION_PERIOD) {
			if(slow_fan_counter > 0) {
				slow_fan_counter--;
			}
			else {
				alarm_FanFault = SET_ALARM;
			}
		}
		else {
			slow_fan_counter = FAN_SLOW_FILTER;
			alarm_FanFault = RESET_ALARM;
		}
	}
	*/
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	fan_check_running();
}

static void start_is_fan_okay_control(){
	HAL_TIM_IC_Start_IT(&htim14, TIM_FAN_CHANNEL_FAN_CHECK);
}

static void set_fan_power(uint8_t pwm_duty_cycle){
	if (pwm_duty_cycle > FAN_POWER_100_PERCENT)
		pwm_duty_cycle = FAN_POWER_100_PERCENT;

	__HAL_TIM_SET_COMPARE(&htim14, TIM_PWM_CHANNEL_FAN_POWER, pwm_duty_cycle);
}

void start_pwm_generation(){
	HAL_TIM_PWM_Start(&htim3, TIM_PWM_CHANNEL_FAN_POWER);
}
