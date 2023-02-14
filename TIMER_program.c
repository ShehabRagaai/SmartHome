/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:MCAL                          ********************/
/*****************       SWC:TIMERS                          ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"TIMER_interface.h"
#include"TIMER_config.h"
#include"TIMER_register.h"
#include"TIMER_private.h"
static void(*Copy_PvCallBackRecive)(void)=NULL;
static void(*Copy_PvCallBackICURecive)(void)=NULL;
u8 Global_Flag=0;
u16 Global_ValueOFCompareMatch;
u8 Global_NumberOfExcuation;



u16 Map_s32GetMapValue(u16 copy_s32InputMin,u16 copy_s32InputMax,u16 copy_s32outputMin,u16 copy_s32OutputMax,u16 copy_s32InputValue)
{
	u16 MAP_s32Slope=(copy_s32InputMin-copy_s32InputMax)/(copy_s32outputMin-copy_s32OutputMax);
	u16 MAP_s32OutputValue=MAP_s32Slope*(copy_s32InputValue-copy_s32InputMin)+copy_s32outputMin;
	return MAP_s32OutputValue;
}

/*Timer0*/
void TIMER0_VoidIntl(void)
{
	/* CTC Mode*/
	CLEAR_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	SET_BIT(TIMSIK,TIMSIK_OCIE0);

	/*Set on Top,Clear on compare match
	CLEAR_BIT(TCCR0,TCCR0_COM0);
	SET_BIT(TCCR0,TCCR0_COM1 );*/

	/*Prescaller:divided by 8*/
	CLEAR_BIT(TCCR0,TCCR0_CS00);
	SET_BIT(TCCR0,TCCR0_CS01);
	CLEAR_BIT(TCCR0,TCCR0_CS02);



}
void TIMER0_SetCompareMatchValue(u8 Copy_u8Value)
{
	OCR0= Copy_u8Value;
}
u8 TIMER0_u8SetCallBack(void(*Copy_PvCallBackFunc)(void))
{
	u8 Local_u8ErrorState=0;

	if(Copy_PvCallBackFunc==NULL)
	{
		Local_u8ErrorState=1;
	}

	else
	{

		Copy_PvCallBackRecive=Copy_PvCallBackFunc;
	}

	return Local_u8ErrorState;

}

/*Timer1*/
u8 ICU_u8SetCallBack(void(*Copy_PvCallBackFunc)(void))
{
	u8 Local_u8ErrorState=0;

	if(Copy_PvCallBackFunc==NULL)
	{
		Local_u8ErrorState=1;
	}

	else
	{

		Copy_PvCallBackICURecive=Copy_PvCallBackFunc;
	}

	return Local_u8ErrorState;
}

/*PWM TIMER1 ChannelA*/
void TIMER1_VoidIntl(void)
{
	/*Fast PWM Mode ChannelA*/
	CLEAR_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	/*Fast PWM Mode ChannelB*/
	CLEAR_BIT(TCCR1A,TCCR1A_COM1B0);
	SET_BIT(TCCR1A,TCCR1A_COM1B1);


	/*WaveForm Generation Mode*/
	CLEAR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	CLEAR_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);
	/*Set Timer Clock:Divition By 8*/
	CLEAR_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLEAR_BIT(TCCR1B,TCCR1B_CS12);
	/*
	Rising Edge trigger
	SET_BIT(TCCR1B,TCCR1B_ICES1);
	/*ICU Interrupt Enable
	SET_BIT(TIMSIK,TIMSIK_TICIE1);*/
}

void TIMER1_ICUSetTriggerEdge(u16 Copy_u8Value)
{
	if(Copy_u8Value==RISING_EDGE)
	{
		SET_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else if(Copy_u8Value==FILLING_EDGE)
	{
		CLEAR_BIT(TCCR1B,TCCR1B_ICES1);
	}
}


void TIMER1_ICUInterruptEnableAndDisable(u16 Copy_u8Value)
{
	if(Copy_u8Value==Enable)
	{
		SET_BIT(TIMSIK,TIMSIK_TICIE1);
	}
	else if(Copy_u8Value==Disable)
	{
		CLEAR_BIT(TIMSIK,TIMSIK_TICIE1);
	}
}

u16 TIMER1_ICUReadValue(void)
{
	return ICR1;
}

/*Set The Compare Match Value Of Timer1 ChannelA That Control On Time Of PWM*/
void TIMER1_SetCompareMatchChannelAValue(u16 Copy_u8Value)
{
	OCR1A= Copy_u8Value;

}
/*Set The Compare Match Value Of Timer1 ChannelB That Control On Time Of PWM*/
void TIMER1_SetCompareMatchChannelBValue(u16 Copy_u8Value)
{
	OCR1B= Copy_u8Value;

}

/*Set The Top Value Of Timer to be used In PWM*/
void TIMER1_SetICR1Value(u16 Copy_u8Value)
{
	ICR1=Copy_u8Value;
}

void TIMER1_SetTimerValue(u16 Copy_u8Value)
{
	TCNT1=Copy_u8Value;
}

u16 TIMER1_GetTimerReading(void)
{
	return TCNT1 ;
}

/*Watch Dog*/

void WDT_voidSleep(u8 Copy_SleepTimeValue)
{
	WDTCR&=0b11111000;
	WDTCR|=Copy_SleepTimeValue;
}

void WDT_voidEnable(void)
{
	SET_BIT(WDTCR,WDTCR_WDE);
}
void WDT_voidDisable(void)
{
	WDTCR|=0b00011000;
	WDTCR=0;

}

void TIMER_voidschedual(u16 Copy_DelayTime,void(*Func)(void),u16 Copy_NumberOfExcuation)
{
	Global_Flag=1;
	u8 Local_prescaller=8;
	u8 Local_TimerClock=Local_prescaller/8000000;

	u16 Local_Resolution=256;

	u16 Local_NumberOFOVTickis=Local_TimerClock*Local_Resolution;
	u16 Local_NumberOFCompareMatch=Copy_DelayTime/0.1;
	Global_ValueOFCompareMatch=0.1/Local_TimerClock;

	TIMER0_SetCompareMatchValue(Global_ValueOFCompareMatch);
	TIMER0_u8SetCallBack(Func);

	Global_NumberOfExcuation=Copy_NumberOfExcuation;





}

void __vector_10 (void)__attribute__((signal));
void __vector_10 (void)
{
	if(Global_Flag==0)

	{

		Copy_PvCallBackRecive();
	}
	else if(Global_Flag==1)
	{
		static u8 Local_Counter=0;
		Local_Counter++;
		if(Local_Counter==Global_ValueOFCompareMatch)
		{
			if(Global_NumberOfExcuation==periodic)
			{
				Copy_PvCallBackRecive();
				Local_Counter=0;
			}
			else if(Global_NumberOfExcuation==once)
			{
				Copy_PvCallBackRecive();
				CLEAR_BIT(TIMSIK,TIMSIK_OCIE0);


			}
		}

	}

}

void __vector_6 (void)__attribute__((signal));
void __vector_6 (void)
{


	Copy_PvCallBackICURecive();


}



