/*
 * TIMERS_interface.h
 *
 *  Created on: Dec 19, 2023
 *      Author: bagiz
 */

#ifndef TIMERS_INTERFACE_H_
#define TIMERS_INTERFACE_H_


typedef enum{

	T0_2_NORMAL,
	T0_2_CTC,
	T0_2_FAST_PWM,
	T0_2_PHASE_CORRECT,

}Timer0_2_WfGenMode;
typedef enum{

	T0_2_DISCONNECTED_NON,
	T0_2_TOGGLE,
	T0_2_CLEAR,
	T0_2_SET,

	T0_2_DISCONNECTED_FAST,
	T0_2_CLEAR_ON_COM_SET_ON_TOP,
	T0_2_SET_ON_COM_CLEAR_ON_TOP,

	T0_2_DISCONNECTED_PHASE,
	T0_2_CLEAR_UP_COUNTING_SET_DOWNCOUNTING,
	T0_2_SET_UP_COUNTING_CLEAR_DOWNCOUNTING

}Timer0_2_COM_Mode;

typedef enum{
	Clk_Stopped,
	No_prescaler,
	Clk_8,
	Clk_32,
	Clk_64,
	Clk_128,
	Clk_256,
	Clk_1024,
	Ext_ClkSource_Falling_edge,
	Ext_ClkSource_Rising_edge


}Clock_Select_t;

typedef struct{

	Timer0_2_WfGenMode  Wf_gen_mode ;
	Timer0_2_COM_Mode   Com_mode ;
	Clock_Select_t      Clk_prescaler;

}Timer0_2_cfg_t;

typedef enum{
	T0_COM_INT,
	T0_OVF_INT,

	T1_InpCap_Int,
	T1_ComA_Int,
	T1_ComB_Int,
	T1_Ovf_Int,

	T2_COM_INT,
	T2_OVF_INT,

}TIMERS_Interrupt_t;

typedef enum{

	T1_NORMAL,
	PWM_PHASE_CORR_8BIT,
	PWM_PHASE_CORR_9BIT,
	PWM_PHASE_CORR_10BIT,
	T1_CTC1,
	T1_FAST_PWM_8BIT,
	T1_FAST_PWM_9BIT,
	T1_FAST_PWM_10BIT,
	PWM_PHASE_FREQ_CORR1,
	PWM_PHASE_FREQ_CORR2,
	PWM_PHASE_CORR1,
	PWM_PHASE_CORR2,
	T1_CTC2,
	T1_FAST_PWM1,
	T1_FAST_PWM2,
}Timer1_WfGenMode_t;

typedef enum {
	T1_DISCONNECTED_NON,
	T1_TOGGLE,
	T1_CLEAR,
	T1_SET,

	T1_DISCONNECTED_FAST,
	T1_CLEAR_ON_COM_SET_ON_TOP,
	T1_SET_ON_COM_CLEAR_ON_TOP,

	T1_DISCONNECTED_PHASE,
	T1_CLEAR_UP_COUNTING_SET_DOWNCOUNTING,
	T1_SET_UP_COUNTING_CLEAR_DOWNCOUNTING

}Timer1_COM_Mode_t;

typedef struct{

	Timer1_WfGenMode_t  Wf_gen_mode ;
	Timer1_COM_Mode_t   Com_mode ;
	Clock_Select_t      Clk_prescaler;

}Timer1_cfg_t;

typedef enum
{
	TIMER0,
	TIMER1,
	TIMER2

}Timers;


uint8 Timer0_voidInit(const Timer0_2_cfg_t *Timer0_cfg);
uint8 Timer1_voidInit(const Timer1_cfg_t *Timer1_cfg);
uint8 Timer2_voidInit(const Timer0_2_cfg_t *Timer2_cfg);

void Timer0_voidSetPreloadValue(uint8 Copy_u8PreLoadVal);
void Timer0_voidSetCompareMatchValue(uint8 Copy_u8CompMatVal);


void Timer1_voidSetValue(uint16 Copy_u16Value);
uint16 TIMER1_u16GetTimerRead(void);

void Timer1_voidSetTopValue(uint16 Copy_u16Value);
void Timer1_voidSetCompValue(uint16 Copy_u16Value);

uint8 Timer0_2_u8SetComp(Timer0_2_COM_Mode Mode);
uint8 Timer1_u8SetComp(Timer1_COM_Mode_t Mode);


uint8 Timer_u8SetCallBack(TIMERS_Interrupt_t Copy_u8IntSource ,void(*Copy_pvCallBackFunc)(void));

uint8 Timers_u8IntEnable(Timers timer_index , TIMERS_Interrupt_t Copy_u8IntSource);
uint8 Timers_u8IntDisable(Timers timer_index , TIMERS_Interrupt_t Copy_u8IntSource);

/*
void Timer0_voidInit(void);
void TIMER1_voidInit(void);
*/
uint16 Timer0_u16GetCounterRead(void);
uint16 Timer1_u16Get_ICR1_Read(void);

void SERVO_voidTIMER1_M14Init(void);
void SERVO_voidSetAngle(uint16 Copy_u8Angle);



#endif /* TIMERS_INTERFACE_H_ */
