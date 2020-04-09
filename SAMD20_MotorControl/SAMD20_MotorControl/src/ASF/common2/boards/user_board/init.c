/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>
#include "main.h"

#if defined(__GNUC__)
void board_init(void) WEAK __attribute__((alias("system_board_init")));
#elif defined(__ICCARM__)
void board_init(void);
#  pragma weak board_init=system_board_init
#endif

void system_board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
}

/******************************************************************************************************
 * @fn					- sys_config
 * @brief				- Calls all the config functions (called from main.c)
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void sys_config(void)
{
 	/*Configure system tick to generate periodic interrupts */
 	SysTick_Config(system_gclk_gen_get_hz(GCLK_GENERATOR_0));

	// Initialize UART - Terminal Debug (Debug On/Off in user_board.h)
	#ifdef DEBUG_WITH_UART
		config_UART();
	#endif

	// Config / Initialize Modules
	config_GPIO();
	//config_encUART();
	//config_encoder();
	//config_Motors();

	config_UART_Callback();		//Terminal UART, Encoder UART, BLE Callback?

	delay_init();

	// Initialize EEPROM
	//config_eeprom();
	//config_BOD();		// ToDO: Fix BOD -> DummyHandler
	
	// Initialize WDT	
	config_GCLK();	
	//config_WDT();		//ToDo: WDT Kicks us into reset handler every 4th loop
	//config_WDT_Callback();
	
	// Initialize Timer
	//configure_timer();	

	//Clear_Sleep_Timer();

	configure_i2c_slave();
	configure_i2c_slave_callbacks();

	system_interrupt_enable_global();
	
}