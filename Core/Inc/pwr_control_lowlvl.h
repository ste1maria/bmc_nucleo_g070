/*
 * pwr_control_lowlvl.h
 *
 *  Created on: Sep 10, 2021
 *      Author: leana
 */

#ifndef INC_PWR_CONTROL_LOWLVL_H_
#define INC_PWR_CONTROL_LOWLVL_H_

typedef enum  {
	DRMOS_STAGE,
	_5V_STAGE,
	_0V9_1V2_1V8_STAGE,
	_3V3_STAGE,
	DDR_STAGE,
	FINISHED_POWER_SETUP
} pwup_seq_stage;

void enable_power_curcuit(power_management_curcuit curcuit);

void disable_power_curcuit(power_management_curcuit curcuit);

 void start_first_pwup_seq_stage();

#endif /* INC_PWR_CONTROL_LOWLVL_H_ */
