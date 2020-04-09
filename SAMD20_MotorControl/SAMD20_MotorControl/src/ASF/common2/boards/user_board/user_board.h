/**
 * \file
 *
 * \brief User board definition template
 *
 */

 /* This file is intended to contain definitions and configuration details for
 * features and devices that are available on the board, e.g., frequency and
 * startup time for an external crystal, external memory devices, LED and USART
 * pins.
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef USER_BOARD_H
#define USER_BOARD_H

#include <conf_board.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \ingroup group_common_boards
 * \defgroup user_board_group User board
 *
 * @{
 */

void system_board_init(void);

	/** Name string macro */
	#define BOARD_NAME				"USER_BOARD"

	#define	DEBUG_WITH_UART				"YES UART"

	/** @} */

	/** \name Resonator definitions *  @{ */
	#define BOARD_FREQ_SLCK_XTAL      (32768U)
	#define BOARD_FREQ_SLCK_BYPASS    (32768U)
	#define BOARD_FREQ_MAINCK_XTAL    0 /* Not Mounted */
	#define BOARD_FREQ_MAINCK_BYPASS  0 /* Not Mounted */
	#define BOARD_MCK                 CHIP_FREQ_CPU_MAX
	#define BOARD_OSC_STARTUP_US      15625
		/** @} */

	/** \name LED0 definitions  *  @{ */
	#define LED0_PIN                  PIN_PA14
	#define LED0_ACTIVE               false
	#define LED0_INACTIVE             !LED0_ACTIVE
	/** @} */

	/** \name SW0 definitions  *  @{ */
	#define SW0_PIN                   PIN_PA15
	#define SW0_ACTIVE                false
	#define SW0_INACTIVE              !SW0_ACTIVE
	#define SW0_EIC_PIN               PIN_PA15A_EIC_EXTINT15
	#define SW0_EIC_MUX               MUX_PA15A_EIC_EXTINT15
	#define SW0_EIC_PINMUX            PINMUX_PA15A_EIC_EXTINT15
	#define SW0_EIC_LINE              15
	/** @} */

	/**
	 * \name Button #0 definitions
	 *
	 * Wrapper macros for SW0, to ensure common naming across all Xplained Pro
	 * boards.
	 *
	 *  @{ */
	#define BUTTON_0_NAME             "SW0"
	#define BUTTON_0_PIN              SW0_PIN
	#define BUTTON_0_ACTIVE           SW0_ACTIVE
	#define BUTTON_0_INACTIVE         SW0_INACTIVE
	#define BUTTON_0_EIC_PIN          SW0_EIC_PIN
	#define BUTTON_0_EIC_MUX          SW0_EIC_MUX
	#define BUTTON_0_EIC_PINMUX       SW0_EIC_PINMUX
	#define BUTTON_0_EIC_LINE         SW0_EIC_LINE
	/** @} */

	/* Motor Defines - Test */
	#define DIR_PIN						PIN_PB00
	#define	PLS_PIN						PIN_PB01

	#define	CHA_ENC						PIN_PB02
	#define	CHB_ENC						PIN_PB03

	//#define PBTN						PIN_PA18
	//#define STATUSLED					PIN_PA19
	#define STATUSLED_GREEN				PIN_PA19
	#define STATUSLED_ORANGE			PIN_PA18
	#define LIMIT_SW_PIN				PIN_PB09
	
	//I2C STRAP PINS
	#define I2C_STRAP_0					PIN_PA27	//Pin 51
	#define I2C_STRAP_1					PIN_PB23	//Pin 50



/***************************************************************************
 * \brief Turns off the specified LEDs.
 * \param led_gpio LED to turn off (LEDx_GPIO).
 * \note The pins of the specified LEDs are set to GPIO output mode.
 ***************************************************************************/
#define LED_Off(led_gpio)     port_pin_set_output_level(led_gpio,true)

/***************************************************************************
 * \brief Turns on the specified LEDs.
 * \param led_gpio LED to turn on (LEDx_GPIO).
 * \note The pins of the specified LEDs are set to GPIO output mode.
 ***************************************************************************/
#define LED_On(led_gpio)      port_pin_set_output_level(led_gpio,false)

/***************************************************************************
 * \brief Toggles the specified LEDs.
 * \param led_gpio LED to toggle (LEDx_GPIO).
 * \note The pins of the specified LEDs are set to GPIO output mode.
 ***************************************************************************/
#define LED_Toggle(led_gpio)  port_pin_toggle_output_level(led_gpio)


#ifdef __cplusplus
}
#endif

#endif // USER_BOARD_H
