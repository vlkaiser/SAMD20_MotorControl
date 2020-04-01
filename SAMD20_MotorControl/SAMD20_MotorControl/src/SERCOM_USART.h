/*
 * SERCOM_USART.h
 *
 * Created: 3/26/2020 10:36:11 AM
 *  Author: VKaiser
 */ 

 /*
 APIs provided by the RS485 SERCOM USART driver are:
 ? void usart_get_config_defaults(struct usart_config *const config)
 ? enum status_code usart_init(struct usart_module *const module,Sercom *const hw, const
 struct usart_config *const config);
 ? void usart_enable(const struct usart_module *const module)
 ? void usart_disable(const struct usart_module *const module)
 ? void usart_reset(const struct usart_module *const module)
 */

#ifndef SERCOM_USART_H_
#define SERCOM_USART_H_

#include "main.h"

#define TIMEOUT 1000

#define MAX_UART_BUFFER_LENGTH   600

#define	UART_START_BYTE		0x02
#define UART_END_BYTE		0x03
#define UART_CR				0xD
#define UART_LF				0xA

#define READ_BUFFER_DATA_LENGTH 5
#define WRITE_BUFFER_DATA_LENGTH 256

// Terminal UART
struct usart_module usart_instance;
uint8_t ch_buffer;
uint8_t tx_rx_buffer[MAX_UART_BUFFER_LENGTH];
uint16_t rx_index;
BOOL USART_data_available;


void config_UART(void);
void config_UART_Callback(void);
//static void usart_read_callback(const struct usart_module *const usart_module);
//static void usart_write_callback(const struct usart_module *const usart_module);
void usart_read_callback(const struct usart_module *const usart_module);
void usart_write_callback(const struct usart_module *const usart_module);

void UART_Continuous(void);


#endif /* SERCOM_USART_H_ */