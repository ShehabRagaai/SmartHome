/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:HAL                           ********************/
/*****************       SWC:CLCD                            ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/


#ifndef CLCD_INTERFACE_H_H
#define CLCD_INTERFACE_H_H
void CLCD_voidCommand(u8 copy_u8Command);
void CLCD_voidSendData(u8 copy_u8Data);
void CLCD_voidInit(void);
void CLCD_voidSendString(const char*copy_Pcstring);
void CLCD_GoTOXY(u8 copy_u8Xpos,u8 copy_u8Ypos);
void CLCD_WriteSpecialCharacter(u8* copy_Pu8Pattern,u8 copy_PatternNumber,u8 copy_u8Xpos,u8 copy_u8Ypos);
void CLCD_voidWriteNumber(u32 copy_u32Number);

#endif
