/*
 * debug_uart.c
 *
 *  Created on: Sep 2, 2021
 *      Author: leana
 */
#include "debug_uart.h"
#include "string.h"
#include "main.h"
/* FUNCTION DEFINITIONS */

static void send_console_greetings(void);
static void show_console_menu(void);

static void console_print_array(const char ** string_sequence);
static void console_print(char * message);

static void start_receive_routine(void);
static void stop_receive_routine(void);
/*------*/

/*  var-s */
extern  UART_HandleTypeDef huart1;
uint8_t service_UART_rx_buf;
/*----- */

void start_debug_session(void){
    send_console_greetings();

    show_console_menu();

    //start_receive_routine();
}

static void send_console_greetings(void){
	console_print("Hello");
}

static void show_console_menu(void){
	char  menu_header[]= "Service menu: \n\r ";

	const char *menu_entries[3];
	menu_entries[0] = "1 - show info;";
	menu_entries[1] ="2 - foo;";
	menu_entries[2] = "3 - bar;";

	console_print(menu_header);
	console_print_array(menu_entries);
	start_receive_routine();
}

static void console_print_array(const char ** string_sequence){
	size_t array_size = sizeof(string_sequence)/sizeof(char)-1;

	for (size_t index = 0; index < array_size; index++){
		char *test= string_sequence[index];
		console_print("\t");
		console_print(string_sequence[index]);
		console_print("\n\r");
	}
}

static void console_print(char * message){
	printf(message);
	//HAL_UART_Transmit(&huart1, &service_UART_rx_buf, sizeof(service_UART_rx_buf), HAL_MAX_DELAY);
}

/* Starts /restartsISR on UART RX line */
static void start_receive_routine(void){
	HAL_UART_Receive_IT(&huart1, (uint8_t*)&service_UART_rx_buf, sizeof(service_UART_rx_buf));
}


static void stop_receive_routine(void){
 //not used
}

