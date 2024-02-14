/*
 * TIMERS_program.c
 *
 *  Created on: Dec 19, 2023
 *      Author: bagiz
 */

#include "STD_TYPES.h"
#include "bit_math.h"
#include "ErrType.h"
#include "MAP.h"

#include "TIMERS_interface.h"
#include "TIMERS_config.h"
#include "TIMERS_privare.h"
#include "TIMERS_register.h"


static void(*Timer_pvCallBackFunc[8])(void)={NULL};



uint8 Timer0_voidInit(const Timer0_2_cfg_t *Timer0_cfg)
{
	ErrorState Local_u8ErrorState=OK;

	if(Timer0_cfg != NULL)
	{
		switch (Timer0_cfg->Wf_gen_mode)
		{
		case T0_2_NORMAL:		 CLR_BIT(TCCR0,TCCR0_WGM00);CLR_BIT(TCCR0,TCCR0_WGM01);		                                break;
		case T0_2_CTC:	  		 CLR_BIT(TCCR0,TCCR0_WGM00);SET_BIT(TCCR0,TCCR0_WGM01);		                                break;
		case T0_2_FAST_PWM: 	 SET_BIT(TCCR0,TCCR0_WGM00);SET_BIT(TCCR0,TCCR0_WGM01);		                                break;
		case T0_2_PHASE_CORRECT: SET_BIT(TCCR0,TCCR0_WGM00);CLR_BIT(TCCR0,TCCR0_WGM01);	                                    break;

		default: Local_u8ErrorState=NOT_OK;		break;
		}

		switch(Timer0_cfg->Com_mode)
		{
		case T0_2_DISCONNECTED_NON: CLR_BIT(TCCR0,TCCR0_COM00);CLR_BIT(TCCR0,TCCR0_COM01);			  					    break;
		case T0_2_TOGGLE:			SET_BIT(TCCR0,TCCR0_COM00);CLR_BIT(TCCR0,TCCR0_COM01);			    					break;
		case T0_2_CLEAR: 			CLR_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);			    					break;
		case T0_2_SET:				SET_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);		    						break;

		case T0_2_DISCONNECTED_FAST:	     CLR_BIT(TCCR0,TCCR0_COM00);CLR_BIT(TCCR0,TCCR0_COM01);							break;
		case T0_2_CLEAR_ON_COM_SET_ON_TOP:	 CLR_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);							break;
		case T0_2_SET_ON_COM_CLEAR_ON_TOP:	 SET_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);							break;

		case T0_2_DISCONNECTED_PHASE:				 CLR_BIT(TCCR0,TCCR0_COM00);CLR_BIT(TCCR0,TCCR0_COM01);					break;
		case T0_2_CLEAR_UP_COUNTING_SET_DOWNCOUNTING:CLR_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);					break;
		case T0_2_SET_UP_COUNTING_CLEAR_DOWNCOUNTING:SET_BIT(TCCR0,TCCR0_COM00);SET_BIT(TCCR0,TCCR0_COM01);					break;

		default: Local_u8ErrorState=NOT_OK;		break;

		}

		switch(Timer0_cfg->Clk_prescaler)
		{
		case Clk_Stopped: 			   		TCCR0 &=PRESCALER_ZERO;  TCCR0 |=0b000;	    	break;
		case No_prescaler: 			   		TCCR0 &=PRESCALER_ZERO;  TCCR0 |=0b001;	  	    break;
		case Clk_8:						   	TCCR0 &=PRESCALER_ZERO;  TCCR0 |=0b010;	   	    break;
		case Clk_64: 						TCCR0 &=PRESCALER_ZERO;  TCCR0 |=0b011;	    	break;
		case Clk_256:						TCCR0 &=PRESCALER_ZERO;  TCCR0 |=0b100;     	break;
		case Clk_1024:						TCCR0 &=PRESCALER_ZERO;  TCCR0 |=0b101;     	break;
		case Ext_ClkSource_Falling_edge:	TCCR0 &=PRESCALER_ZERO;  TCCR0 |=0b110;			break;
		case Ext_ClkSource_Rising_edge:		TCCR0 &=PRESCALER_ZERO;  TCCR0 |=0b111;			break;

		default: Local_u8ErrorState=NOT_OK;			break;

		}

	}
	else
	{
		Local_u8ErrorState=NOT_OK;
	}

	return Local_u8ErrorState;

}

void Timer0_voidSetPreloadValue(uint8 Copy_u8PreLoadVal)
{
	TCNT0 = Copy_u8PreLoadVal;
}


void Timer0_voidSetCompareMatchValue(uint8 Copy_u8CompMatVal)
{
	OCR0 = Copy_u8CompMatVal;
}




uint8 Timer1_voidInit(const Timer1_cfg_t *Timer1_cfg)
{
	ErrorState Local_u8ErrorState=OK;

	if(Timer1_cfg != NULL)
	{
		switch (Timer1_cfg->Wf_gen_mode)
		{
		case T1_NORMAL: CLR_BIT(TCCR1A,TCCR1A_WGM10);  CLR_BIT(TCCR1A,TCCR1A_WGM11);  CLR_BIT(TCCR1B,TCCR1B_WGM12);  CLR_BIT(TCCR1B,TCCR1B_WGM13);			        break;

		case PWM_PHASE_CORR_8BIT: 	SET_BIT(TCCR1A,TCCR1A_WGM10);  CLR_BIT(TCCR1A,TCCR1A_WGM11);  CLR_BIT(TCCR1B,TCCR1B_WGM12);  CLR_BIT(TCCR1B,TCCR1B_WGM13);	    break;
		case PWM_PHASE_CORR_9BIT: 		CLR_BIT(TCCR1A,TCCR1A_WGM10);  SET_BIT(TCCR1A,TCCR1A_WGM11);  CLR_BIT(TCCR1B,TCCR1B_WGM12);  CLR_BIT(TCCR1B,TCCR1B_WGM13);	break;
		case PWM_PHASE_CORR_10BIT: 		SET_BIT(TCCR1A,TCCR1A_WGM10);  SET_BIT(TCCR1A,TCCR1A_WGM11);  CLR_BIT(TCCR1B,TCCR1B_WGM12);  CLR_BIT(TCCR1B,TCCR1B_WGM13);  break;

		case T1_CTC1:	CLR_BIT(TCCR1A,TCCR1A_WGM10);  CLR_BIT(TCCR1A,TCCR1A_WGM11);  SET_BIT(TCCR1B,TCCR1B_WGM12);  CLR_BIT(TCCR1B,TCCR1B_WGM13);	     		    break;

		case T1_FAST_PWM_8BIT:	SET_BIT(TCCR1A,TCCR1A_WGM10);  CLR_BIT(TCCR1A,TCCR1A_WGM11);  SET_BIT(TCCR1B,TCCR1B_WGM12);  CLR_BIT(TCCR1B,TCCR1B_WGM13);	     	break;
		case T1_FAST_PWM_9BIT:		CLR_BIT(TCCR1A,TCCR1A_WGM10);  SET_BIT(TCCR1A,TCCR1A_WGM11);  SET_BIT(TCCR1B,TCCR1B_WGM12);  CLR_BIT(TCCR1B,TCCR1B_WGM13);     	break;
		case T1_FAST_PWM_10BIT:	SET_BIT(TCCR1A,TCCR1A_WGM10);  SET_BIT(TCCR1A,TCCR1A_WGM11);  SET_BIT(TCCR1B,TCCR1B_WGM12);  CLR_BIT(TCCR1B,TCCR1B_WGM13);	     	break;

		case PWM_PHASE_FREQ_CORR1:	CLR_BIT(TCCR1A,TCCR1A_WGM10);  CLR_BIT(TCCR1A,TCCR1A_WGM11);  CLR_BIT(TCCR1B,TCCR1B_WGM12);  SET_BIT(TCCR1B,TCCR1B_WGM13);	    break;
		case PWM_PHASE_FREQ_CORR2:	SET_BIT(TCCR1A,TCCR1A_WGM10);  CLR_BIT(TCCR1A,TCCR1A_WGM11);  CLR_BIT(TCCR1B,TCCR1B_WGM12);  SET_BIT(TCCR1B,TCCR1B_WGM13);	    break;
		case PWM_PHASE_CORR1:	CLR_BIT(TCCR1A,TCCR1A_WGM10);  SET_BIT(TCCR1A,TCCR1A_WGM11);  CLR_BIT(TCCR1B,TCCR1B_WGM12);  SET_BIT(TCCR1B,TCCR1B_WGM13);	     	break;
		case PWM_PHASE_CORR2:	CLR_BIT(TCCR1A,TCCR1A_WGM10);  SET_BIT(TCCR1A,TCCR1A_WGM11);  SET_BIT(TCCR1B,TCCR1B_WGM12);  SET_BIT(TCCR1B,TCCR1B_WGM13);	     	break;

		case T1_CTC2:	CLR_BIT(TCCR1A,TCCR1A_WGM10);  CLR_BIT(TCCR1A,TCCR1A_WGM11);  SET_BIT(TCCR1B,TCCR1B_WGM12);  SET_BIT(TCCR1B,TCCR1B_WGM13);	     			break;
		case T1_FAST_PWM1:	CLR_BIT(TCCR1A,TCCR1A_WGM10);  SET_BIT(TCCR1A,TCCR1A_WGM11);  SET_BIT(TCCR1B,TCCR1B_WGM12);  SET_BIT(TCCR1B,TCCR1B_WGM13);	        	break;
		case T1_FAST_PWM2:	SET_BIT(TCCR1A,TCCR1A_WGM10);  SET_BIT(TCCR1A,TCCR1A_WGM11);  SET_BIT(TCCR1B,TCCR1B_WGM12);  SET_BIT(TCCR1B,TCCR1B_WGM13);	     	    break;

		default: Local_u8ErrorState=NOT_OK;		break;

		}

		switch(Timer1_cfg->Com_mode)
		{
		case T1_DISCONNECTED_NON: 	CLR_BIT(TCCR1A,TCCR1A_COM1A0);  	CLR_BIT(TCCR1A,TCCR1A_COM1A1);	    					break;
		case T1_TOGGLE:				SET_BIT(TCCR1A,TCCR1A_COM1A0);  	CLR_BIT(TCCR1A,TCCR1A_COM1A1);		 				    break;
		case T1_CLEAR: 				CLR_BIT(TCCR1A,TCCR1A_COM1A0);  	SET_BIT(TCCR1A,TCCR1A_COM1A1);		   			   	    break;
		case T1_SET:				SET_BIT(TCCR1A,TCCR1A_COM1A0);  	SET_BIT(TCCR1A,TCCR1A_COM1A1);		     				break;

		case T1_DISCONNECTED_FAST:			CLR_BIT(TCCR1A,TCCR1A_COM1A0);  	CLR_BIT(TCCR1A,TCCR1A_COM1A1);					break;
		case T1_CLEAR_ON_COM_SET_ON_TOP:	CLR_BIT(TCCR1A,TCCR1A_COM1A0);  	SET_BIT(TCCR1A,TCCR1A_COM1A1);		 			break;
		case T1_SET_ON_COM_CLEAR_ON_TOP:	SET_BIT(TCCR1A,TCCR1A_COM1A0);  	SET_BIT(TCCR1A,TCCR1A_COM1A1);				    break;

		case T1_DISCONNECTED_PHASE:						CLR_BIT(TCCR1A,TCCR1A_COM1A0);  	CLR_BIT(TCCR1A,TCCR1A_COM1A1);		break;
		case T1_CLEAR_UP_COUNTING_SET_DOWNCOUNTING:		CLR_BIT(TCCR1A,TCCR1A_COM1A0);  	SET_BIT(TCCR1A,TCCR1A_COM1A1);		break;
		case T1_SET_UP_COUNTING_CLEAR_DOWNCOUNTING:		SET_BIT(TCCR1A,TCCR1A_COM1A0);  	SET_BIT(TCCR1A,TCCR1A_COM1A1);		break;


		default: Local_u8ErrorState=NOT_OK;		break;

		}

		switch(Timer1_cfg->Clk_prescaler)
		{
		case Clk_Stopped: 				   		TCCR1B &=PRESCALER_ZERO;  TCCR1B |=0b000;			    break;
		case No_prescaler: 				     	TCCR1B &=PRESCALER_ZERO;  TCCR1B |=0b001;			    break;
		case Clk_8:						  	   	TCCR1B &=PRESCALER_ZERO;  TCCR1B |=0b010;			    break;
		case Clk_64: 					  		TCCR1B &=PRESCALER_ZERO;  TCCR1B |=0b011;		  	    break;
		case Clk_256:					  		TCCR1B &=PRESCALER_ZERO;  TCCR1B |=0b100;      	     	break;
		case Clk_1024:					  		TCCR1B &=PRESCALER_ZERO;  TCCR1B |=0b101;      	    	break;
		case Ext_ClkSource_Falling_edge:  		TCCR1B &=PRESCALER_ZERO;  TCCR1B |=0b110;				break;
		case Ext_ClkSource_Rising_edge:   		TCCR1B &=PRESCALER_ZERO;  TCCR1B |=0b111;				break;

		default: Local_u8ErrorState=NOT_OK;			break;

		}

	}
	else
	{
		Local_u8ErrorState=NULL_PTR_ERR;
	}
	return Local_u8ErrorState;
}



void Timer1_voidSetTopValue(uint16 Copy_u16Value)
{
	ICR1= Copy_u16Value;
}

uint16 Timer1_u16Get_ICR1_Read(void)
{
	return ICR1 ;
}

void Timer1_voidSetCompValue(uint16 Copy_u16Value)
{
	OCR1A=Copy_u16Value;
}


uint8 Timer2_voidInit(const Timer0_2_cfg_t *Timer2_cfg)
{
	ErrorState Local_u8ErrorState=OK;

	if(Timer2_cfg != NULL )
	{
		switch (Timer2_cfg->Wf_gen_mode)
		{
		case T0_2_NORMAL: 		   CLR_BIT(TCCR2,TCCR2_WGM20);	CLR_BIT(TCCR2,TCCR2_WGM21);					 	        break;
		case T0_2_CTC:			   CLR_BIT(TCCR2,TCCR2_WGM20);	SET_BIT(TCCR2,TCCR2_WGM21);					            break;
		case T0_2_FAST_PWM:	       SET_BIT(TCCR2,TCCR2_WGM20);	CLR_BIT(TCCR2,TCCR2_WGM21);					            break;
		case T0_2_PHASE_CORRECT:   SET_BIT(TCCR2,TCCR2_WGM20);	SET_BIT(TCCR2,TCCR2_WGM21);			       	 	        break;

		default: Local_u8ErrorState=NOT_OK;		 break;
		}

		switch(Timer2_cfg->Com_mode)
		{
		case T0_2_DISCONNECTED_NON: CLR_BIT(TCCR2,TCCR2_COM20);	CLR_BIT(TCCR2,TCCR2_COM21);			  			        break;
		case T0_2_TOGGLE:			SET_BIT(TCCR2,TCCR2_COM20);	CLR_BIT(TCCR2,TCCR2_COM21);			                    break;
		case T0_2_CLEAR: 			CLR_BIT(TCCR2,TCCR2_COM20);	SET_BIT(TCCR2,TCCR2_COM21);			                    break;
		case T0_2_SET:				SET_BIT(TCCR2,TCCR2_COM20);	SET_BIT(TCCR2,TCCR2_COM21);		                        break;

		case T0_2_DISCONNECTED_FAST:			CLR_BIT(TCCR2,TCCR2_COM20);	CLR_BIT(TCCR2,TCCR2_COM21);		            break;
		case T0_2_CLEAR_ON_COM_SET_ON_TOP:		CLR_BIT(TCCR2,TCCR2_COM20);	SET_BIT(TCCR2,TCCR2_COM21);		            break;
		case T0_2_SET_ON_COM_CLEAR_ON_TOP:		SET_BIT(TCCR2,TCCR2_COM20);	SET_BIT(TCCR2,TCCR2_COM21);		            break;

		case T0_2_DISCONNECTED_PHASE:						CLR_BIT(TCCR2,TCCR2_COM20);	CLR_BIT(TCCR2,TCCR2_COM21);		break;
		case T0_2_CLEAR_UP_COUNTING_SET_DOWNCOUNTING:		CLR_BIT(TCCR2,TCCR2_COM20);	SET_BIT(TCCR2,TCCR2_COM21);		break;
		case T0_2_SET_UP_COUNTING_CLEAR_DOWNCOUNTING:		SET_BIT(TCCR2,TCCR2_COM20);	SET_BIT(TCCR2,TCCR2_COM21);		break;


		}

		switch(Timer2_cfg->Clk_prescaler)
		{
		case Clk_Stopped: 			   		TCCR2 &=PRESCALER_ZERO;  TCCR2 |=0b000;		    break;
		case No_prescaler: 			   		TCCR2 &=PRESCALER_ZERO;  TCCR2 |=0b001;		    break;
		case Clk_8:						   	TCCR2 &=PRESCALER_ZERO;  TCCR2 |=0b010;		    break;
		case Clk_32:						TCCR2 &=PRESCALER_ZERO;  TCCR2 |=0b011;		    break;
		case Clk_64: 						TCCR2 &=PRESCALER_ZERO;  TCCR2 |=0b100;		    break;
		case Clk_128: 						TCCR2 &=PRESCALER_ZERO;  TCCR2 |=0b101;		    break;
		case Clk_256:						TCCR2 &=PRESCALER_ZERO;  TCCR2 |=0b110;        	break;
		case Clk_1024:						TCCR2 &=PRESCALER_ZERO;  TCCR2 |=0b111;        	break;

		default: Local_u8ErrorState=NOT_OK;			break;

		}
	}
	else
	{
		Local_u8ErrorState=NULL_PTR_ERR;
	}



	return Local_u8ErrorState;

}




uint8 Timers_u8IntEnable(Timers timer_index , TIMERS_Interrupt_t Copy_u8IntSource)
{

	ErrorState Local_u8ErrorState=OK;
	if(timer_index==TIMER0)
	{
		switch(Copy_u8IntSource)
		{
		case T0_COM_INT : 	SET_BIT(TIMSK,TIMSK_OCIE0);		            break;
		case T0_OVF_INT : 	SET_BIT(TIMSK,TIMSK_TOIE0);		            break;
		default : Local_u8ErrorState=NOT_OK;	 						break;

		}
	}
	else if (timer_index==TIMER1)
	{
		switch(Copy_u8IntSource)
		{
		case T1_InpCap_Int : 	SET_BIT(TIMSK,TIMSK_TICIE1);        	break;
		case T1_ComA_Int : 		SET_BIT(TIMSK,TIMSK_OCIE1A);        	break;
		case T1_ComB_Int : 		SET_BIT(TIMSK,TIMSK_OCIE1B);        	break;
		case T1_Ovf_Int : 		SET_BIT(TIMSK,TIMSK_TOIE1);	        	break;

		default : Local_u8ErrorState=NOT_OK;	 						break;

		}
	}
	else if (timer_index==TIMER2)
	{
		switch(Copy_u8IntSource)
		{
		case T2_COM_INT : 		SET_BIT(TIMSK,TIMSK_OCIE2);				break;
		case T2_OVF_INT : 		SET_BIT(TIMSK,TIMSK_TOIE2);				break;
		default : Local_u8ErrorState=NOT_OK;						    break;

		}
	}
	else
	{
		Local_u8ErrorState=NOT_OK;
	}

	return Local_u8ErrorState;


}
uint8 Timers_u8IntDisable(Timers timer_index , TIMERS_Interrupt_t Copy_u8IntSource)
{
	ErrorState Local_u8ErrorState=OK;
	if(timer_index==TIMER0)
	{
		switch(Copy_u8IntSource)
		{
		case T0_COM_INT : 	CLR_BIT(TIMSK,TIMSK_OCIE0);				    	break;
		case T0_OVF_INT : 	CLR_BIT(TIMSK,TIMSK_TOIE0);						break;

		default : Local_u8ErrorState=NOT_OK;							    break;

		}
	}
	else if (timer_index==TIMER1)
	{
		switch(Copy_u8IntSource)
		{
		case T1_InpCap_Int : 	CLR_BIT(TIMSK,TIMSK_TICIE1);				break;
		case T1_ComA_Int : 		CLR_BIT(TIMSK,TIMSK_OCIE1A);				break;
		case T1_ComB_Int : 		CLR_BIT(TIMSK,TIMSK_OCIE1B);				break;
		case T1_Ovf_Int : 		CLR_BIT(TIMSK,TIMSK_TOIE1);					break;

		default : Local_u8ErrorState=NOT_OK;							    break;

		}
	}
	else if (timer_index==TIMER2)
	{
		switch(Copy_u8IntSource)
		{
		case T2_COM_INT : 	CLR_BIT(TIMSK,TIMSK_OCIE2);						break;
		case T2_OVF_INT : 	CLR_BIT(TIMSK,TIMSK_TOIE2);						break;
		default : Local_u8ErrorState=NOT_OK;	 							break;

		}
	}
	else
	{
		Local_u8ErrorState=NOT_OK;
	}

	return Local_u8ErrorState;



}


uint16 Timer0_u16GetCounterRead(void)
{
	return TCNT0;
}

uint16 Timer1_u16GetCounterRead(void)
{
	return OCR1A;
}



void SERVO_voidTIMER1_M14Init(void)
{
	/*1-Select Mode 14 in Timer 1 */
	CLR_BIT(TCCR1A , 0);
	SET_BIT(TCCR1A , 1);
	SET_BIT(TCCR1B , 3);
	SET_BIT(TCCR1B , 4);

	/*2-Select OC1A Action */
	CLR_BIT(TCCR1A , 6);
	SET_BIT(TCCR1A , 7);


	/*Select Prescaler ==> 8*/
	CLR_BIT(TCCR1B,0);
	SET_BIT(TCCR1B,1);
	CLR_BIT(TCCR1B,2);

	/*4-Set ICR1 Value ==> 40000*/
	ICR1 = 40000 ;

}
void SERVO_voidSetAngle(uint16 Copy_u16Angle)
{

	OCR1A = MAP(0,180,1200,5200,Copy_u16Angle);
}

uint16 TIMER1_u16GetTimerRead(void)
{
	return TCNT1 ;
}

void Timer1_voidSetValue(uint16 Copy_u16Value)
{
	TCNT1=Copy_u16Value;
}




uint8 Timer_u8SetCallBack(TIMERS_Interrupt_t Copy_u8IntSource ,void(*Copy_pvCallBackFunc)(void))
{

	ErrorState Local_u8ErrorState;
	if(Copy_pvCallBackFunc!=NULL)
	{
		Timer_pvCallBackFunc[Copy_u8IntSource]=Copy_pvCallBackFunc;
	}
	else
	{
		Local_u8ErrorState=NULL_PTR_ERR;
	}
	return Local_u8ErrorState;

}



/*Timer0_OV_ISR*/

__attribute__((signal)) void __vector_11 (void);
void __vector_11 (void)
{
	if(Timer_pvCallBackFunc[T0_OVF_INT]!=NULL)
	{
		Timer_pvCallBackFunc[T0_OVF_INT]();
	}
	else
	{

	}
}

/*TIMER0_  CTC   ISR*/
__attribute__((signal)) void __vector_10(void);
void __vector_10 (void)
{
	if(Timer_pvCallBackFunc[T0_COM_INT]!=NULL)
	{
		Timer_pvCallBackFunc[T0_COM_INT]();
	}
	else
	{

	}
}

/*Timer1_OV_ISR*/

__attribute__((signal)) void __vector_9 (void);
void __vector_9 (void)
{
	if(Timer_pvCallBackFunc[T1_Ovf_Int]!=NULL)
	{
		Timer_pvCallBackFunc[T1_Ovf_Int]();
	}
	else
	{

	}
}

/*TIMER1_  COMPA   ISR*/
__attribute__((signal)) void __vector_7(void);
void __vector_7 (void)
{
	if(Timer_pvCallBackFunc[T1_ComA_Int]!=NULL)
	{
		Timer_pvCallBackFunc[T1_ComA_Int]();
	}
	else
	{

	}
}

/*TIMER1_  COMPB   ISR*/
__attribute__((signal)) void __vector_8(void);
void __vector_8 (void)
{
	if(Timer_pvCallBackFunc[T1_ComB_Int]!=NULL)
	{
		Timer_pvCallBackFunc[T1_ComB_Int]();
	}
	else
	{

	}
}

/*TIMER1 CAPT   ISR*/
__attribute__((signal)) void __vector_6(void);
void __vector_6 (void)
{
	if(Timer_pvCallBackFunc[T1_InpCap_Int]!=NULL)
	{
		Timer_pvCallBackFunc[T1_InpCap_Int]();
	}
	else
	{

	}
}



/*Timer2_OV_ISR*/

__attribute__((signal)) void __vector_5 (void);
void __vector_5 (void)
{
	if(Timer_pvCallBackFunc[T0_OVF_INT]!=NULL)
	{
		Timer_pvCallBackFunc[T0_OVF_INT]();
	}
	else
	{

	}
}

/*TIMER2_  CTC   ISR*/
__attribute__((signal)) void __vector_4(void);
void __vector_4 (void)
{
	if(Timer_pvCallBackFunc[T0_COM_INT]!=NULL)
	{
		Timer_pvCallBackFunc[T0_COM_INT]();
	}
	else
	{

	}
}

