/*
 * DC_Motors.c
 *
 * Created: 3/25/2020 1:06:56 PM
 *  Author: VKaiser
 */ 

#include "DC_Motors.h"


/******************************************************************************************************
 * @fn					- configMotors()
 * @brief				- Port/pin config for motor driver and encoder signals, pushbutton, status led
 * @param[in]			- void
 * @return				- void
 *
 * @note				- called from main.c - test 
 ******************************************************************************************************/
 void configMotors(void)
 {
 	struct port_config pin_conf;
	port_get_config_defaults(&pin_conf);
	
	/* TODO: ConfigMotors for Motor Control Board */

		pin_conf.direction  = PORT_PIN_DIR_OUTPUT;
		pin_conf.input_pull = PORT_PIN_PULL_NONE;
		port_pin_set_config(DIR_PIN, &pin_conf);
		port_pin_set_config(PLS_PIN, &pin_conf);

		pin_conf.input_pull = PORT_PIN_PULL_DOWN;
		port_pin_set_config(STATUSLED, &pin_conf);
		
		pin_conf.direction  = PORT_PIN_DIR_INPUT;
		pin_conf.input_pull = PORT_PIN_PULL_UP;
		port_pin_set_config(CHA_ENC, &pin_conf);
		port_pin_set_config(CHB_ENC, &pin_conf);

		pin_conf.direction  = PORT_PIN_DIR_INPUT;
		pin_conf.input_pull = PORT_PIN_PULL_DOWN;
		port_pin_set_config(PBTN, &pin_conf);


	//TODO: Expand Daughter Card Motor Config
	port_pin_set_output_level(DIR_PIN, LOW);
	port_pin_set_output_level(PLS_PIN, LOW);

 }

/******************************************************************************************************
 * @fn					- motorCCW()
 * @brief				- Move motor Counter Clockwise 
 * @param[in]			- NumSpeed - delay time in ms
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
 /*
 void motorCCW(int NumSpeed)
 {
	//Rotates CW, slower.
	 for(int i = 0; i < NumSpeed; i++)
	 {
		port_pin_set_output_level(DIR_PIN, LOW);
		delay_ms(1);
		port_pin_set_output_level(PLS_PIN, LOW);
		delay_ms(10);
		port_pin_set_output_level(PLS_PIN, HIGH);
		delay_ms(5);
		}
 }
 */
