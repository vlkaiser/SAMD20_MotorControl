 /******************************************************************************************************
 * @fn					- 
 * @brief				- 
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/

/***************************************************************************************************************************
* Project							: SAMD20 Xplained (User Board) Motor Driver Demo
* Program Name						:
* Author							: vkaiser
* Date Created						: Mar 23 2020
*
* Purpose							: Develop motor/encoder control 
*
*
* MCU								: ATSAMD20J18
* Language							: C
* Hardware Modifications			: N/A
* Debugger							: EDBG (On-board)
*
* Repo / Revision History			: https://github.com/vlkaiser/
*
* - Special Setup -
*  Header files for all drivers that have been imported from Atmel Software Framework (ASF).
*  Use in conjunction with			: SAMD20 Xplained Pro; Lin 4118S-04S Motor, CUI AMT212C-V encoder, Oriental Motor CVD215-K Motor Driver (temp)
*  Wiring Details					: 
*  Revision History					:
* 	Date				Author			Notes
* 						vkaiser			- Initial commit
*
***************************************************************************************************************************/
//ToDo: ENCODER USART ON NOT I2C SERCOM
//ToDo: Read Encoder
//ToDo: Report Encoder USART Terminal
//ToDo: Motor Control (Breakdown)


#include "main.h"
//#include "stdio.h"

uint32_t timer_count;	// Sleep timer


/******************************************************************************************************
 * @fn					- Clear_Sleep_Timer
 * @brief				- Reset timer_count
 * @param[in]			- void
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
void Clear_Sleep_Timer(void)
{
	timer_count = 0;
}

/******************************************************************************************************
 * @fn					- writeStr
 * @brief				- write a string to the UART buffer
 * @param[in]			- *ptr to string
 * @return				- void
 *
 * @note				- If Debug with uart is defined (user_hoard.h)
 ******************************************************************************************************/
 void writeStr(uint8_t *ptr, uint8_t len)
 {
	#ifdef DEBUG_WITH_UART
		usart_write_buffer_wait(&usart_instance, ptr, len);
	#endif
 }
 
/******************************************************************************************************
 * @fn					- main
 * @brief				- Initialize and start main loop
 * @param[in]			- UART Terminal - 9600
 * @return				- void
 *
 * @note				- 
 ******************************************************************************************************/
// Debug Status Messages 

uint8_t statusCheck[] = "Hello World!\r\n";
uint8_t init[] = "Initializing...\r\n";
int main (void)
{
	system_init();
	sys_config();
	writeStr(init, sizeof(init));			//uart debug statement

	port_pin_set_output_level(STATUSLED_GREEN, TRUE);
	port_pin_set_output_level(STATUSLED_GREEN, FALSE);
	port_pin_set_output_level(STATUSLED_ORANGE, TRUE);

	writeStr(statusCheck, sizeof(init));
	
	__vo int i = 0;
	uint8_t loopCnt[] = "1\r\n";
	//uint8_t statusMsg[] = "OK\r\n";
	uint8_t statusReset[] = "Reset Counter\r\n";
	//uint8_t statusLoop[] = "Finished loop\r\n";

	while(1)
	{
		port_pin_set_output_level(STATUSLED_ORANGE, TRUE);
		delay_ms(500);
		port_pin_set_output_level(STATUSLED_ORANGE, FALSE);
		port_pin_set_output_level(STATUSLED_GREEN, TRUE);

		delay_ms(500);		// problem child
		port_pin_set_output_level(STATUSLED_GREEN, FALSE);
		
		// ToDo: TEMPORARY -> Count Loops
		loopCnt[0] = i + '0';

		writeStr(loopCnt, sizeof(loopCnt));		
		i++;
		if (i > 150) 
		{
			i = 0;
			for (int x = 0; x < 4; x++)
			{
				loopCnt[x] = 0;
			}
			writeStr(statusReset, sizeof(statusReset));
		}

	}


}
