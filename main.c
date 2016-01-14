#include "MC96F8316.h"
#include "test.h"
#include "intrins.h"

u8 gTestMode = TEST_AA_BATTERY;
u32 gSysTick = 0;

void dumpHandler()
{
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

#ifdef LED_DEBUG
void led_test()
{
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
}
#endif

void testLoop()
{
	u8 test_pos_now = TEST_CHANNEL_1;

	do{
			switch(test_pos_now)
			{
				case TEST_CHANNEL_1:
						CLOSE_CHANNEL_1();break;
				case TEST_CHANNEL_2:
						CLOSE_CHANNEL_1();break;
				case TEST_CHANNEL_3:
						CLOSE_CHANNEL_1();break;
				case TEST_CHANNEL_4:
						CLOSE_CHANNEL_1();break;
				default:
						dumpHandler();break;
			}

			if(getAverage(test_pos_now) > ADC_START_BATTERY_DETECT)
			{
				
			}






			switch(test_pos_now)
			{
				case TEST_CHANNEL_1:
						OPEN_CHANNEL_1();break;
				case TEST_CHANNEL_2:
						OPEN_CHANNEL_1();break;
				case TEST_CHANNEL_3:
						OPEN_CHANNEL_1();break;
				case TEST_CHANNEL_4:
						OPEN_CHANNEL_1();break;
				default:
						dumpHandler();break;
			}
			delay_ms(20);
			test_pos_now++;
		}while(test_pos_now<= TEST_CHANNEL_4);
}

void InitConfig()
{
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

	#ifdef LED_DEBUG
	led_test();
	#endif


	if(GET_BATTERY_STATUS())   // AA battery status
	{
		gTestMode = TEST_AA_BATTERY;
	}
	else
		gTestMode = TEST_AAA_BATTERY;

	
	testLoop();
	
}


void T0_Int_Handler(void) interrupt 13
{
	gSysTick++;
}