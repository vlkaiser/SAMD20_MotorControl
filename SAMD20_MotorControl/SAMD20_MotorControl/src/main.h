/*
 * main.h
 *
 * Created: 3/25/2020 1:08:59 PM
 *  Author: VKaiser
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include <asf.h>
#include "user_board.h"
#include "stdio.h"
#include "string.h"
#include "Ascii2Hex.h"

#include "DC_TypeDefs.h"
#include "GPIO_Peripherals.h"
#include "Motors_4118S-04SD.h"
#include "SERCOM_USART.h"
#include "Encoder_AMT212C.h"


/* Prototypes */
void writeStr(uint8_t *ptr, uint8_t len);
void Clear_Sleep_Timer(void);



#endif /* MAIN_H_ */