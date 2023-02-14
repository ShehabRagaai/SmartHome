/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:HAL                           ********************/
/*****************       SWC:CLCD                            *********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/

#include"STD_TYPES.h"
#include<util/delay.h>
#include"DIO_interface.h"
#include"CLCD_config.h"
#include"CLCD_interface.h"

void CLCD_voidCommand(u8 copy_u8Command)
{
	/*Set RS pin low for command*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);
	/*Set RW pin high to write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
	/*Send command to data pins*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,copy_u8Command);
	/*Send enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);



}
void CLCD_voidSendData(u8 copy_u8Data)
{
	/*Set RS pin high for data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);
	/*Set RW pin high to write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
	/*Send data to data pins*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,copy_u8Data);
	/*Send enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);

}

void CLCD_voidInit(void)
{
	/*delay for more than 30 ms */
	_delay_ms(30);
	/*Function set command:2 lines,5*8 font size*/
	CLCD_voidCommand(0b00111000);
	/*Display ON/OFF control:Display enable,cursor disable,NO Blink cursor*/
	CLCD_voidCommand(0b00001100);
	/*Clear display*/
	CLCD_voidCommand(0b00000001);



}


void CLCD_voidSendString(const char* copy_Pcstring)
{
	u8 Local_u8Counter=0;

	while(copy_Pcstring[Local_u8Counter]!= '\0')

	{
		CLCD_voidSendData(copy_Pcstring[Local_u8Counter]);
		Local_u8Counter++;
	}
}

void CLCD_GoTOXY(u8 copy_u8Xpos,u8 copy_u8Ypos)
{
	u8 Local_u8Address;
	/*Location at first line*/
	if(copy_u8Xpos==0)
	{
		Local_u8Address=copy_u8Ypos;

	}

	/*Location at second line*/

	else if(copy_u8Xpos==1)
	{
		Local_u8Address=0x40+copy_u8Ypos;
	}

	/*Set DDRAM address in Address Counter */
	CLCD_voidCommand(Local_u8Address+128);
}

void CLCD_WriteSpecialCharacter(u8* copy_Pu8Pattern,u8 copy_PatternNumber,u8 copy_u8Xpos,u8 copy_u8Ypos)
{
	u8 Local_u8GCRAMAddress;
	u8 Local_u8Counter;
	Local_u8GCRAMAddress=copy_PatternNumber*8;
	CLCD_voidCommand(Local_u8GCRAMAddress+64);
	for(Local_u8Counter=0;Local_u8Counter<8;Local_u8Counter++)
	{
		CLCD_voidSendData(copy_Pu8Pattern[Local_u8Counter]);
	}

	CLCD_GoTOXY(copy_u8Xpos,copy_u8Ypos);

	CLCD_voidSendData(copy_PatternNumber);



}


void CLCD_voidWriteNumber(u32 copy_u32Number)
{
	u8 Local_u8Digit;
	u8 Local_u8Counter=0;
	s8 Local_u8Counter2;
	static u8 Local_ArrayOfChar[10]={'0','1','2','3','4','5','6','7','8','9'};
	static u8 Local_ArrayOfDigits[10];

	if(copy_u32Number==0)
	{
		CLCD_voidSendData(Local_ArrayOfChar[0]);
	}
	else
	{

		while(copy_u32Number>0)
		{
			Local_u8Digit=copy_u32Number%10;
			copy_u32Number=copy_u32Number/10;
			Local_ArrayOfDigits[Local_u8Counter]=Local_ArrayOfChar[Local_u8Digit];
			Local_u8Counter++;
		}

		for(Local_u8Counter2=Local_u8Counter-1;Local_u8Counter2>=0;Local_u8Counter2--)
		{
			CLCD_voidSendData(Local_ArrayOfDigits[Local_u8Counter2]);
		}
	}
}


