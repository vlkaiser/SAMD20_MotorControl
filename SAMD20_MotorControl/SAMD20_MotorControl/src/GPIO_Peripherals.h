/*
 * DC_peripherals.h
 *
 * Created: 3/25/2020 1:04:45 PM
 *  Author: VKaiser
 */ 


#ifndef DC_PERIPHERALS_H_
#define DC_PERIPHERALS_H_

#include "main.h"


/******************* Prototypes *******************/
void sys_config(void);

void config_GPIO(void);

void config_BOD(void);
void config_GCLK(void);
void config_WDT(void);
void config_WDT_Callback(void);
void watchdog_early_warning_callback(void);


#endif /* DC_PERIPHERALS_H_ */