/*
 * SERCOM_I2C.c
 *
 * Created: 4/9/2020 5:04:35 PM
 *  Author: VKaiser
 */ 

#include "SERCOM_I2C.h"

/*
* Global Variables
*/
#define MAX_RX_BUFFER_LENGTH	256
#define I2C_TIMEOUT				10
#define CONF_I2C_SLAVE_MODULE   SERCOM2		//SERCOM port
//#define SLAVE_ADDRESS 0x12

struct i2c_slave_module i2c_slave_instance;
struct i2c_slave_config config_i2c_slave;
struct i2c_slave_packet rw_packet;

 /* Timeout counter. */
 uint16_t timeout = 0;

 /**********************************************************************
 * @fn					- configure_i2c_slave
 * @brief				- Initialize config structure and module instance
 *
 * @param[in]			- 
 * @return				- void
 *
 * @note				- 
 **********************************************************************/
void configure_i2c_slave(void)
{
	uint8_t statusMsg[] = "Configuring I2C Slave....\r\n";
	writeStr(statusMsg, sizeof(statusMsg));			//uart debug statement
	
	/* Initialize config structure and module instance */
	i2c_slave_get_config_defaults(&config_i2c_slave);

	/* Change address and address_mode */
	config_i2c_slave.address      = cmd_resp.ID;
	config_i2c_slave.address_mode = I2C_SLAVE_ADDRESS_MODE_MASK;

	/* Initialize and enable device with config */
	i2c_slave_init(&i2c_slave_instance, CONF_I2C_SLAVE_MODULE, &config_i2c_slave);

	i2c_slave_enable(&i2c_slave_instance);
}

/**********************************************************************
 * @fn					- configure_i2c_slave_callbacks
 * @brief				- Register and enable callback functions
 *
 * @param[in]			- 
 * @return				- void
 *
 * @note				- 
 **********************************************************************/
void configure_i2c_slave_callbacks(void)
{
	uint8_t statusMsg[] = "Configuring I2C Slave Callbacks....\r\n";
	writeStr(statusMsg, sizeof(statusMsg));			//uart debug statement

	/* Register and enable callback functions */
	i2c_slave_register_callback(&i2c_slave_instance, i2c_read_request_callback,	I2C_SLAVE_CALLBACK_READ_REQUEST);
	i2c_slave_enable_callback(&i2c_slave_instance,	I2C_SLAVE_CALLBACK_READ_REQUEST);

	i2c_slave_register_callback(&i2c_slave_instance, i2c_write_request_callback, I2C_SLAVE_CALLBACK_WRITE_REQUEST);
	i2c_slave_enable_callback(&i2c_slave_instance, I2C_SLAVE_CALLBACK_WRITE_REQUEST);

	i2c_slave_register_callback(&i2c_slave_instance, i2c_write_complete_callback, I2C_SLAVE_CALLBACK_WRITE_COMPLETE);
	i2c_slave_enable_callback(&i2c_slave_instance, I2C_SLAVE_CALLBACK_WRITE_COMPLETE);

	i2c_slave_register_callback(&i2c_slave_instance, i2c_read_complete_callback, I2C_SLAVE_CALLBACK_READ_COMPLETE);
	i2c_slave_enable_callback(&i2c_slave_instance, I2C_SLAVE_CALLBACK_READ_COMPLETE);
}


/**********************************************************************
 * @fn					- i2c_write_complete_callback
 * @brief				- i2c SLAVE write complete triggers this callback
 *
 * @param[in]			- struct i2c_slave_module
 * @param[in]			- *const module
 * @return				- void
 *
 * @note				- MASTER: i2c_read, SLAVE: write-to-buf Complete
 **********************************************************************/
void i2c_write_complete_callback(struct i2c_slave_module *const module)
{
	//Never happens
}

/**********************************************************************
 * @fn					- i2c_read_complete_callback
 * @brief				- i2c SLAVE read complete triggers this callback
 *							
 *
 * @param[in]			- struct i2c_slave_module
 * @param[in]			- *const module
 * @return				- void
 *
 * @note				- MASTER: i2c_write, SLAVE: read-into-buf Complete
 *						This is also triggered for master-write-addr prior to read
 **********************************************************************/
void i2c_read_complete_callback(struct i2c_slave_module *const module)
{
	LED_Toggle(STATUSLED_ORANGE);
	if (cmd_sent.cmdID != 0)
	{
		//If new data, set flag to process data.
		flgcmdRx = TRUE;			
	}

}

/**********************************************************************
 * @fn					- i2c_read_request_callback
 * @brief				- i2c master read request triggers this callback
 *
 * @param[in]			- struct i2c_slave_module
 * @param[in]			- *const module
 * @return				- void
 *
 * @note				- I2C Read Callback
 **********************************************************************/
void i2c_read_request_callback(	struct i2c_slave_module *const module)
{
	/* Init i2c packet */
	rw_packet.data_length = sizeof(cmd_resp);
	rw_packet.data = (uint8_t *)&cmd_resp;

	/* Write buffer to master */
	i2c_slave_write_packet_job(module, &rw_packet);
	
}

/**********************************************************************
 * @fn					- i2c_write_request_callback
 * @brief				- i2c master write request triggers this callback
 *
 * @param[in]			- struct i2c_slave_module
 * @param[in]			- *const module
 * @return				- void
 *
 * @note				- I2C Write Callback
 **********************************************************************/
void i2c_write_request_callback(struct i2c_slave_module *const module)
{
	/* Init i2c packet */
	rw_packet.data_length = sizeof(cmd_sent);
	rw_packet.data = (uint8_t *)&cmd_sent;


	/* Read buffer from master */
	if (i2c_slave_read_packet_job(module, &rw_packet) != STATUS_OK)
	{
	}

}