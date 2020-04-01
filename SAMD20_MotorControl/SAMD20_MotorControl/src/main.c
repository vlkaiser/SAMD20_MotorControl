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
//ToDo: USART on NOT SERCOM3
//TODo: Communicate over terminal
//ToDo: USART ON SERCOM 3
//ToDo: Read Encoder
//ToDo: Report Encoder USART Terminal
//ToDo: Motor Control (Breakdown)


#include "main.h"

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




int main (void)
{
	system_init();
	sys_config();

	Clear_Sleep_Timer();

	uint8_t string[] = "Hello World!\r\n";
	usart_write_buffer_wait(&usart_instance, string, sizeof(string));

	while(1)
	{

		usart_read_buffer_job(&usart_instance, &ch_buffer, MAX_UART_BUFFER_LENGTH);
		delay_ms(500);
		UART_Continuous();


	}

}
