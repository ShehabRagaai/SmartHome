#include"STD_TYPES.h"
#include"DIO_interface.h"
#include"PORT_interface.h"
#include"CLCD_interface.h"
#include"KEYPAD_interface.h"
#include"Servo_interface.h"
#include"LDR_interface.h"
#include"DM_interface.h"
#include"TIMER_interface.h"
#include"util/delay.h"
#include<stdlib.h>

#define LAST_PAGE 2

typedef struct node
{
	u32 Data;
	struct node*ptr;
}Node;

void main(void)
{
	u32 Local_NewID=0;
	u32 Local_UserDeletedID=0;
	u32 Local_AdminCorrectPassword=1234;
	u32 Local_User_ID=0;
	u32 Local_AdminPassword=0;
	u32 Local_DeleteIDCounter1=1;
	u32 Local_Iterator1=1;
    u32 Local_IDcounter1=1;
	u32 Local_counter1=1;

	u8 Local_u8UserIDRecieve;
	u8 Local_u8UserDeletedIDRecieve;
	u8 Local_u8Mode;
	u8 Local_u8AdminPassRecieve;
	u8 Local_u8Recieve;
	u8 Local_u8AddORDelete;
	u8 Local_counter2=0;
	u8 Local_DeleteIDCounter2=0;
	u8 Local_Iterator2=0;
	u8 Local_Flag=0;
	u8 Local_u8Button;
	u8 Local_IDcounter2=0;
	u8 Local_u8PageNumber=1;
	u8 Local_Flag2=0;
	u8 Local_Flag3=0;

	Node*Search=NULL;
	Node*Search_Temp=NULL;
	Node*ID_Search=NULL;
	Node*ID_Search2=0;
	Node* Head=NULL;
	Node*Head_Temp=NULL;



	PORT_voidInit();
	CLCD_voidInit();
	TIMER1_VoidIntl();

	// while(1)
	CLCD_voidCommand(1);
	CLCD_GoTOXY(0,4);
	CLCD_voidSendString("Welcome");
	_delay_ms(3000);
	do
	{
		CLCD_GoTOXY(0,0);
		CLCD_voidSendString("1.Admin Mode");
		CLCD_GoTOXY(1,0);
		CLCD_voidSendString("2.User Mode");
		Local_u8Mode=KPD_u8GetPressKey();
	}while(Local_u8Mode==KPD_NO_PRESSED_KEY||(Local_u8Mode!=1&&Local_u8Mode!=2));

	switch(Local_u8Mode)
	{
	case 1:
		CLCD_voidCommand(1);
		do
		{
			CLCD_GoTOXY(0,0);
			CLCD_voidSendString("Enter Password:");
			Local_u8AdminPassRecieve=KPD_u8GetPressKey();
			if(Local_u8AdminPassRecieve==KPD_NO_PRESSED_KEY)
			{
				//Do Nothing
			}
			else
			{
				Local_AdminPassword=Local_AdminPassword+Local_u8AdminPassRecieve*Local_counter1;
				CLCD_GoTOXY(1,0);
				CLCD_voidSendData('*');
				Local_counter1*=10;
				Local_counter2++;
			}

		}while(Local_u8AdminPassRecieve!=Start&&Local_counter2<10);

		CLCD_voidCommand(1);
		CLCD_GoTOXY(0,4);
		CLCD_voidSendString("Checking");
		_delay_ms(1000);

		if(Local_AdminPassword==Local_AdminCorrectPassword)
		{
			Local_AdminPassword=0;
			Local_counter1=1;
			Local_counter2=0;
			do
			{
				CLCD_voidCommand(1);
				CLCD_GoTOXY(0,0);
				CLCD_voidSendString("1.Add New ID");
				CLCD_GoTOXY(1,0);
				CLCD_voidSendString("2.Delete old ID");
				Local_u8AddORDelete=KPD_u8GetPressKey();
			}while(Local_u8AddORDelete==KPD_NO_PRESSED_KEY||(Local_u8AddORDelete!=1&&Local_u8AddORDelete!=2));



			switch(Local_u8AddORDelete)
			{
			case 1:
				CLCD_voidCommand(1);
				do
				{
					CLCD_GoTOXY(0,0);
					CLCD_voidSendString("Add New ID:");
					Local_u8UserIDRecieve=KPD_u8GetPressKey();
					if(Local_u8AdminPassRecieve==KPD_NO_PRESSED_KEY)
					{
						//Do Nothing
					}
					else
					{
						Local_NewID=Local_NewID+Local_u8UserIDRecieve*Local_IDcounter1;
						CLCD_GoTOXY(1,0);
						CLCD_voidSendData('*');
						Local_IDcounter1*=10;
						Local_IDcounter2++;
					}
				}while(Local_u8UserIDRecieve!=Start&&Local_IDcounter2<10);

				CLCD_voidCommand(1);
				CLCD_GoTOXY(0,4);
				CLCD_voidSendString("Checking");
				_delay_ms(1000);

				/*Add Node In Linked List By FILO Method*/
				ID_Search=Head;
				while(ID_Search->ptr!=NULL)
				{
					if(ID_Search->Data==Local_NewID)
					{
						Local_Flag3=1;
						break;
					}

				}

				if(Local_Flag3==1)
				{
					CLCD_voidCommand(1);
					CLCD_GoTOXY(0,0);
					CLCD_voidSendString("This ID used");
					Local_NewID=0;
					Local_IDcounter1=1;
					Local_IDcounter2=0;


				}

				else
				{

					Head_Temp=Head;
					Head=(Node*)malloc(sizeof(Node));
					Head->Data=Local_NewID;
					Head->ptr=Head_Temp;
					Local_NewID=0;
					Local_IDcounter1=1;
					Local_IDcounter2=0;
					CLCD_voidCommand(1);
					CLCD_GoTOXY(0,0);
					CLCD_voidSendString("ID Added");
				}

				break;
			case 2:
				CLCD_voidCommand(1);
				do
				{
					CLCD_GoTOXY(0,0);
					CLCD_voidSendString("Deleted ID:");
					Local_u8UserDeletedIDRecieve=KPD_u8GetPressKey();
					if(Local_u8UserDeletedIDRecieve==KPD_NO_PRESSED_KEY)
					{
						//DO NOTHING
					}
					else
					{
						Local_UserDeletedID=Local_UserDeletedID+Local_u8UserDeletedIDRecieve*Local_DeleteIDCounter1;
						CLCD_GoTOXY(1,0);
						CLCD_voidWriteNumber(Local_u8UserDeletedIDRecieve);
						Local_DeleteIDCounter1*=10;
						Local_DeleteIDCounter2++;

					}


				}while(Local_u8UserDeletedIDRecieve!=Start&&Local_DeleteIDCounter2<10);

				CLCD_voidCommand(1);
				CLCD_GoTOXY(0,4);
				CLCD_voidSendString("Checking");
				_delay_ms(1000);
				/*Delete Node In Linked List By FILO Method*/
				Search=Head;
				while(Search!=NULL)
				{

					if(Search->Data==Local_UserDeletedID)
					{
						if(Search==Head)
						{
							Head=Search->ptr;
							free(Search);

						}
						else
						{
							Search_Temp->ptr=Search->ptr;
							free(Search);


						}
						Local_Flag2=1;
						break;
					}

					Search_Temp=Search;
					Search=Search->ptr;
				}
				if(Local_Flag2==0)
				{
					CLCD_voidCommand(1);
					CLCD_GoTOXY(0,0);
					CLCD_voidSendString("ID Not Found");
				}
				else
				{
					CLCD_voidCommand(1);
					CLCD_GoTOXY(0,4);
					CLCD_voidSendString("Deleted");
				}
				Local_UserDeletedID=0;
				Local_DeleteIDCounter1=1;
				Local_DeleteIDCounter2=0;

				break;
			}

		}
		else
		{
			Local_AdminPassword=0;
			Local_DeleteIDCounter1=1;
			Local_DeleteIDCounter2=0;

			CLCD_voidCommand(1);
			CLCD_GoTOXY(0,0);
			CLCD_voidSendString("Wrong Password");

		}



		break;


	case 2:
		CLCD_voidCommand(1);
		CLCD_GoTOXY(0,0);
		CLCD_voidSendString("Enter ID:");
		CLCD_GoTOXY(1,0);

		do
		{
			Local_u8Button=KPD_u8GetPressKey();
			if(Local_u8Button==KPD_NO_PRESSED_KEY)
			{
				//DO NOTHING
			}
			else
			{
				Local_User_ID=Local_User_ID+Local_u8Button*Local_Iterator1;

				CLCD_voidSendData('*');
				Local_Iterator1*=10;
				Local_Iterator2++;
			}
		}while(Local_u8Button!=Start&&Local_Iterator2<10);



		CLCD_voidCommand(1);

		CLCD_GoTOXY(0,4);

		CLCD_voidSendString("Checking");
		_delay_ms(1000);

		ID_Search2=Head;
		while(ID_Search2->ptr!=NULL)
		{
			if(ID_Search2->Data==Local_User_ID)
			{
				Local_Flag=1;
				break;
			}
		}

		if(Local_Flag==0)
		{
			Local_User_ID=0;
			Local_Iterator1=1;
			Local_Iterator1=0;
			CLCD_voidCommand(1);
			CLCD_GoTOXY(0,0);
			CLCD_voidSendString("Welcome TO My");
			CLCD_GoTOXY(1,0);
			CLCD_voidSendString("SmartHome");
			_delay_ms(1000);
			CLCD_voidCommand(1);
			CLCD_GoTOXY(0,0);
			CLCD_voidSendString("Choose options");
			CLCD_GoTOXY(1,0);
			CLCD_voidSendString("from the menu");
			_delay_ms(1000);


			while(1)
			{
				Local_u8Recieve=KPD_u8GetPressKey();
				CLCD_voidCommand(1);

				while(Local_u8Recieve==KPD_NO_PRESSED_KEY||Local_u8Recieve==Down||Local_u8Recieve==Up)
				{
					if(Local_u8PageNumber==1)
					{
						CLCD_GoTOXY(0,0);
						CLCD_voidSendString("1.O_D");
						CLCD_GoTOXY(0,6);
						CLCD_voidSendString("2.C_D");
						CLCD_GoTOXY(1,0);
						CLCD_voidSendString("3.O_L");
						CLCD_GoTOXY(1,6);
						CLCD_voidSendString("4.C_L");
						CLCD_GoTOXY(1,11);
						CLCD_voidSendString("5.Down");
					}
					else if(Local_u8PageNumber==LAST_PAGE)
					{
						CLCD_GoTOXY(0,0);
						CLCD_voidSendString("6.A_L");
						CLCD_GoTOXY(0,6);
						CLCD_voidSendString("7.O_F");
						CLCD_GoTOXY(1,0);
						CLCD_voidSendString("8.C_F");
						CLCD_GoTOXY(1,6);
						CLCD_voidSendString("9.A_F");
						CLCD_GoTOXY(1,11);
						CLCD_voidSendString("10.Up");
					}
					Local_u8Recieve=KPD_u8GetPressKey();
					if(Local_u8Recieve==Up&&Local_u8PageNumber<1)
					{
						Local_u8PageNumber--;
					}
					else if(Local_u8Recieve==Down&&Local_u8PageNumber<LAST_PAGE)
					{
						Local_u8PageNumber++;

					}
				}

				if(Local_u8PageNumber==1)
				{

					switch(Local_u8Recieve)
					{
					/*Open Door*/
					case 1:
						Servo_voidCloseDoor();
						CLCD_voidCommand(1);
						CLCD_GoTOXY(0,4);
						CLCD_voidSendString("DOOR OPENING");
						_delay_ms(2000);
						break;

						/*Closed Door*/
					case 2:
						Servo_voidCloseDoor();
						CLCD_voidCommand(1);
						CLCD_GoTOXY(0,4);
						CLCD_voidSendString("DOOR CLOSING");
						_delay_ms(2000);
						break;
						/*Open All Light*/
					case 3:
						DIO_u8SetPortValue(DIO_u8PORTB,DIO_u8PORT_HIGH);
						CLCD_voidCommand(1);
						CLCD_GoTOXY(0,4);
						CLCD_voidSendString("Light OPENING");
						_delay_ms(2000);
						break;
						/*Close All Light */
					case 4:
						DIO_u8SetPortValue(DIO_u8PORTB,DIO_u8PORT_LOW);
						CLCD_voidCommand(1);
						CLCD_GoTOXY(0,4);
						CLCD_voidSendString("Light CLOSING");
						_delay_ms(2000);
						break;

					}
				}
				else if(Local_u8PageNumber==LAST_PAGE)
				{
					switch (Local_u8Recieve)
					{
					/*Adjust Light by LDR*/
					case 6:
						LDR_voidAdjustLight();
						CLCD_voidCommand(1);
						CLCD_GoTOXY(0,4);
						CLCD_voidSendString("Light Adjusting");
						_delay_ms(2000);
						break;
						/*Open Fan*/
					case 7:
						DC_voidOpenFan();
						CLCD_voidCommand(1);
						CLCD_GoTOXY(0,4);
						CLCD_voidSendString("Fan Opening");
						break;
						/*Closed Fan*/
					case 8:
						CLCD_voidCommand(1);
						CLCD_GoTOXY(0,4);
						CLCD_voidSendString("Fan Closing");
						DC_voidClosedFan();
						break;
						/*Adjust Fan*/
					case 9:
						DC_voidAdjustFan();
						CLCD_voidCommand(1);
						CLCD_GoTOXY(0,4);
						CLCD_voidSendString("Fan Adjusting");
						break;
					}
				}



			}

		}

		else
		{

			CLCD_voidCommand(1);
			CLCD_GoTOXY(0,4);
			CLCD_voidSendString("Wrong ID");
			Local_User_ID=0;
			Local_Iterator1=1;
			Local_Iterator2=0;


		}
		break;
	}

}


