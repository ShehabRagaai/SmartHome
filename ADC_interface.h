/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:MCAL                          ********************/
/*****************       SWC:ADC                            ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_
typedef struct
{
	u8*channel;
	u16*results;
	u8 size;
	void(*NotificationFunc)(void);

}Chain_t;


void ADC_voidINTIL(void);
u8 ADC_u8StartConversionSnch(u8 copy_u8channel,u8*copy_u8PuReading);
u8 ADC_u8StartConversionASnch(u8 copy_u8channel,void (*copy_PvNotifacation)(void),u8* copy_u8PuReading);
u8 ADC_u8ChainStartASnch(Chain_t*Copy_PChain);

#endif
