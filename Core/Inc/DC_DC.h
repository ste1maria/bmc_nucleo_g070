/*
 * DC_DC.h
 *
 *  Created on: Sep 2, 2021
 *      Author: leana
 */

#ifndef INC_DC_DC_H_
#define INC_DC_DC_H_

void start_power_up_sequence();

void handle_PG_OK(uint16_t GPIO_Pin);
void handle_PG_failed(uint16_t GPIO_Pin);

void handle_temperature_OK();
void handle_temperature_not_OK();

void handle_ALERTn_FAULTn();
void handle_ALERT_FAULT();

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

#endif /* INC_DC_DC_H_ */
