/*******************************************************************************/
/**
\file       APP.c
\brief      State_machine for window lifter
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
#include "APP.h"

/* GPIO routines prototypes */ 
#include "GPIO.h"

/** Used modules */

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

T_UBYTE rub_level=LEVEL_MAX;
T_UBYTE rub_state=state_initial;
T_ULONG rul_count_gen=0;

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

void State_Machine_1ms(void);
void Func_500us(void);
void Out_Leds(void);

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

void Func_500us(void)
{
	static T_UBYTE lub_count_cycle1ms=0;
	static T_UBYTE lub_count_antipinch=0;

	lub_count_cycle1ms++;
	
	if(lub_count_cycle1ms>1)
	{
		lub_count_cycle1ms=0;
		State_Machine_1ms();
		
	}
	
	
	if(ANTIPINCH==ACTIVATED && rub_state==state_up_aut)
	{
		lub_count_antipinch++;
		if(lub_count_antipinch>20)
		{
			lub_count_antipinch=0;
			rub_state=state_antipinch;
				
		}
		
	}
	
}

/*translate the level to the outputs leds*/

void Out_Leds(void)
{
	
	if(rub_level<LEVEL_MIN)
	{
		rub_level=LEVEL_MIN;
	}
	
	if(rub_level>LEVEL_MAX)
	{
		rub_level=LEVEL_MAX;
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
	
	
	if(rub_level>LEVEL_MIN)
	{
		LED_ON(RA0);
	}

	if(rub_level>LEVEL1)
	{
		LED_ON(RA1);
	}
	if(rub_level>LEVEL2)
	{
		LED_ON(RA2);
	}
	if(rub_level>LEVEL3)
	{
		LED_ON(RA3);
	}
	if(rub_level>LEVEL4)
	{
		LED_ON(RA4);
	}
	if(rub_level>LEVEL5)
	{
		LED_ON(RA5);
	}
	if(rub_level>LEVEL6)
	{
		LED_ON(RA6);
	}
	if(rub_level>LEVEL7)
	{
		LED_ON(RA7);
	}
	if(rub_level>LEVEL8)
	{
		LED_ON(RA8);
	}
	if(rub_level>LEVEL9)
	{
		LED_ON(RA9);
	}
	
	
}

/*state machine for the different stages of the system*/

void State_Machine_1ms(void)
{


	
	switch(rub_state)
	{

		case state_initial:   
		
		    OFF_LED_DOWN;
		    OFF_LED_UP;                           
			Out_Leds();
			
			if(UP_PUSH==ACTIVATED)
			{
				rul_count_gen++;
				if(rul_count_gen>t_10ms)
				{
					rub_state=state_up_inter;
				}
			}
			
			if(DOWN_PUSH==ACTIVATED)
			{
				rul_count_gen++;
				if(rul_count_gen>t_10ms)
				{
					rub_state=state_down_inter;
				}
			}
		
		
			break;
		
		case state_up_inter: 
		
			if(UP_PUSH==ACTIVATED)
			{
				rul_count_gen++;
			}
			
			if(UP_PUSH==DEACTIVATED && rul_count_gen<t_500ms)
			{
				rub_state=state_up_aut;
				rub_level++;
				rul_count_gen=0;
			}
			
			if(UP_PUSH==ACTIVATED && rul_count_gen>t_500ms)
			{
				rub_state=state_up_manual;
			}
		
		
		
			break;
			
		case state_down_inter:
		
			if(DOWN_PUSH==ACTIVATED)
			{
				rul_count_gen++;
			}
			
			if(DOWN_PUSH==DEACTIVATED && rul_count_gen<t_500ms)
			{
				rub_state=state_down_aut;
				rub_level--;
				rul_count_gen=0;
			}
			
			if(DOWN_PUSH==ACTIVATED && rul_count_gen>t_500ms)
			{
				rub_state=state_down_manual;
			}
		
		
		
			break;
		
		
		
		case state_up_aut:
		
				if(rub_level>LEVEL_MAX-1)
				{
				
				rul_count_gen=0;
				rub_state=state_initial;
				
				}
				else
				{
					
				ON_LED_UP;
				rul_count_gen++;				
				Out_Leds();
				
				if(rul_count_gen>t_400ms)
				{
				
				rub_level++;
				rul_count_gen=0;
				
				}
							
				}
	
		
			break;
		
		
		
		case state_down_aut:

				if(rub_level<LEVEL_MIN+1)
				{
				
				rul_count_gen=0;
				rub_state=state_initial;
				
				}
				else
				{
					
				ON_LED_DOWN;
				rul_count_gen++;				
				Out_Leds();
				
				if(rul_count_gen>t_400ms)
				{
				
				rub_level--;
				rul_count_gen=0;
				
				}
							
				}
			

			break;
		
		case state_up_manual:
			
			if(rub_level<LEVEL_MAX)
			{
				
			
				ON_LED_UP;
				rub_level++;
				Out_Leds();
				delay_ms(t_400ms);
				rul_count_gen=0;
			}
				
			OFF_LED_UP;
			if(UP_PUSH==DEACTIVATED)
			{
				rub_state=state_initial;
					
			}
			
			
			

			break;
		
		
		case state_down_manual:
		
			if(rub_level>LEVEL_MIN)
			{
			
			ON_LED_DOWN;
			rub_level--;
			Out_Leds();
			delay_ms(t_400ms);
			rul_count_gen=0;
			
			}
			
		    OFF_LED_DOWN;		
			if(DOWN_PUSH==DEACTIVATED)
			{
				rub_state=state_initial;	
			}

			
			
			break;
		
		case state_antipinch:
				
				OFF_LED_UP;
				if(rub_level<LEVEL_MIN+1)
				{
				rul_count_gen=0;
				delay_ms(t_5000ms);
				rub_state=state_initial;
	
				}
				else
				{
					
								
				ON_LED_DOWN;
				rub_level--;
				Out_Leds();
				if(rub_level>0)
				{
					delay_ms(t_400ms);	
				}
				
				}
			

			break;
			
		
		
		default:
			break;

	}
	
	
	
	
	
	
	
	
	
	
	
	
}









