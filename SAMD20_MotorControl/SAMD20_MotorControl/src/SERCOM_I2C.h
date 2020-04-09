/*
 * SERCOM_I2C.h
 *
 * Created: 4/9/2020 5:04:45 PM
 *  Author: VKaiser
 */ 


#ifndef SERCOM_I2C_H_
#define SERCOM_I2C_H_

#include "main.h"

/* the Data Packing of these structs mean that uint32s should come before uint8s or bytes could be lost */
	struct cmd_issued
	{
		uint32_t encLocMoveTo;
		uint8_t cmdID;
	
	};
	struct cmd_issued cmd_sent;
	struct cmd_issued cmd_processed;

	struct cmd_response
	{
		uint32_t encoderLoc;

		uint8_t lastCmdRxd;
		uint8_t lastCmdStatus;
		uint8_t ID;
		uint8_t config;
		uint8_t status;
		uint8_t motorStatus;
	
		/*
		uint32_t voltage5V;
		uint32_t current5V;
		uint32_t peakCurrent5V;
		uint32_t voltage24V;
		uint32_t current24V;
		uint32_t peakCurrent24V;
		uint32_t voltage400V;		//future
		uint32_t current400V;		//future
		uint32_t peakCurrent400V;	//future

		uint32_t pcbTemp;
		*/
	};

struct cmd_response cmd_resp;
struct cmd_response cmd_resp_copy;

BOOL flgcmdRx;		//Flag for command received 

/******************* Prototypes *******************/

void configure_i2c_slave(void);
void configure_i2c_slave_callbacks(void);
void i2c_write_complete_callback(struct i2c_slave_module *const module);
void i2c_read_complete_callback(struct i2c_slave_module *const module);
void i2c_read_request_callback(	struct i2c_slave_module *const module);
void i2c_write_request_callback( struct i2c_slave_module *const module);


#endif /* SERCOM_I2C_H_ */