/*
 * DC_peripherals.c
 *
 * Created: 3/25/2020 1:05:25 PM
 *  Author: VKaiser
 */ 

  #include <DC_peripherals.h>

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

	//config_whoami();	//Determine which motor board is connected to: before i2c_config

	system_interrupt_enable_global();
	
}

