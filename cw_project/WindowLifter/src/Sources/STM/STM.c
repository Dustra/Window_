#include "MCU_derivative.h"
#include "STM.h"


void Timer_Config()
{
	STM.CR.R=0x00003F01;	/*Choose prescaler of 64 to get 1us*/
	STM.CH[0].CCR.R=1;		/*Initialize channel 1*/
	
}