/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:MCAL                          ********************/
/*****************       SWC:TIMERS                          ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/
#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define RISING_EDGE  1
#define FILLING_EDGE 0

#define Enable  1
#define Disable 0

#define periodic 1
#define once 0

void TIMER0_SetCompareMatchValue(u8 Copy_u8Value);
void TIMER0_VoidIntl(void);
u8 TIMER0_u8SetCallBack(void(*Copy_PvCallBackFunc)(void));

void TIMER1_VoidIntl(void);
void TIMER1_SetCompareMatchChannelAValue(u16 Copy_u8Value);
void TIMER1_SetCompareMatchChannelBValue(u16 Copy_u8Value);
void TIMER1_SetICR1Value(u16 Copy_u8Value);
void TIMER1_SetTimerValue(u16 Copy_u8Value);
u16 TIMER1_GetTimerReading(void);
void TIMER1_ICUSetTriggerEdge(u16 Copy_u8Value);
void TIMER1_ICUInterruptEnableAndDisable(u16 Copy_u8Value);
u16 TIMER1_ICUReadValue(void);
u8 ICU_u8SetCallBack(void(*Copy_PvCallBackFunc)(void));

void WDT_voidSleep(u8 Copy_SleepTimeValue);
void WDT_voidEnable(void);
void WDT_voidDisable(void);

void TIMER_voidschedual(u16 Copy_DelayTime,void(*Func)(void),u16 Copy_NumberOfExcuation);

u16 Map_s32GetMapValue(u16 copy_s32InputMin,u16 copy_s32InputMax,u16 copy_s32outputMin,u16 copy_s32OutputMax,u16 copy_s32InputValue);






#endif
