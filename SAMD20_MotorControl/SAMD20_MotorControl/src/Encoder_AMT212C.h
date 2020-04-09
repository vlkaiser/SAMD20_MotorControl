/*
 * Encoder_AMT212C_V.h
 *
 * Created: 4/1/2020 2:06:14 PM
 *  Author: VKaiser
 */ 


#ifndef ENCODER_AMT212C_H_
#define ENCODER_AMT212C_H_

#include "main.h"

struct usart_module usart_instance_ENC;
struct usart_config config_ENC_usart;

//typedef enum status_code enum status_code_enc;

void config_encUART(void);
void config_encoder(void);
void config_ENCODER_UART(void);
void Get_Encoder(void);
void Get_EncTurns(void);
void Get_EncPos(void);

enum status_code UART_WriteString(uint8_t *buf, uint16_t size);
enum status_code UART_GetChar(uint8_t port, uint8_t *ch);

#endif /* ENCODER_AMT212C-V_H_ */