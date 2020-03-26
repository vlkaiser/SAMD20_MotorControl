/*
 * DC_TypeDefs.h
 *
 * Created: 3/25/2020 1:08:19 PM
 *  Author: VKaiser
 */ 


#ifndef DC_TYPEDEFS_H_
#define DC_TYPEDEFS_H_


#define __vo		volatile

#define UINT8   	unsigned char
#define UINT16   	unsigned short
#define UINT32   	unsigned long

#define INT8   		signed char
#define INT16   	signed short
#define INT32   	signed long

#define	BOOL		UINT8

#define	TRUE		1
#define FALSE		0

#define	SET			ENABLE
#define RESET		DISABLE

/***** Command ID Abstractions *****/

// Commands Sent: cmdID
#define PWR_UP		0x55		//Power Up: Find HOME
#define PWR_DWN		0x66		//Power Down: GoTo HOME
#define ESTP		0x86		//STOP As is (No Motion)
#define CURSTAT		0x99		//Report Status (No Motion)
/* TODO: MEAS_ST will initiate a sequence, probably loaded by the SMARC */
#define MEAS_ST		0xA0		//Start Meas Sequence

// Commands Sent: encLocMoveTo //
#define posHome		0xACCE55ED
#define posEnd		0x0B501E7E
#define posStart	0xFEEDFEED
#define posSTOP		0xDECEA5ED

/********** Command Response **********/
//cmd Status
#define dWAIT		0xBE
#define dRDY		0x60
#define dERR		0xD0

//cmd encoderloc
#define endPwrUp	0x1D1D1700
#define endPwrDown	0x11223344
#define endMeas		0x88AA88EE
#define endESTOP	0xDEADDEAD



#endif /* DC_TYPEDEFS_H_ */