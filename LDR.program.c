/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:HAL                          ********************/
/*****************       SWC:Servo                          ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/

#include"STD_TYPES.h"
#include"ADC_interface.h"
#include"DIO_interface.h"

void LDR_voidAdjustLight(void)
{
	u8 copy_u8RecieveReading=0;
	ADC_voidINTIL();
	ADC_u8StartConversionSnch(0,&copy_u8RecieveReading);
	if(copy_u8RecieveReading>=0&&copy_u8RecieveReading<32)
	{
		DIO_u8SetPortValue(DIO_u8PORTA,0b00000001);
	}
	else if (copy_u8RecieveReading>=32&&copy_u8RecieveReading<64)
	{
		DIO_u8SetPortValue(DIO_u8PORTA,0b00000011);
	}

	else if (copy_u8RecieveReading>=64&&copy_u8RecieveReading<96)
		{
			DIO_u8SetPortValue(DIO_u8PORTA,0b00000111);
		}
	else if (copy_u8RecieveReading>=96&&copy_u8RecieveReading<128)
			{
				DIO_u8SetPortValue(DIO_u8PORTA,0b00001111);
			}
	else if (copy_u8RecieveReading>=128&&copy_u8RecieveReading<160)
			{
				DIO_u8SetPortValue(DIO_u8PORTA,0b00011111);
			}
	else if (copy_u8RecieveReading>=160&&copy_u8RecieveReading<192)
			{
				DIO_u8SetPortValue(DIO_u8PORTA,0b00111111);
			}
	else if (copy_u8RecieveReading>=192&&copy_u8RecieveReading<224)
			{
				DIO_u8SetPortValue(DIO_u8PORTA,0b01111111);
			}
	else if (copy_u8RecieveReading>=224&&copy_u8RecieveReading<256)
			{
				DIO_u8SetPortValue(DIO_u8PORTA,0b11111111);
			}

}
