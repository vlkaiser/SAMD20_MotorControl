/*
 * Encoder_AMT212C_V.c
 *
 * Created: 4/1/2020 2:06:04 PM
 *  Author: VKaiser
 */

 #include "Encoder_AMT212C.h"

 // Encoder Addresses
 uint8_t encRead_pos	= 0x78;
 uint8_t encRead_turns	= 0x7A;

 // Encoder Calculations
 uint8_t result_pos[5] = {0};
 uint32_t shift_position = 0;
 uint32_t result_position = 0;
 uint8_t result_tur[5] = {0,0,0,0,0};
 uint32_t result_turns = 0;
 BOOL zero_flag = 1;
 uint16_t rx_encIndex;

 /******************************************************************************************************
 * @fn					- config_EncUART
 * @brief				- setup USART for encoder communication on SERCOM3
 * @param[in]			- void
 * @return				- void
 *
 * @note				- ToDo: Is SERCOM3  OK for this, or will it interfere with i2c?
 ******************************************************************************************************/
void config_encUART(void)
{
	uint8_t statusMsg[] = "Configuring Encoder UART....\r\n";
	writeStr(statusMsg, sizeof(statusMsg));			//uart debug statement
	
	struct usart_config config_usart;
	usart_get_config_defaults(&config_usart);

	config_usart.baudrate    = 115200;						// boosted this above 115200 to overcome a ~10% latency issue
	config_usart.mux_setting = USART_RX_3_TX_2_XCK_3;
	config_usart.pinmux_pad0 = PINMUX_UNUSED;
	config_usart.pinmux_pad1 = PINMUX_UNUSED;
	config_usart.pinmux_pad2 = PINMUX_PA24C_SERCOM3_PAD2;	// PA24 = TX ENC_B
	config_usart.pinmux_pad3 = PINMUX_PA25C_SERCOM3_PAD3;	// PA25 = RX ENC_A
	
	while (usart_init(&usart_instance, SERCOM3, &config_usart) != STATUS_OK)
	{
		__ASM volatile ("nop");
	}

	usart_enable(&usart_instance);
}

/******************************************************************************************************
 * @fn					- config_Encoder
 * @brief				- Configure encoder pins
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
 void config_encoder(void)
 {
		uint8_t statusMsg[] = "Configuring Encoder....\r\n";
		writeStr(statusMsg, sizeof(statusMsg));			//uart debug statement

		struct port_config pin_conf;
		port_get_config_defaults(&pin_conf);

 		pin_conf.direction  = PORT_PIN_DIR_INPUT;
 		pin_conf.input_pull = PORT_PIN_PULL_UP;
 		port_pin_set_config(CHA_ENC, &pin_conf);
 		port_pin_set_config(CHB_ENC, &pin_conf);

 }

  /******************************************************************************************************
 * @fn					- config_ENCODER_UART
 * @brief				- setup USART for ENCODER communication on SERCOM____
 * @param[in]			- void
 * @return				- void
 *
 * @note				- ToDo: Is SERCOM3  OK for this, or will it interfere with i2c?
 ******************************************************************************************************/
void config_ENCODER_UART(void)
{
	usart_get_config_defaults(&config_ENC_usart);

	config_ENC_usart.baudrate    = 115200;						// boosted this above 115200 to overcome a ~10% latency issue
	config_ENC_usart.mux_setting = USART_RX_3_TX_2_XCK_3;
	config_ENC_usart.pinmux_pad0 = PINMUX_UNUSED;
	config_ENC_usart.pinmux_pad1 = PINMUX_UNUSED;
	config_ENC_usart.pinmux_pad2 = PINMUX_PA24C_SERCOM3_PAD2;	// PA24 = TX
	config_ENC_usart.pinmux_pad3 = PINMUX_PA25C_SERCOM3_PAD3;	// PA25 = RX
	
	while (usart_init(&usart_instance, SERCOM3, &config_ENC_usart) != STATUS_OK)
	{
		__ASM volatile ("nop");
	}

	usart_enable(&usart_instance);
}

 /******************************************************************************************************
 * @fn					- UART_GetChar
 * @brief				- 
 * @param[in]			- port
 *						- *ch
 * @return				- The status_code after the execution of usart_read_buffer_job (Success/Fail)
 *
 * @note				- status_code_enc is an instance of status_code
 ******************************************************************************************************/
enum status_code UART_GetChar(uint8_t port, uint8_t *ch)
{
	return usart_read_buffer_job(&usart_instance_ENC, ch, 1);
}

/******************************************************************************************************
* @fn					- UART_WriteString
* @brief				-
* @param[in]			- *buf 
*						- size
* @return				- void
*
* @note					- Expand to include ports?
******************************************************************************************************/
// Original Function - pending expansion for ports??
// enum status_code_enc UART_WriteString(/*uint8_t port, */uint8_t *buf, uint16_t size)
/*
{
	enum status_code ret;
	
	//if (port == 1)
	//{
	ret = usart_write_buffer_job(&usart_instance, buf, size);
	//}
	//else if(port == 0)
	//{
	//ret = usart_write_buffer_job(&usart_instance_ENC, buf, size);
	//}

	return ret;
}
*/
enum status_code UART_WriteString(uint8_t *buf, uint16_t size)
{
	//enum status_code_enc ret;	
	//ret = usart_write_buffer_job(&usart_instance, buf, size);
	//return ret;

	//why can't we...
	return usart_write_buffer_job(&usart_instance, buf, size);
}

 /******************************************************************************************************
 * @fn					- Get_Encoder
 * @brief				- 
 * @param[in]			- void
 * @return				- void
 *
 * @note				-
 ******************************************************************************************************/
//ToDO: Nothing calls get_encoder
void Get_Encoder(void)
{

	Get_EncPos();
	Get_EncTurns();

}

 /******************************************************************************************************
 * @fn					- Get_EncPos
 * @brief				- Read the position from the encoder
 * @param[in]			- void
 * @return				- void
 *
 * @note				-
 ******************************************************************************************************/
 void Get_EncPos(void)
 {
 	// Get Position
 	UART_WriteString(&encRead_pos, 1);
 	delay_us(4);
 	while(USART_data_available == false)
 	{
	 	//port_pin_set_output_level(Orange_LED, LED_0_ACTIVE);
 	}
 //	port_pin_set_output_level(Orange_LED, !LED_0_ACTIVE);
 	
 	if (rx_encIndex > 4)	// rx_index == 5 after a normal, successful read (but could be shifted to higher indices)
 	{
	 	for(uint16_t i = (rx_encIndex - 5); i < rx_encIndex; i++)
		{
		 	result_pos[i] = AtoH(tx_rx_buffer[i]);
	 	}
 	}
 	else
 	{
	 	// erroneous read, do not change result_pos[] from previous read
 	}
 	USART_data_available = false;
 	rx_encIndex = 0;
 	shift_position = (result_pos[0] << 12) | (result_pos[1] << 8) | (result_pos[2] << 4) | (result_pos[3]) ;
 	result_position = shift_position / 4;
 	
 	delay_ms(1);

 }

 /******************************************************************************************************
 * @fn					- Get_EncTurns
 * @brief				- Read the number of turns from the encoder
 * @param[in]			- void
 * @return				- void
 *
 * @note				-
 ******************************************************************************************************/
 //ToDO: rx_encIndex not being set/updated anywhere
 //ToDO: tx_rx_buffer populated from usart_read_callback
 
 void Get_EncTurns(void)
 {
 		// Get Turns
 		UART_WriteString(&encRead_turns, 1);
 		delay_us(4);
 		while(USART_data_available == false)
 		{
	 		//port_pin_set_output_level(Orange_LED, LED_0_ACTIVE);
 		}
 		//port_pin_set_output_level(Orange_LED, !LED_0_ACTIVE);
 		
 		if (rx_encIndex > 4)	// rx_index == 5 after a normal, successful read (but could be shifted to higher indices)
 		{
	 		for(uint16_t i = (rx_encIndex - 5); i < rx_encIndex; i++)
			{
		 		result_tur[i] = AtoH(tx_rx_buffer[i]);
	 		}
 		}
 		else
 		{
	 		// erroneous read, do not change result_tur[] from previous read
 		}
 		USART_data_available = false;
 		rx_encIndex = 0;
 		result_turns = (result_tur[0] << 12) | (result_tur[1] << 8) | (result_tur[2] << 4) | (result_tur[3]); // CAN NOT be negative (Ascii does not have neg/ tx_rx_buffer is UINT)
 		
 		if(result_tur[0] == 0x03 && result_tur[1] == 0x0f)
 		{
	 		zero_flag = 0;
	 	}
		else
		{
	 		zero_flag = 0x04;
 		}
 		
 		delay_ms(1);

 }