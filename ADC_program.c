/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:MCAL                          ********************/
/*****************       SWC:ADC                             ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"ADC_interface.h"
#include"ADC_register.h"
#include"ADC_config.h"
#include"ADC_private.h"

static u8 Global_u8BusyState=IDEL;
static u8* Global_u8ADCReading=NULL;
void (*Global_PvFunc)(void)=NULL;
static u8* Global_u8chainchannels;
static u16* Global_u8chainresults;
static u8 Global_u8chainSize;
void (*GlobalChain_PvFunc)(void)=NULL;
u8 Global_u8Index=0;
u8 ADC_u8ISR_Source;






void ADC_voidINTIL(void)
{
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLEAR_BIT(ADMUX,ADMUX_REFS1);

	SET_BIT(ADMUX,ADMUX_ADLAR);

	SET_BIT(ADCSRA,ADCSRA_ADPS2);
	SET_BIT(ADCSRA,ADCSRA_ADPS1);
	SET_BIT(ADCSRA,ADCSRA_ADPS0);


	SET_BIT(ADCSRA,ADCSRA_ADEN);

}


u8 ADC_u8StartConversionSnch(u8 copy_u8channel,u8*copy_u8PuReading)
{
	u8 Local_u8StateError=0;
	u32 Local_u32Counter;

	if(Global_u8BusyState==BUSY)
	{
		Local_u8StateError=1;
	}
	else
	{
		Global_u8BusyState=BUSY;
		ADMUX&=0b11100000;
		ADMUX|=copy_u8channel;

		SET_BIT(ADCSRA,ADCSRA_ADSC);

		while(GET_BIT(ADCSRA,ADCSRA_ADIF)==0 && Local_u32Counter<TIME_OUT)
		{
			Local_u32Counter++;
		}

		if(Local_u32Counter==TIME_OUT)
		{
			Local_u8StateError=1;
		}
		else
		{

			SET_BIT(ADCSRA,ADCSRA_ADIF);
			*copy_u8PuReading=ADCH;
			Global_u8BusyState=IDEL;
		}

	}

	return Local_u8StateError;
}

u8 ADC_u8StartConversionASnch(u8 copy_u8channel,void (*copy_PvNotifacation)(void),u8* copy_u8PuReading)
{
	u8 Local_u32StateError=0;
	if(Global_u8BusyState==BUSY)
	{
		Local_u32StateError=1;
	}
	else
	{

		Global_u8BusyState=BUSY;
		ADC_u8ISR_Source=Single_Conversion;
		ADMUX&=0b11100000;
		ADMUX|=copy_u8channel;

		SET_BIT(ADCSRA,ADCSRA_ADSC);

		SET_BIT(ADCSRA,ADCSRA_ADIE);

		Global_u8ADCReading=copy_u8PuReading;
		Global_PvFunc=copy_PvNotifacation;
	}


	return Local_u32StateError;




}



/*Reentrant Function*/
u8 ADC_u8ChainStartASnch(Chain_t*Copy_PChain)
{
	u8 Local_u32StateError=0;
	Global_u8Index=0;



	if(Copy_PChain==NULL)
	{
		Local_u32StateError=1;
	}
	else
	{
		if(Global_u8BusyState==IDEL)
		{
			Global_u8BusyState=BUSY;
			ADC_u8ISR_Source=Chain_Conversion;
			Global_u8chainchannels=Copy_PChain->channel;
			Global_u8chainresults=Copy_PChain->results;
			Global_u8chainSize=Copy_PChain->size;
			GlobalChain_PvFunc=Copy_PChain->NotificationFunc;

			ADMUX&=0b11100000;
			ADMUX|=Global_u8chainchannels[Global_u8Index];

			SET_BIT(ADCSRA,ADCSRA_ADSC);

			SET_BIT(ADCSRA,ADCSRA_ADIE);









		}
		else
		{
			Local_u32StateError=2;
		}
	}

	return Local_u32StateError;
}

void __vector_16 (void)__attribute((signal));
void __vector_16 (void)
{
	if(ADC_u8ISR_Source==Single_Conversion)
	{
	*Global_u8ADCReading=ADCH;
	 Global_u8BusyState=IDEL;
	 Global_PvFunc();
	}
	else if(ADC_u8ISR_Source==Chain_Conversion)
	{
		Global_u8chainresults[Global_u8Index]=ADCH;
		Global_u8Index++;
		if(Global_u8Index==Global_u8chainSize)
		{
			Global_u8BusyState=IDEL;
			GlobalChain_PvFunc();
			CLEAR_BIT(ADCSRA,ADCSRA_ADIE);

		}
		else
		{
			ADMUX&=0b11100000;
			ADMUX|=Global_u8chainchannels[Global_u8Index];
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}

	}

}


