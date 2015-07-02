
#include "MCU_derivative.h"


/** GPIO funtion prototypes  */
#include    "GPIO.h"
#include    "PIT.h"
#include    "APP.h"


void disableWatchdog(void) 
{
  SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}


void timer_config()
{
	STM.CR.R=0x00003F01;
	STM.CH[0].CCR.R=1;
	
}

int8_t cuenta=4;

//////////////////////////////////////////////////////////////////////////////////////////////////////////

extern void delay_ms(vuint32_t time_ms)
{
	STM.CNT.R=0;
	while(STM.CNT.R<time_ms*1000)
	{
		
	}
	
}



/*~~~~~~~ Main Code ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main(void) 

{

	initModesAndClock();
	disableWatchdog();
	vfnGPIO_LED_Init();	
	INTC_InitINTCInterrupts();
	timer_config();
	EXCEP_InitExceptionHandlers();
	PIT_device_init();
    PIT_channel_configure(PIT_CHANNEL_0 , Func_500us);	
    PIT_channel_start(PIT_CHANNEL_0);
    enableIrq();
    
    while(1)
    {
    	
       	
    	
    	
    }
    
}