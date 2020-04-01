/*
 * SERCOM_USART.c
 *
 * Created: 3/26/2020 10:35:45 AM
 *  Author: VKaiser
 */ 
 
#include "SERCOM_USART.h"

BOOL start_msg = FALSE;

 /******************************************************************************************************
 * @fn					- config_UART
 * @brief				- setup USART for terminal communication on SERCOM3
 * @param[in]			- void
 * @return				- void
 *
 * @note				- ToDo: Is SERCOM3  OK for this, or will it interfere with i2c?
 ******************************************************************************************************/
void config_UART(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);

	config_usart.baudrate    = 115200;						// boosted this above 115200 to overcome a ~10% latency issue
	config_usart.mux_setting = USART_RX_3_TX_2_XCK_3;
	config_usart.pinmux_pad0 = PINMUX_UNUSED;
	config_usart.pinmux_pad1 = PINMUX_UNUSED;
	config_usart.pinmux_pad2 = PINMUX_PA24C_SERCOM3_PAD2;	// PA24 = TX
	config_usart.pinmux_pad3 = PINMUX_PA25C_SERCOM3_PAD3;	// PA25 = RX
	
	while (usart_init(&usart_instance, SERCOM3, &config_usart) != STATUS_OK)
	{
		__ASM volatile ("nop");
	}

	usart_enable(&usart_instance);
}


 /******************************************************************************************************
 * @fn					- config_UART_Callback
 * @brief				- Configure UART for Terminal communication, and Encoder communication
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void config_UART_Callback(void)
{
	usart_register_callback(&usart_instance, (usart_callback_t) usart_write_callback, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_register_callback(&usart_instance, (usart_callback_t) usart_read_callback, USART_CALLBACK_BUFFER_RECEIVED);
	usart_enable_callback(&usart_instance, USART_CALLBACK_BUFFER_TRANSMITTED);
	usart_enable_callback(&usart_instance, USART_CALLBACK_BUFFER_RECEIVED);

	//usart_register_callback(&usart_instance_ENC, (usart_callback_t) usart_write_callback_ENC, USART_CALLBACK_BUFFER_TRANSMITTED);
	//usart_register_callback(&usart_instance_ENC, (usart_callback_t) usart_read_callback_ENC, USART_CALLBACK_BUFFER_RECEIVED);
	//usart_enable_callback(&usart_instance_ENC, USART_CALLBACK_BUFFER_TRANSMITTED);
	//usart_enable_callback(&usart_instance_ENC, USART_CALLBACK_BUFFER_RECEIVED);
}

 /******************************************************************************************************
 * @fn					- usart_read_callback
 * @brief				- USART READ Callback
 * @param[in]			- const struct usart_module *const usart_module
 * @return				- void
 *
 * @note				- Calls UART_Continuous to look for next message
 ******************************************************************************************************/
void usart_read_callback(const struct usart_module *const usart_module)
{
	tx_rx_buffer[rx_index] = ch_buffer;
	tx_rx_buffer[rx_index+1] = 0;		// clear future buffer
	tx_rx_buffer[rx_index+2] = 0;		// clear future buffer
	rx_index++;

	if (ch_buffer == 0x0A)	// this is four because there are four chars plus a fifth "0x0A" at the end of every response from the encoder
	{
		USART_data_available = TRUE;
	}
	UART_Continuous();		// listen for next UART msg
}

 /******************************************************************************************************
 * @fn					- usart_write_callback
 * @brief				- USART Write Callback
 * @param[in]			- const struct usart_module *const usart_module
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void usart_write_callback(const struct usart_module *const usart_module)
{
	__ASM volatile ("nop");
}

 /******************************************************************************************************
 * @fn					- UART_Continuous
 * @brief				- Listen for next UART message
 * @param[in]			- void
 * @return				- void
 *
 * @note				- called from usart_read_callback
 ******************************************************************************************************/
void UART_Continuous(void)
{
	usart_read_buffer_job(&usart_instance, &ch_buffer, 1);
}
