/*
 * Ascii2Hexc.h
 * Convert Arbitrary to Hex
 * Created: 4/1/2020 3:12:30 PM
 *  Author: VKaiser
 */ 

#include "Ascii2Hex.h"

 /*****************************************************************
   *  ascii character to hex nibble (case insensitive)             *
   *****************************************************************/
 
 unsigned char AtoH (unsigned char data)
 { 
	 if (data > '9') 
		{ 
			data += 9;
		}
	return (data &= 0x0F);
 }
 