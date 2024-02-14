/*
 * UltraSonic_prog.c
 *
 *  Created on: Feb 14, 2024
 *      Author: bagiz
 */

#include "STD_TYPES.h"
#include "bit_math.h"
#include "DIO_interface.h"
#include "TIMERS_register.h"
#include "TIMERS_interface.h"
#include <util/delay.h>

uint8 UltraSonicDistance(port_index Port , pin_index Pin)
{


	uint16 Reading1;
	uint16 Reading2;
	uint16 period;
	uint8  distance;

	Timer1_cfg_t timer11={
			.Wf_gen_mode=T1_NORMAL,
			.Com_mode=T1_DISCONNECTED_NON,
			.Clk_prescaler=No_prescaler
	};

	Timer1_voidInit(&timer11);

	//TCCR1A=0;// i am working in normal mode with | i am not generating signal i am capturing

	SET_BIT(TIFR,ICF1);//clear flag --> don't remove

	/*trigger pulse*/

	DIO_u8SetPinValue(Port,Pin,DIO_u8PIN_HIGH);
	_delay_us(20);
	DIO_u8SetPinValue(Port,Pin,DIO_u8PIN_LOW);

	/*first rising edge*/

	SET_BIT(TCCR1B,6);//trigger on rising edge -----> input capture unit edge select

	while(GET_BIT(TIFR,ICF1)==0);//pooling on flag until it's got triggerd

	Reading1=ICR1;//load value from start to first rising edge
	SET_BIT(TIFR,ICF1);//clear flag by writing one on it

	/*first falling edge*/
	CLR_BIT(TCCR1B,6);//trigger on falling edge
	while(GET_BIT(TIFR,ICF1)==0);//pooling on flag until it's got triggerd

	Reading2=ICR1;//load value from start to first falling
	SET_BIT(TIFR,ICF1);//clear flag by writing one on it

	TCNT1=0;			/*too important to reset counter */
	TCCR1B = 0;  		/* Stop the timer */

	period  = (Reading2-Reading1);
	distance=(uint8)((period*34600)/(16000000*2));//we divided over 2 because the period is that taken to go and return

	return distance;

}
