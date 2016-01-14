#ifndef __TEST_H__
#define __TEST_H__
#include "MC96F8316.h"

typedef  unsigned char		u8;
typedef	 unsigned short 		u16;		
typedef 	 unsigned long		u32;

//#define LED_DEBUG	0

//adc value
#define ADC_START_BATTERY_DETECT		100


#define 		ClrWdt()		WDTCR = 0xE0
#define		NOP()		_nop_()

#define GET_BATTERY_STATUS()	(P0&0x08)

//led1
#define LED1_R_ON()		P33 = 0
#define LED1_R_OFF()		P33 = 1

#define LED1_G_ON()		P35 = 0
#define LED1_G_OFF()	P35 = 1

//led2
#define LED2_R_ON()		P32 = 0
#define LED2_R_OFF()		P32 = 1

#define LED2_G_ON()		P34 = 0
#define LED2_G_OFF()	P34 = 1

//led3
#define LED3_R_ON()		P31 = 0
#define LED3_R_OFF()		P31 = 1

#define LED3_G_ON()		P00 = 0
#define LED3_G_OFF()	P00 = 1

//led4
#define LED4_R_ON()		P30 = 0
#define LED4_R_OFF()		P30 = 1

#define LED4_G_ON()		P37 = 0
#define LED4_G_OFF()	P37 = 1


#define CLOSE_CHANNEL_1()	P23 = 1
#define OPEN_CHANNEL_1()	P23 = 0

#define CLOSE_CHANNEL_2()	P24 = 1
#define OPEN_CHANNEL_2()	P24 = 0

#define CLOSE_CHANNEL_3()	P25 = 1
#define OPEN_CHANNEL_3()	P25 = 0

#define CLOSE_CHANNEL_4()	P02 = 1
#define OPEN_CHANNEL_4()	P02 = 0


#define TEST_AA_BATTERY	0x08	
#define TEST_AAA_BATTERY	0x00

#define TEST_CHANNEL_1	1
#define TEST_CHANNEL_2	2
#define TEST_CHANNEL_3	3
#define TEST_CHANNEL_4	4

#define CHANNEL_CUR_1	11
#define CHANNEL_CUR_2	12
#define CHANNEL_CUR_3	13
#define CHANNEL_CUR_4	10





u16 getAverage(u8 test_pos);
u16 getAdcValue(u8 channel);
void dumpHandler();
void delay_ms(u16 nus);
#endif
