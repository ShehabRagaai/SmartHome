/***********************;*********************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:HAL                           ********************/
/*****************       SWC:KEYPAD                          ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/

#include"STD_TYPES.h"
#include"DIO_interface.h"
#include"KEYPAD_config.h"
#include"KEYPAD_interface.h"

u8 KPD_u8GetPressKey(void)
{
	u8 Local_u8PressedKey=KPD_NO_PRESSED_KEY;
	u8 Local_u8ColumnIdx;
	u8 Local_u8RowIdx;
	u8 Local_u8PinState;
	static u8 Local_u8ColumnArr[COLUMN_NUM]={KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN,KPD_COLUMN3_PIN};
	static u8 Local_u8RowArr[ROW_NUM]={KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};
	static u8 Local_u8KpdArr[ROW_NUM][COLUMN_NUM]= KPD_AAR_VAL;

	for(Local_u8ColumnIdx=0;Local_u8ColumnIdx<COLUMN_NUM;Local_u8ColumnIdx++)
	{
		DIO_u8SetPinValue(KPD_PORT,Local_u8ColumnArr[Local_u8ColumnIdx],DIO_u8PIN_LOW);

		for(Local_u8RowIdx=0;Local_u8RowIdx<ROW_NUM;Local_u8RowIdx++)
		{
			DIO_u8GetPinValue(KPD_PORT,Local_u8RowArr[Local_u8RowIdx],&Local_u8PinState);
			if(Local_u8PinState==DIO_u8PIN_LOW)
			{
				Local_u8PressedKey=Local_u8KpdArr[Local_u8RowIdx][Local_u8ColumnIdx];
				while(Local_u8PinState==DIO_u8PIN_LOW)
				{
					DIO_u8GetPinValue(KPD_PORT,Local_u8RowArr[Local_u8RowIdx],&Local_u8PinState);
				}

				return Local_u8PressedKey;
			}

		}

		DIO_u8SetPinValue(KPD_PORT,Local_u8ColumnArr[Local_u8ColumnIdx],DIO_u8PIN_HIGH);

	}


	return Local_u8PressedKey;
}
