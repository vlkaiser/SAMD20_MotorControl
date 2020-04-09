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
 * @note				- ToDo: Is SERCOM4  OK for this, or will it interfere with i2c?
 ******************************************************************************************************/
void config_UART(void)
{
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);

	config_usart.baudrate    = 9600;						
	config_usart.mux_setting = USART_RX_1_TX_0_XCK_1;
	config_usart.pinmux_pad0 = PINMUX_PB08D_SERCOM4_PAD0;	// PB08 = TX
	config_usart.pinmux_pad1 = PINMUX_PB09D_SERCOM4_PAD1;	// PB09 = RX
	config_usart.pinmux_pad2 = PINMUX_UNUSED;
	config_usart.pinmux_pad3 = PINMUX_UNUSED;
	
	while (usart_init(&usart_instance, SERCOM4, &config_usart) != STATUS_OK)
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

