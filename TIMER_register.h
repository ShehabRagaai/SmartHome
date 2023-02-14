/********************************************************************************/
/********************************************************************************/
/*****************       Aathur:Shehab Ahmed Ragaai          ********************/
/*****************       Layer:MCAL                           ********************/
/*****************       SWC:TIMERS                             ********************/
/*****************       version:1.00                        ********************/
/********************************************************************************/
/********************************************************************************/

#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_

#define TCCR0  *((volatile u8*)0x53)
#define TCCR0_WGM00 6
#define TCCR0_WGM01 3
#define TCCR0_CS02  2
#define TCCR0_CS01  1
#define TCCR0_CS00  0
#define TCCR0_COM0  4
#define TCCR0_COM1  5


#define OCR0  *((volatile u8*)0x5C)

#define TIMSIK *((volatile u8*)0x59)
#define TIMSIK_TOIE0  0
#define TIMSIK_OCIE0  1
#define TIMSIK_TICIE1 5



#define TCCR1A   *((volatile u8*)0X4F)
#define TCCR1A_WGM10     0
#define TCCR1A_WGM11     1
#define TCCR1A_COM1A0    6
#define TCCR1A_COM1A1    7
#define TCCR1A_COM1B0	 4
#define TCCR1A_COM1B1    5

#define TCCR1B   *((volatile u8*)0X4E)
#define TCCR1B_CS10  0
#define TCCR1B_CS11  1
#define TCCR1B_CS12  2
#define TCCR1B_WGM12 3
#define TCCR1B_WGM13 4
#define TCCR1B_ICES1 6

#define OCR1A     *((volatile u16*)0X4A)
#define OCR1B     *((volatile u16*)0X48)
#define ICR1      *((volatile u16*)0X46)

#define TCNT1     *((volatile u16*)0X4C)

#define WDTCR     *((volatile u8*)0X41)
#define WDTCR_WDTOE 4
#define WDTCR_WDE   3
#define WDTCR_WDP0  0
#define WDTCR_WDP1  1
#define WDTCR_WDP2  2



#endif
