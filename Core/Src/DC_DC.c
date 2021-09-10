#include "DC_DC.h"
#include "main.h"
#include "stdbool.h"
#include "SMP_dialog.h"
/* -------- private variables --------- */

_Bool curciut_5V_THWN_OK = false;
_Bool curcuit_5V_PG_OK = false;
_Bool curcuit_0V9_notALERT_notFAULT= false;
_Bool curcuit_0V9_PG_OK = false;
_Bool curcuit_1V2_PG_OK = false;
_Bool curcuit_1V8_PG_OK = false;
_Bool curcuit_DDR_VTT0_PG_OK = false;
_Bool curcuit_DDR_VTT1_PG_OK = false;
_Bool curcuit_DDR0_PG_OK = false;
_Bool curcuit_DDR1_PG_OK = false;

typedef enum {
	mode_power_up,
	mode_power_down
} power_switch_mode;

power_switch_mode power_sequence_direction = mode_power_up;

/* declarations */
void start_power_up_sequence();
void start_power_down_sequence();

static void terminate_current_pwup_seq_stage();

static void handle_PG_OK(uint16_t GPIO_Pin);
static void handle_PG_failed(uint16_t GPIO_Pin);

static void handle_temperature_OK();
static void handle_temperature_not_OK();

static void handle_ALERTn_FAULTn();
static void handle_ALERT_FAULT();

static void set_power_up_stage(pwup_seq_stage stage);
static pwup_seq_stage get_power_up_stage();

/* -----------------DEFINITIONS ----------------- */
// stays here
void start_power_up_sequence(void){
	power_sequence_direction = mode_power_up;
	start_first_pwup_seq_stage();
}

// stays here
void start_power_down_sequence(void){
	power_sequence_direction = mode_power_down;
	terminate_current_pwup_seq_stage();
}

/* TODO: eliminate repeating code*/

// stays here - but clean up
static void terminate_current_pwup_seq_stage(){

	pwup_seq_stage stage = get_power_up_stage();

	if (stage == DRMOS_STAGE){
			// no change in stage, coz it is the first one
		//disable_power_curcuit();
	}
	else if (stage == _5V_STAGE) {
		disable_power_curcuit(curciut_DRMOS);
	}
	else if (stage == _0V9_1V2_1V8_STAGE) {
		set_power_up_stage(_5V_STAGE);

		disable_power_curcuit(curcuit_5V);
	}
	else if (stage == _3V3_STAGE){
		set_power_up_stage(_0V9_1V2_1V8_STAGE);

		disable_power_curcuit(curcuit_0V9);
		disable_power_curcuit(curcuit_1V2);
		disable_power_curcuit(curcuit_1V8);
	}
	else if (stage == DDR_STAGE){
		set_power_up_stage(_3V3_STAGE);

		disable_power_curcuit(curcuit_3V3);
	}
	else if (stage == FINISHED_POWER_SETUP){
		set_power_up_stage(DDR_STAGE);

		disable_power_curcuit(curcuit_DDR_VTT0);
		disable_power_curcuit(curcuit_DDR_VTT1);
		disable_power_curcuit(curcuit_DDR0);
		disable_power_curcuit(curcuit_DDR1);
	}
}


// stays here - but clean up (???)
static void run_next_power_up_stage(/*pwup_seq_stage current_stage*/){
	pwup_seq_stage current_stage = get_power_up_stage();

	switch (current_stage){
	case DRMOS_STAGE:
		//enable next curcuit
		set_power_up_stage(_0V9_1V2_1V8_STAGE);

		enable_next_curcuit(curcuit_0V9);
		enable_next_curcuit(curcuit_1V2);
		enable_next_curcuit(curcuit_1V8);

		break;

	case _0V9_1V2_1V8_STAGE:
		//enable next curcuit
		set_power_up_stage(_3V3_STAGE);

		enable_next_curcuit(curcuit_3V3);
		break;

	case _3V3_STAGE:
		//enable next curcuit
		set_power_up_stage(DDR_STAGE);

		enable_next_curcuit(curcuit_DDR_VTT0);
		enable_next_curcuit(curcuit_DDR_VTT1);
		enable_next_curcuit(curcuit_DDR0);
		enable_next_curcuit(curcuit_DDR1);
		break;

	case DDR_STAGE:
		//end power-up sequence
		set_power_up_stage(FINISHED_POWER_SETUP);

		/*enable SMP*/
		break;
	}
}

// stays here, but clean up
static void enable_next_curcuit(power_management_curcuit next_curcuit){
	/*
	 * 	curcuit_5V,			// NCP711 (enable, power good); NCP302035 ( temperature)
	curcuit_0V9,			// NCP4200
	curcuit_1V2,			// FAN23SV10MAMPX
	curcuit_1V8,			// NCP51402
	curcuit_3V3,			// NCP51402
	curcuit_DDR_VTT0,	// NCP51402
	curcuit_DDR_VTT1,	// NCP51402
	curcuit_DDR0,		// LD39100
	curcuit_DDR1		// LD39100
	 */
	switch (next_curcuit){
	case curcuit_5V:
		//enable next curcuit
		break;

	case curcuit_0V9:
	case curcuit_1V2:
	case curcuit_1V8:
		//enable next curcuit
		break;

	case curcuit_3V3:
		//enable next curcuit
		break;

	case curcuit_DDR_VTT0:
	case	curcuit_DDR_VTT1:
	case curcuit_DDR0:
	case curcuit_DDR1:
		//end power-up sequence
		break;
	}
}

// STAYS HERE, but clean up
static void handle_PG_OK(uint16_t GPIO_Pin){
	/*1) get the power-up sequence stage
	 * 2) set next power-up sequence stage
	 * 3) enable respective curcuit(s) - excluding the last one
	 */
	pwup_seq_stage stage = get_power_up_stage();

	if (stage == DRMOS_STAGE  && GPIO_Pin == _5V_DRMOS_EN_Pin) {
		if(curciut_5V_THWN_OK) {	// if THWN triggered before power good

			curcuit_5V_PG_OK = true;

			run_next_power_up_stage(current_stage = _0V9_1V2_1V8_STAGE);

			enable_power_curcuit(curcuit_0V9);
			enable_power_curcuit(curcuit_1V2);
			enable_power_curcuit(curcuit_1V8);
		}
		else {
			curcuit_5V_PG_OK = true;
		}
	}
	else if (stage == _0V9_1V2_1V8_STAGE) {
		if (GPIO_Pin == _0V9_PG_Pin){
				 curcuit_0V9_PG_OK = true;
		}
		else if (GPIO_Pin == _1V2_PG_Pin){
			curcuit_1V2_PG_OK = true;
		}
		else if (GPIO_Pin == _1V8_PG_Pin){
			curcuit_1V8_PG_OK = true;
		}

		if (curcuit_0V9_PG_OK \
				&& curcuit_1V2_PG_OK \
				&& curcuit_1V8_PG_OK \
				&& curcuit_0V9_notALERT_notFAULT) {

			set_power_up_stage(_3V3_STAGE);

			enable_power_curcuit(curcuit_3V3);
		}
	}
	else if (stage == _3V3_STAGE){
		set_power_up_stage(DDR_STAGE);

		enable_power_curcuit(curcuit_DDR_VTT0);
		enable_power_curcuit(curcuit_DDR_VTT1);
		enable_power_curcuit(curcuit_DDR0);
		enable_power_curcuit(curcuit_DDR1);
	}
	else if (stage == DDR_STAGE){

		if (GPIO_Pin == DDR_VTT0_PG_Pin){
			curcuit_DDR_VTT0_PG_OK = true;
		}
		else if(GPIO_Pin == DDR_VTT1_PG_Pin){
			curcuit_DDR_VTT1_PG_OK = true;
		}
		else if (GPIO_Pin == DDR0_VPP_PG_Pin){
			curcuit_DDR0_PG_OK = true;
		}
		else if (GPIO_Pin == DDR1_VPP_PG_Pin){
			curcuit_DDR1_PG_OK = true;
		}

		if (curcuit_DDR_VTT0_PG_OK \
				&& curcuit_DDR_VTT1_PG_OK \
				&& curcuit_DDR0_PG_OK \
				&&curcuit_DDR1_PG_OK){
			set_power_up_stage(FINISHED_POWER_SETUP);

		// ENABLE SMP
		// enable_SMP();
		}
	}
}

// STAYS HERE, but clean up
static void handle_PG_failed(uint16_t GPIO_Pin){
	/*1) get the power-up sequence stage
	 * 2) run reversed order set up
	 */
	if (GPIO_Pin == _5V_DRMOS_EN_Pin){
		curcuit_5V_PG_OK = false;
		//set_power_up_stage(DRMOS_STAGE);
	}
	else if (GPIO_Pin == _0V9_PG_Pin){
		 curcuit_0V9_PG_OK = false;
		//	set_power_up_stage(_0V9_1V2_1V8_STAGE);
	}
	else if (GPIO_Pin == _1V2_PG_Pin){
		curcuit_1V2_PG_OK = false;
	//	set_power_up_stage(_0V9_1V2_1V8_STAGE);
	}
	else if (GPIO_Pin == _1V8_PG_Pin){
		curcuit_1V8_PG_OK = false;
		//set_power_up_stage(_0V9_1V2_1V8_STAGE);
	}
	else	if (GPIO_Pin == DDR_VTT0_PG_Pin){
		curcuit_DDR_VTT0_PG_OK = false;
		//set_power_up_stage(DDR_STAGE);
	}
	else if(GPIO_Pin == DDR_VTT1_PG_Pin){
		curcuit_DDR_VTT1_PG_OK = false;
		//set_power_up_stage(DDR_STAGE);
	}
	else if (GPIO_Pin == DDR0_VPP_PG_Pin){
		curcuit_DDR0_PG_OK = false;
		//set_power_up_stage(DDR_STAGE);
	}
	else if (GPIO_Pin == DDR1_VPP_PG_Pin){
		curcuit_DDR1_PG_OK = false;
		//set_power_up_stage(DDR_STAGE);
	}

	// only if we were moving UP, should not repeat
	if (power_sequence_direction == mode_power_up){
		start_power_down_sequence();
	}
}

// STAYS HERE, but clean up
static void handle_temperature_OK(){
	curciut_5V_THWN_OK = true;

	// if power good triggered before THWN
	if (curcuit_5V_PG_OK && curciut_5V_THWN_OK ){
		enable_power_curcuit(curcuit_0V9);
		enable_power_curcuit(curcuit_1V2);
		enable_power_curcuit(curcuit_1V8);
		set_power_up_stage(_0V9_1V2_1V8_STAGE);
	}
}

// STAYS HERE, but clean up
static void handle_temperature_not_OK(){
	/*1) get the power-up sequence stage
	 * 2) run reversed order set up
	 */
	curciut_5V_THWN_OK = false;
	start_power_down_sequence();
}

// STAYS HERE, but clean up
static void handle_ALERTn_FAULTn(){
	/*1) get the power-up sequence stage
	 * 2) set next power-up sequence stage
	 */

	if (get_power_up_stage() == _0V9_1V2_1V8_STAGE){
		curcuit_0V9_notALERT_notFAULT = true;

		if (curcuit_0V9_PG_OK \
				&& curcuit_1V2_PG_OK \
				&& curcuit_1V8_PG_OK \
				&& curcuit_0V9_notALERT_notFAULT) {

			set_power_up_stage(_3V3_STAGE);

			enable_power_curcuit(curcuit_3V3);
		}
	}
}

// STAYS HERE, but clean up
static void handle_ALERT_FAULT(){
	/*1) get the power-up sequence stage
	 * 2) run reversed order set up
	 */
	curcuit_0V9_notALERT_notFAULT = false;
	start_power_down_sequence();
}

// STAYS HERE, but clean up
static void set_power_up_stage(pwup_seq_stage stage){
	power_up_sequence_stage = stage;
}

// STAYS HERE, but clean up
static  pwup_seq_stage get_power_up_stage(){
	return power_up_sequence_stage;
}
