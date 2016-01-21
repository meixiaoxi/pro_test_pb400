#include "MC96F8316.h"
#include "test.h"
#include "intrins.h"

u8 gTestMode = TEST_AA_BATTERY;
u32 gSysTick = 0;
u8 stepNow = 1;
u8 test_pos_now = TEST_CHANNEL_1;
void LED_ON(u8 num)
{
	switch(num)
	{
		case 0:
				LED1_R_ON();break;
		case 1:
				LED2_R_ON();break;
		case 2:
				LED3_R_ON();break;
		case 3:
				LED4_R_ON();break;
	}
}
void LED_OFF(u8 num)
{
	switch(num)
	{
		case 0:
				LED1_R_OFF();break;
		case 1:
				LED2_R_OFF();break;
		case 2:
				LED3_R_OFF();break;
		case 3:
				LED4_R_OFF();break;
	}
}
void dumpHandler()
{
u8 ii;
			
			switch(test_pos_now)
			{
				case TEST_CHANNEL_1:
						OPEN_CHANNEL_1();LED1_R_ON();break;
				case TEST_CHANNEL_2:
						OPEN_CHANNEL_2();LED2_R_ON();break;
				case TEST_CHANNEL_3:
						OPEN_CHANNEL_3();LED3_R_ON();break;
				case TEST_CHANNEL_4:
						OPEN_CHANNEL_4();LED4_R_ON();break;
				default:
						dumpHandler();break;
			}

				return;
				for(ii=0; ii <= 3; ii++)
				{
					if(stepNow & (1<<ii))
						LED_ON(ii);
					else
						LED_OFF(ii);
				}
				while(1)
				{
					NOP();
					ClrWdt();
				}

	LED1_R_ON();
	LED2_R_ON();
	LED3_R_ON();
	LED4_R_ON();

	while(1)
	{
		NOP();
		ClrWdt();
	}
}

#ifdef IO_DEBUG
void led_test()
{
/*
	LED1_G_ON();
	LED2_G_ON();
	LED3_G_ON();
	LED4_G_ON();
	delay_ms(500);
	LED1_G_OFF();
	LED2_G_OFF();
	LED3_G_OFF();
	LED4_G_OFF();

	LED1_R_ON();
	LED2_R_ON();
	LED3_R_ON();
	LED4_R_ON();
	delay_ms(500);
	LED1_R_OFF();
	LED2_R_OFF();
	LED3_R_OFF();
	LED4_R_OFF();
	*/
	P0 = 0x00;
	P1=	0x00;
	P2 = 0x00;
	P3 = 0x00;
	delay_ms(500);
	P0 = 0xFF;
	P1 = 0xFF;
	P2 = 0xFF;
	P3 = 0xFF;
	delay_ms(500);
}
#endif

u32 nowSysTick;
	u16	gAdc_Current_Level_1_Min;
	u16	gAdc_Current_Level_1_Max;
	u16	gAdc_Current_Level_2_Min;
	u16	gAdc_Current_Level_2_Max;
	u16	gAdc_Current_Level_3_Min;
	u16	gAdc_Current_Level_3_Max;
	u8	gAdc_Start_Battery_Charging;
void testLoop()
{
	u8 errorCount = 0,test_current_level;
	u32 tempSysTick;
	u16 tCurrentAdc,minCurrent,maxCurrent;

	

	if(gTestMode == TEST_AAA_BATTERY)
	{
		gAdc_Current_Level_1_Min = ADC_CURRENT_LEVEL_1_MIN_AAA;
		gAdc_Current_Level_1_Max = ADC_CURRENT_LEVEL_1_MAX_AAA;
		gAdc_Current_Level_2_Min = ADC_CURRENT_LEVEL_2_MIN_AAA;
		gAdc_Current_Level_2_Max = ADC_CURRENT_LEVEL_2_MAX_AAA;
		gAdc_Current_Level_3_Min = ADC_CURRENT_LEVEL_3_MIN_AAA;
		gAdc_Current_Level_3_Max = ADC_CURRENT_LEVEL_3_MAX_AAA;
		gAdc_Start_Battery_Charging = ADC_START_BATTERY_CHARGING;	
	}
	else
	{
		gAdc_Current_Level_1_Min = ADC_CURRENT_LEVEL_1_MIN;
		gAdc_Current_Level_1_Max = ADC_CURRENT_LEVEL_1_MAX;
		gAdc_Current_Level_2_Min = ADC_CURRENT_LEVEL_2_MIN;
		gAdc_Current_Level_2_Max = ADC_CURRENT_LEVEL_2_MAX;
		gAdc_Current_Level_3_Min = ADC_CURRENT_LEVEL_3_MIN;
		gAdc_Current_Level_3_Max = ADC_CURRENT_LEVEL_3_MAX;
		gAdc_Start_Battery_Charging = ADC_START_BATTERY_CHARGING;
	}
	
	
	



	do{

			switch(test_pos_now)
			{
				case TEST_CHANNEL_1:
						CLOSE_CHANNEL_1();break;
				case TEST_CHANNEL_2:
						CLOSE_CHANNEL_2();break;
				case TEST_CHANNEL_3:
						CLOSE_CHANNEL_3();break;
				case TEST_CHANNEL_4:
						CLOSE_CHANNEL_4();break;
				default:
						dumpHandler();
						goto endpos;
						break;
			}



			//wait for ZERO_STATE---->DETECT_STATE
			//while(getAverage(test_pos_now) > ADC_START_BATTERY_DETECT)
			//	ClrWdt();
			getSysTick();
			tempSysTick = nowSysTick;
			do
			{
				tCurrentAdc = getAverage(test_pos_now);
				if(tCurrentAdc > ADC_NO_CURRENT)
				{
					if(tCurrentAdc > gAdc_Current_Level_1_Min)
					{
						stepNow = 4;
						goto battery_detect;
					}
					else
						break;
				}
				getSysTick();
				if(nowSysTick < tempSysTick || (nowSysTick-tempSysTick) >=	12)
				{
					dumpHandler();
					goto endpos;
				}
				ClrWdt();
				
			}while(1);

			getSysTick();
			tempSysTick = nowSysTick;
			while(getAverage(test_pos_now) > ADC_NO_CURRENT)
			{
				getSysTick();
				if(nowSysTick < tempSysTick || (nowSysTick-tempSysTick) >=	MAX_TIME_BATTERY_DEAD)
				{
					dumpHandler();
					goto endpos;
				}
				ClrWdt();
			}
			stepNow++;
			//ok now battery state is BATTERY_DETECT
			//time wait for battery detect
			tempSysTick = nowSysTick;
			while(getAverage(test_pos_now) < gAdc_Start_Battery_Charging)
			{
				getSysTick();
				if(nowSysTick < tempSysTick  || (nowSysTick-tempSysTick) >=	MAX_TIME_TO_BATTERY_DETECT)
				{
					dumpHandler();
					goto endpos;
				}
			}
			stepNow++;
			if((nowSysTick-tempSysTick) < MIN_TIME_TO_BATTERY_DETECT)
			{
				dumpHandler();
				goto endpos;
			}
			stepNow++;
			
			//BATTERY_DETECT_STATE
		battery_detect:
			getSysTick();
			tempSysTick = nowSysTick;

			delay_ms(10);
			do
			{
				tCurrentAdc = getAverage(test_pos_now);
				if(tCurrentAdc < gAdc_Current_Level_1_Min|| tCurrentAdc > gAdc_Current_Level_1_Max)	// CURRENT_LEVEL_1
				{
					errorCount++;
					if(errorCount > 3)
					{
						dumpHandler();
						goto endpos;
					}
				}

				getSysTick();
				if(nowSysTick < tempSysTick || (nowSysTick-tempSysTick) >=	MAX_TIME_DURING_BATTERY_DETECT)
				{
					dumpHandler();
					goto endpos;
				}
				//delay_ms(10);
				ClrWdt();
			}while(tCurrentAdc > gAdc_Current_Level_1_Min);
			stepNow++;
			if((nowSysTick-tempSysTick) < MIN_TIME_DURING_BATTERY_DETECT)
			{
				dumpHandler();
				goto endpos;
			}
			stepNow++;
			//wait for no current
			tempSysTick = nowSysTick;
			do{
				tCurrentAdc = getAverage(test_pos_now);
				ClrWdt();
				getSysTick();
				if(nowSysTick < tempSysTick || (nowSysTick-tempSysTick) >=4)
				{
					dumpHandler();
					goto endpos;
				}
			}while(tCurrentAdc > ADC_NO_CURRENT);
			stepNow++;
			//ok, now battery state is BATTERY_NORMAL_CHARGING
			//time wait for battery normal charging
			for(test_current_level = 1; test_current_level <=4; test_current_level++)
			{
			errorCount = 0;
			switch(test_current_level)
			{
				case 1:
						minCurrent = gAdc_Current_Level_3_Min;
						maxCurrent = gAdc_Current_Level_3_Max;
						break;
				case 2:
						minCurrent = gAdc_Current_Level_2_Min;
						maxCurrent = gAdc_Current_Level_2_Max;
						break;
				case 3:
				case 4:
						minCurrent = gAdc_Current_Level_1_Min;
						maxCurrent = gAdc_Current_Level_1_Max;
						break;
				default:
						dumpHandler();
						goto endpos;
						break;
			}
			getSysTick();
			tempSysTick = nowSysTick;
			while(getAverage(test_pos_now) < gAdc_Start_Battery_Charging)
			{
				getSysTick();
				if(nowSysTick < tempSysTick  || (nowSysTick-tempSysTick) >=	MAX_TIME_TO_BATTERY_NORMAL_CHARGING)
				{
					dumpHandler();
					goto endpos;
				}
			}
			stepNow++;
			if((nowSysTick-tempSysTick) < MIN_TIME_TO_BATTERY_NORMAL_CHARGING_SPEC)
			{
				dumpHandler();
				goto endpos;
			}
			stepNow++;
			//BATTERY_NORMAL_CHARGING
			getSysTick();
			tempSysTick = nowSysTick;
			delay_ms(10);
			do{
				tCurrentAdc = getAverage(test_pos_now);
				if(tCurrentAdc < minCurrent || tCurrentAdc > maxCurrent)
				{
					errorCount++;
					if(errorCount > 5)
					{
						dumpHandler();
						goto endpos;
					}
				}
				getSysTick();
				if(nowSysTick < tempSysTick || (nowSysTick-tempSysTick) >=	MAX_TIME_DURING_BATTERY_NORMAL_CHARGING)
				{
					dumpHandler();
					goto endpos;
				}
				ClrWdt();
			}while(tCurrentAdc > minCurrent);

			if((nowSysTick-tempSysTick) < MIN_TIME_DURING_BATTERY_NORMAL_CHARGING)
			{
				dumpHandler();
				goto endpos;
			}

			tempSysTick = nowSysTick;
			do{
				tCurrentAdc = getAverage(test_pos_now);
				ClrWdt();
				getSysTick();
				if(nowSysTick < tempSysTick || (nowSysTick-tempSysTick) >=4)
				{
					dumpHandler();
					goto endpos;
				}
			}while(tCurrentAdc > ADC_NO_CURRENT);
		}

			
			switch(test_pos_now)
			{
				case TEST_CHANNEL_1:
						OPEN_CHANNEL_1();
						LED3_G_ON();
						break;
				case TEST_CHANNEL_2:
						OPEN_CHANNEL_2();
						LED4_G_ON();
						break;
				case TEST_CHANNEL_3:
						OPEN_CHANNEL_3();
						LED1_G_ON();
						break;
				case TEST_CHANNEL_4:
						OPEN_CHANNEL_4();
						LED2_G_ON();
						break;
				default:
						dumpHandler();
						goto endpos;
						break;
			}
			
		endpos:
			delay_ms(20);
			test_pos_now++;
	}while(test_pos_now<= TEST_CHANNEL_4);
}

void InitConfig()
{
#ifdef IO_DEBUG
					//					TEST_MODE_SEL	 S4		    --	   LED3_G
    P0IO    = 0xFF;         // out     out    out     out        input              out             out          out                 (0:input   1:output)
    P0OD    = 0x00;        // -      pp     pp      pp            PP                PP               pp            pp                    (0:push-pull   1:open-drain)
    P0PU    = 0x00;         // -      on      on       on           off                off             off           off                  (0:disable      1:enable)               
    P0        = 0x01;	        // -      -       -         -              0              0                0               0
    P03DB   = 0x00;       // 0       0      0       0               0              0                 0              0
    P0FSR   = 0x00;       // 0      0      0       0              0              0                   0            0

                                    //-        V3_CUR_ADC      V2_CUR_ADC   V1_CUR_ADC  V4_CUR_ADC     --             --          --
    P1IO    = 0xFF;         // out         input                       input                input               input         out          out            out
    P1OD    = 0x00;        // pp        PP           PP           pp             PP             PP             PP                 pp
    P1PU    = 0x80;        // on        off          off           off            off             off            off                 off
    P1	  = 0x00;        // 00000000
    P12DB   = 0x00;       // 00000000
    P1FSRH  = 0x00;      // 00         10                        10                       10
     P1FSRL  = 0x00;	 //                                                                                       010              00            00                 0 
    
                                    //-    -  	S3   		 S2        S1       -         -      -
    P2IO    = 0xFF;         //-   out      out          	out         out    out     out     out
    P2OD    = 0x00;         // -   PP      PP              PP             PP      PP      pp     pp
    P2PU    = 0x00;         // -    on     off              off             off     on      on     on
    P2	  = 0x00;		    // -      -      1      1      -      -      -      -
    P2FSR   = 0x00;	   //             00000000

                                     //led4_G    --    led1_G    led2_G    led1_R    led2_R    led3_R   led4_R
    P3IO    = 0xFF;         // out         out      out            out         out           out        out         out
    P3OD    = 0x00;        // PP         PP      PP         PP       PP         PP       PP       PP
    P3PU    = 0x00;         // off       off      off        off       off       off       off       off
    P3	   = 0xFF;	//00000000
    P3FSR   = 0x00;		  // 0        0         0          0         0         0          0        0		

#else
					//					TEST_MODE_SEL	 S4		    --	   LED3_G
    P0IO    = 0xF7;         // out     out    out     out        input              out             out          out                 (0:input   1:output)
    P0OD    = 0x00;        // -      pp     pp      pp            PP                PP               pp            pp                    (0:push-pull   1:open-drain)
    P0PU    = 0x00;         // -      on      on       on           off                off             off           off                  (0:disable      1:enable)               
    P0        = 0x01;	        // -      -       -         -              0              0                0               0
    P03DB   = 0x00;       // 0       0      0       0               0              0                 0              0
    P0FSR   = 0x00;       // 0      0      0       0              0              0                   0            0

                                    //-        V3_CUR_ADC      V2_CUR_ADC   V1_CUR_ADC  V4_CUR_ADC     --             --          --
    P1IO    = 0x87;         // out         input                       input                input               input         out          out            out
    P1OD    = 0x00;        // pp        PP           PP           pp             PP             PP             PP                 pp
    P1PU    = 0x80;        // on        off          off           off            off             off            off                 off
    P1	  = 0x00;        // 00000000
    P12DB   = 0x00;       // 00000000
    P1FSRH  = 0x2A;      // 00         10                        10                       10
     P1FSRL  = 0x40;	 //                                                                                       010              00            00                 0 
    
                                    //-    -  	S3   		 S2        S1       -         -      -
    P2IO    = 0x7F;         //-   out      out          	out         out    out     out     out
    P2OD    = 0x00;         // -   PP      PP              PP             PP      PP      pp     pp
    P2PU    = 0x00;         // -    on     off              off             off     on      on     on
    P2	  = 0x00;		    // -      -      1      1      -      -      -      -
    P2FSR   = 0x00;	   //             00000000

                                     //led4_G    --    led1_G    led2_G    led1_R    led2_R    led3_R   led4_R
    P3IO    = 0xFF;         // out         out      out            out         out           out        out         out
    P3OD    = 0x00;        // PP         PP      PP         PP       PP         PP       PP       PP
    P3PU    = 0x00;         // off       off      off        off       off       off       off       off
    P3	   = 0xFF;	//00000000
    P3FSR   = 0x00;		  // 0        0         0          0         0         0          0        0		
  #endif
}

void main()
{
	u8 cur_detect_pos=1;
	OSCCR = 0x20;		// internal OSC 8MHz
	BITCR = 0x2E;		// BIT 16.384ms

	delay_ms(16);

	LVRCR  = 0x02;                      // builtin reset 2.0V set, LVRCR.0=0 enable !!!

	InitConfig();

	WDTDR = 0xFF;
	ClrWdt();	

	//timer0   as system tick
	T0DR = 38;
	T0CR = 0x8D;

	//ADC
	ADCCRH = 0x07;
	ADCCRL  = 0x90;

	//interrupt
	IE = 0x20;
	IE1 = 0x00;
	IE2 = 0x02;    //enable timer0 overflow 
	IE3 = 0x00;
	EIPOL0L = 0x00;
	EIFLAG0 = 0;
	EIFLAG1 = 0;
	IIFLAG = 0;

	IE |= (1<<7);    //global interrupt


	LED1_G_ON();delay_ms(500);
	LED1_G_OFF();

	#ifdef IO_DEBUG
	led_test();
	#endif


	if(GET_BATTERY_STATUS())   // AA battery status
	{
		gTestMode = TEST_AA_BATTERY;
	}
	else
	{
		gTestMode = TEST_AAA_BATTERY;
	}

	
	testLoop();

	while(1)
	{
		ClrWdt();
		NOP();
	}
	
}


void T0_Int_Handler(void) interrupt 13
{
	gSysTick++;
}
