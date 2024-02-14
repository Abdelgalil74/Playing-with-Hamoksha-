/*
 * main.c
 *
 *  Created on: Feb 14, 2024
 *      Author: bagiz
 */

#include "STD_TYPES.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "UltraSonic_interface.h"
#include "CLCD_interface.h"
#include <util/delay.h>




uint8 Hamoksha1[] = {
		0b01110,
		0b01110,
		0b01110,
		0b00100,
		0b01100,
		0b00110,
		0b01100,
		0b10010
};
uint8 Hamoksha2[] = {
		0b01110,
		0b01110,
		0b01110,
		0b00100,
		0b00110,
		0b01100,
		0b00110,
		0b01001
};

/* Pattern for Run Character*/
uint8 Local_u8Pattern2[8]={
		0b01110,
		0b01110,
		0b00100,
		0b01110,
		0b10101,
		0b01000,
		0b10000,
		0b00000
};
/* Pattern for Run2 Character*/
uint8 Local_u8Pattern3[8]={
		0b01110,
		0b01110,
		0b00100,
		0b01110,
		0b10101,
		0b00010,
		0b00001,
		0b00000
};

void main(void)
{
	PORT_voidInit();
	CLCD_voidInit();


	uint8 Distance=0;
	while(1)
	{

		Distance=UltraSonicDistance(DIO_u8PORTC,DIO_u8PIN0);
/*		CLCD_voidSendStringPos(2,1,"Distance = ");
		CLCD_voidDisplayNumberPos(2,12,Distance);
		CLCD_voidSendStringPos(2,13," Cm ");
*/

		if(Distance>=4)
		{
			CLCD_u8SendSpecialCharacter(1,Local_u8Pattern2,1,Distance-4);
			_delay_ms(150);
			CLCD_voidSendDataPos(1,Distance-3,' ');
			CLCD_u8SendSpecialCharacter(2,Local_u8Pattern3,1,Distance-4);
			_delay_ms(150);
			CLCD_voidSendDataPos(1,Distance-4,' ');

		}



	}
}


