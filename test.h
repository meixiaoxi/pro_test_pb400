#ifndef __TEST_H__
#define __TEST_H__
#include "MC96F8316.h"

typedef  unsigned char		u8;
typedef	 unsigned short 		u16;		
typedef 	 unsigned long		u32;

//#define IO_DEBUG	0

#ifdef IO_DEBUG
#warning "enable IO debug"
#endif


#define ENABLE_FAST_TEST_MODE

//adc value
#define ADC_CURRENT_LEVEL_1_MIN	2358	//1900
#define ADC_CURRENT_LEVEL_1_MAX	3103	//2500

#define ADC_CURRENT_LEVEL_2_MIN	744		//600
#define ADC_CURRENT_LEVEL_2_MAX	1489	//1200

#define ADC_CURRENT_LEVEL_3_MIN	124		//100	
#define ADC_CURRENT_LEVEL_3_MAX	744		//600

#define ADC_START_BATTERY_DETECT		20

#define ADC_NO_CURRENT					10
#define ADC_START_BATTERY_CHARGING	20
#define ADC_CURRENT_BATTERY_DETECT	


#define ADC_CURRENT_LEVEL_1_MIN_AAA	868		//700
#define ADC_CURRENT_LEVEL_1_MAX_AAA	1242	//1000

#define ADC_CURRENT_LEVEL_2_MIN_AAA	248		//200
#define ADC_CURRENT_LEVEL_2_MAX_AAA	621		//500

#define ADC_CURRENT_LEVEL_3_MIN_AAA	62		//50	
#define ADC_CURRENT_LEVEL_3_MAX_AAA	373		//300

//time
#define 	MAX_TIME_BATTERY_DEAD		4	//  10ms

//60ms   
#define 	MIN_TIME_TO_BATTERY_DETECT		3
#define	MAX_TIME_TO_BATTERY_DETECT	8 

//200ms
#define MIN_TIME_TO_BATTERY_NORMAL_CHARGING	16
#define MAX_TIME_TO_BATTERY_NORMAL_CHARGING	22

#define MIN_TIME_TO_BATTERY_NORMAL_CHARGING_SPEC	10

//200ms
#define 	MAX_TIME_DURING_BATTERY_DETECT		25
#define 	MIN_TIME_DURING_BATTERY_DETECT		18	

//200ms
#define 	MIN_TIME_DURING_BATTERY_NORMAL_CHARGING	MIN_TIME_DURING_BATTERY_DETECT
#define 	MAX_TIME_DURING_BATTERY_NORMAL_CHARGING	MAX_TIME_DURING_BATTERY_DETECT

#define    getSysTick()	EA = 0;\
						NOP();\
	nowSysTick = gSysTick;\
	NOP();\
	EA=1;\
	

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


#define LED_ALL_OFF()	LED1_G_OFF(),LED2_G_OFF(),LED3_G_OFF(),LED4_G_OFF()

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
