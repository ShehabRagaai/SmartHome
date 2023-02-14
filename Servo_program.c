/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:HAL                          ********************/
/*****************       SWC:Servo                          ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/

#include"STD_TYPES.h"
#include"Servo_interface.h"
#include"TIMER_interface.h"

void Servo_voidOpenDoor(void)
{

	/*To get 20 ms Periodic Time That Servo worked ON*/
	TIMER1_SetICR1Value(20000);
	/*to get 180 degree: door open*/
	TIMER1_SetCompareMatchChannelAValue(2500);
}
void Servo_voidCloseDoor(void)
{

	/*To get 20 ms Periodic Time That Servo worked ON*/
	TIMER1_SetICR1Value(20000);
	/*to get 0 degree: door closed*/
	TIMER1_SetCompareMatchChannelAValue(0);
}
