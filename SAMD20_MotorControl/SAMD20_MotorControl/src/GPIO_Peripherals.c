/*
 * DC_peripherals.c
 *
 * Created: 3/25/2020 1:05:25 PM
 *  Author: VKaiser
 */

 #include <GPIO_Peripherals.h>



 /******************************************************************************************************
 * @fn					- SysTick_Handler
 * @brief				- SysTick handler interrupt override
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void SysTick_Handler(void)
{
	// Your code goes here
}

 /******************************************************************************************************
 * @fn					- config_BOD
 * @brief				- Configure Brown Out Detection
 * @param[in]			- void
 * @return				- void
 *
 * @note				- BOD33 threshold level is about 2.84V, set bod level to 39
 ******************************************************************************************************/
void config_BOD(void)
{
	#if (SAMD || SAMR21)
	struct bod_config config_bod33;
	bod_get_config_defaults(&config_bod33);
	config_bod33.action = BOD_ACTION_INTERRUPT;
	config_bod33.level = 39;						
	bod_set_config(BOD_BOD33, &config_bod33);
	bod_enable(BOD_BOD33);
	SYSCTRL->INTENSET.reg |= SYSCTRL_INTENCLR_BOD33DET;
	system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_SYSCTRL);
	#endif
}

 /******************************************************************************************************
 * @fn					- config_GCLK
 * @brief				- Configure and enable generic clock generator 1 (GENCTRL and GENDIV registers of GCLK module)
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void config_GCLK(void)
{
	struct system_gclk_gen_config gclk_gen_config1;
	system_gclk_gen_get_config_defaults(&gclk_gen_config1);
	gclk_gen_config1.source_clock = SYSTEM_CLOCK_SOURCE_ULP32K;
	gclk_gen_config1.division_factor = 8;
	gclk_gen_config1.output_enable = false;
	system_gclk_gen_set_config(GCLK_GENERATOR_1,&gclk_gen_config1);
	system_gclk_gen_enable(GCLK_GENERATOR_1);
}

 /******************************************************************************************************
 * @fn					- watchdog_early_warning_callback
 * @brief				- Trigger Orange Status LED
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void watchdog_early_warning_callback(void)
{
    port_pin_set_output_level(PIN_PA11, 1);		// Orange2 LED
}

/******************************************************************************************************
* @fn					- config_WDT
* @brief				- Create a new configuration structure for the Watchdog settings and fill 
*  						with the default module settings.
* @param[in]			- void
* @return				- void
*
* @note				-
******************************************************************************************************/
void config_WDT(void)
{
    struct wdt_conf config_wdt;
    wdt_get_config_defaults(&config_wdt);

    /* Set the Watchdog configuration settings */
    config_wdt.always_on            = false;
	config_wdt.clock_source			= GCLK_GENERATOR_1;
    config_wdt.timeout_period       = WDT_PERIOD_16384CLK;
    config_wdt.early_warning_period = WDT_PERIOD_8192CLK;

    /* Initialize and enable the Watchdog with the user settings */
    wdt_set_config(&config_wdt);
}

/******************************************************************************************************
* @fn					- config_WDT_Callback
* @brief				- Create a new configuration structure for the Watchdog settings and fill
*  						with the default module settings.
* @param[in]			- void
* @return				- void
*
* @note				-
******************************************************************************************************/
void config_WDT_Callback(void)
{
    wdt_register_callback(watchdog_early_warning_callback, WDT_CALLBACK_EARLY_WARNING);
    wdt_enable_callback(WDT_CALLBACK_EARLY_WARNING);
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
	SysTick_Config(system_gclk_gen_get_hz(GCLK_GENERATOR_0));
	delay_init();

	// Initialize USART
	config_UART();
	config_UART_Callback();
	
	// Initialize EEPROM
	//config_eeprom();
	config_BOD();
	
	// Initialize WDT	
	config_GCLK();
	config_WDT();
	config_WDT_Callback();
	
	// Initialize Timer
	//configure_timer();	

	system_interrupt_enable_global();
	
}

