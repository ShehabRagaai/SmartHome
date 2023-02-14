/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:HAL                           ********************/
/*****************       SWC:DC MOTOR                        ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/
#include"STD_TYPES.h"
#include"DIO_interface.h"
#include"DM_interface.h"
#include"DM_config.h"
#include"TIMER_interface.h"
#include"ADC_interface.h"

 void DC_voidClockWise(void)
 {

	 DIO_u8SetPinValue(DM_ActivePORT ,DM_ActiveCCWPin,DIO_u8PIN_LOW);
	 DIO_u8SetPinValue(DM_ActivePORT ,DM_ActiveCWPin,DIO_u8PIN_HIGH);

 }


 void DC_voidCounterClockWise(void)
  {
 	 DIO_u8SetPinValue(DM_ActivePORT ,DM_ActiveCWPin,DIO_u8PIN_LOW);
 	 DIO_u8SetPinValue(DM_ActivePORT ,DM_ActiveCCWPin,DIO_u8PIN_HIGH);
  }

 void DC_voidBreak(void)

 {
	 DIO_u8SetPinValue(DM_ActivePORT ,DM_ActiveCWPin,DIO_u8PIN_LOW);
	 DIO_u8SetPinValue(DM_ActivePORT ,DM_ActiveCCWPin,DIO_u8PIN_LOW);
 }

 void DC_voidOpenFan(void)
 {

	 TIMER1_SetICR1Value(20000);
	 TIMER1_SetCompareMatchChannelBValue(20000);

 }

 void DC_voidClosedFan(void)
  {
	 TIMER1_SetICR1Value(20000);
 	 TIMER1_SetCompareMatchChannelBValue(0);

  }

 void DC_voidAdjustFan(void)
 {
	 u8 copy_u8RecieveReading=0;
	 u16 copy_u8RecieveMilliVoltage=0;
	 u8 Copy_u8Temp=0;
	 ADC_u8StartConversionSnch(1,&copy_u8RecieveReading);
	 TIMER1_SetICR1Value(20000);
	 copy_u8RecieveMilliVoltage=copy_u8RecieveReading*(5000/256);
	 Copy_u8Temp=copy_u8RecieveMilliVoltage/10;
	 if(Copy_u8Temp>=0&&Copy_u8Temp<15)
	 {
		 TIMER1_SetCompareMatchChannelBValue(5000);
	 }
	 else if(Copy_u8Temp>=15&&Copy_u8Temp<25)
	 {
		 TIMER1_SetCompareMatchChannelBValue(10000);
	 }
	 else if(Copy_u8Temp>=25&&Copy_u8Temp<35)
	 {
		 TIMER1_SetCompareMatchChannelBValue(15000);
	 }
	 else if(Copy_u8Temp>=35&&Copy_u8Temp<50)
		 {
			 TIMER1_SetCompareMatchChannelBValue(20000);
		 }
	}
