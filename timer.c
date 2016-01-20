#include "test.h"
#include "intrins.h"
extern u32 gSysTick;
extern u32 nowSysTick;
void delay_ms(u16 nus)
{
    unsigned int i , j;
    for(i=0;i<nus;i++)
   {
   	ClrWdt();
	for(j=0;j<1000;j++);
    }
}
/*
void delay_us(u16 nus)
{
	u16 i;
	for(i=0;i<nus;i++);
	ClrWdt();
}
*/
/*
void getSysTick()
{
	EA = 0;
	NOP();
	nowSysTick = gSysTick;
	NOP();
	EA=1;
}
*/

u32 getDiffTickFromNow(u32 ttick)
{
	getSysTick();

	if(ttick <= nowSysTick)
		return (nowSysTick - ttick); //getDiffTick(ttick, ticknow);
	else
		return (0xFFFFFFFF-ttick+nowSysTick);
}