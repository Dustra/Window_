/*******************************************************************************/
/**
\file       dummy.c
\brief      Dummy Functions
\author     Erick Salinas
\version    1.0
\date       04/04/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Variable types and common definitions */
#include "typedefs.h"

/** Own headers */
#include "dummy.h"

/* GPIO routines prototypes */ 
#include "GPIO.h"

/** Used modules */

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

int8_t level=LEVEL_MAX;
int8_t state=state_initial;
int32_t count_gen=0;

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

void state_machine_1ms(void);
void func_500us(void);

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
/*****************************************************************************************************/

/*function for the 500us interruption*/
/*It will activate the func_1ms and detects the antipinch*/

void func_500us(void)
{
	static int8_t count_cycle1ms=0;
	static int8_t count_antipinch=0;

	count_cycle1ms++;
	
	if(count_cycle1ms>1)
	{
		count_cycle1ms=0;
		state_machine_1ms();
		
	}
	
	
	if(ANTIPINCH==ACTIVATED && state==state_up_aut)
	{
		count_antipinch++;
		if(count_antipinch>20)
		{
			count_antipinch=0;
			state=state_antipinch;
				
		}
		
	}
	
}

/*translate the level to the outputs leds*/

void out_leds(void)
{
	
	if(level<LEVEL_MIN)
	{
		level=LEVEL_MIN;
	}
	
	if(level>LEVEL_MAX)
	{
		level=LEVEL_MAX;
	}
	
	LED_OFF(RA0);
	LED_OFF(RA1);
	LED_OFF(RA2);
	LED_OFF(RA3);
	LED_OFF(RA4);
	LED_OFF(RA5);
	LED_OFF(RA6);
	LED_OFF(RA7);
	LED_OFF(RA8);
	LED_OFF(RA9);
	
	
	if(level>LEVEL_MIN)
	{
		LED_ON(RA0);
	}

	if(level>LEVEL1)
	{
		LED_ON(RA1);
	}
	if(level>LEVEL2)
	{
		LED_ON(RA2);
	}
	if(level>LEVEL3)
	{
		LED_ON(RA3);
	}
	if(level>LEVEL4)
	{
		LED_ON(RA4);
	}
	if(level>LEVEL5)
	{
		LED_ON(RA5);
	}
	if(level>LEVEL6)
	{
		LED_ON(RA6);
	}
	if(level>LEVEL7)
	{
		LED_ON(RA7);
	}
	if(level>LEVEL8)
	{
		LED_ON(RA8);
	}
	if(level>LEVEL9)
	{
		LED_ON(RA9);
	}
	
	
}

/*state machine for the different stages of the system*/

void state_machine_1ms(void)
{


	
	switch(state)
	{

		case state_initial:   
		
		    OFF_LED_DOWN;
		    OFF_LED_UP;                           
			out_leds();
			
			if(UP_PUSH==ACTIVATED)
			{
				count_gen++;
				if(count_gen>LEVEL_MAX)
				{
					state=state_up_inter;
				}
			}
			
			if(DOWN_PUSH==ACTIVATED)
			{
				count_gen++;
				if(count_gen>LEVEL_MAX)
				{
					state=state_down_inter;
				}
			}
		
		
			break;
		
		case state_up_inter: 
		
			if(UP_PUSH==ACTIVATED)
			{
				count_gen++;
			}
			
			if(UP_PUSH==DEACTIVATED && count_gen<t_500ms)
			{
				state=state_up_aut;
				level++;
				count_gen=0;
			}
			
			if(UP_PUSH==ACTIVATED && count_gen>t_500ms)
			{
				state=state_up_manual;
			}
		
		
		
			break;
			
		case state_down_inter:
		
			if(DOWN_PUSH==ACTIVATED)
			{
				count_gen++;
			}
			
			if(DOWN_PUSH==DEACTIVATED && count_gen<t_500ms)
			{
				state=state_down_aut;
				level--;
				count_gen=0;
			}
			
			if(DOWN_PUSH==ACTIVATED && count_gen>t_500ms)
			{
				state=state_down_manual;
			}
		
		
		
			break;
		
		
		
		case state_up_aut:
		
				if(level>LEVEL_MAX-1)
				{
				
				count_gen=0;
				state=state_initial;
				
				}
				else
				{
					
				ON_LED_UP;
				count_gen++;				
				out_leds();
				
				if(count_gen>t_400ms)
				{
				
				level++;
				count_gen=0;
				
				}
							
				}
	
		
			break;
		
		
		
		case state_down_aut:

				if(level<LEVEL_MIN+1)
				{
				
				count_gen=0;
				state=state_initial;
				
				}
				else
				{
					
				ON_LED_DOWN;
				count_gen++;				
				out_leds();
				
				if(count_gen>t_400ms)
				{
				
				level--;
				count_gen=0;
				
				}
							
				}
			

			break;
		
		case state_up_manual:
			
			if(level<LEVEL_MAX)
			{
				
			
				ON_LED_UP;
				level++;
				out_leds();
				delay_ms(t_400ms);
				count_gen=0;
			}
				
			OFF_LED_UP;
			if(UP_PUSH==DEACTIVATED)
			{
				state=state_initial;
					
			}
			
			
			

			break;
		
		
		case state_down_manual:
		
			if(level>LEVEL_MIN)
			{
			
			ON_LED_DOWN;
			level--;
			out_leds();
			delay_ms(t_400ms);
			count_gen=0;
			
			}
			
		    OFF_LED_DOWN;		
			if(DOWN_PUSH==DEACTIVATED)
			{
				state=state_initial;	
			}

			
			
			break;
		
		case state_antipinch:
				
				OFF_LED_UP;
				if(level<LEVEL_MIN+1)
				{
				count_gen=0;
				delay_ms(t_5000ms);
				state=state_initial;
	
				}
				else
				{
					
								
				ON_LED_DOWN;
				level--;
				out_leds();
				if(level>0)
				{
					delay_ms(t_400ms);	
				}
				
				}
			

			break;
			
		
		
		default:
			break;

	}
	
	
	
	
	
	
	
	
	
	
	
	
}









