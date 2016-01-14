#include "test.h"
//u8 tempStr1[] = "temp1:";
//u8 tempStr2[] = "temp2:";

u16 getAdcValue(u8 channel)
{
	
	u16 temp = 0xffff;
	
	short value; 
	char  rAdc_Offset;


	// read adc offset
#pragma asm
	mov A, #0			;
	mov DPTR, #3FFFh	;
	movc A, @A+DPTR		;
#pragma endasm

	rAdc_Offset = ACC;		//; offset value


	ADCCRH = 0x07;
	ADCCRL = 0x80;           	         // VDD reference
	
	ADCCRL |= channel;

	ADCCRL |= (1<<6);
	
	while((ADCCRL&0x10) != 0x10)
	{
		temp--;
		ClrWdt();
		if(temp == 0)
			break;
	}


	value = (ADCDR & 0xfff);	

	// adjust adc value
	if(rAdc_Offset >= -3 && rAdc_Offset <= 7)
	{
	//	rAdc_Offset += 2;
		if(value > rAdc_Offset)
		{
			value -= rAdc_Offset;
		}
		else
		{
			value = 0;
		}
	}	

	ADCCRL = 0x80;
	
	return value;
}

u16 getAverage(u8 test_pos)
{
	u8 i;
	u16 temp,max,min,ret;


	switch(test_pos)
	{
		case TEST_CHANNEL_1:
				test_pos = CHANNEL_CUR_1;break;
		case TEST_CHANNEL_2:
				test_pos = CHANNEL_CUR_2;break;
		case TEST_CHANNEL_3:
				test_pos = CHANNEL_CUR_3;break;
		case TEST_CHANNEL_4:
				test_pos = CHANNEL_CUR_4;break;
		default:
				dumpHandler();break;
	}

	temp = getAdcValue(test_pos);
	ret= temp;
	max =temp;
	min = temp;
	for(i=0;i<9;i++)
	{
		//delay_us(100);
		 temp = getAdcValue(test_pos);
	 	if(temp > max)
	 	{
			max = temp;
	 	}

		 if(temp < min)
		{
			min = temp;
	 	}
	 	ret += temp;
	}
	

	return (ret - max - min)>>3;
}

