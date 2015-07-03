/*******************************************************************************/
/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:        APP.c
* Instance:         RPL_1
* %version:         2 %
* %created_by:      uid02495 %
* %date_created:   	Wed July  1 14:38:03 2004 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the statemachine working by PIT 	  */
/* Interruptions	                                                 		  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 01/07/2015  |                               | Erick Salinas    */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
#include "typedefs.h"
#include "APP.h"		/*Services*/
#include "GPIO.h"
#include "STM.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */

/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */

T_UBYTE rub_level=LEVEL_MAX;
T_UBYTE rub_state=state_initial;

/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */

T_ULONG rul_count_gen=0;

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */

void State_Machine_1ms(void);
void Func_500us(void);
void Out_Leds(void);


/* Exported functions prototypes */
/* ----------------------------- */



/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : inline_func	2
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : delay_ms
 *  Description          : Delay design to stop the system while waiting for desgined time
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :    [No]
 **************************************************************/

void delay_ms(vuint32_t time_ms)
{
	TIMER_REGISTER=0;
	while(TIMER_REGISTER<time_ms*1000)
	{
		
	}
	
}

/**************************************************************
 *  Name                 : Func_500us
 *  Description          : Function call by PIT, executing every 500us, calling State_Machine_1ms()
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :   [No]
 **************************************************************/
 
 
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
	
	
	if(ANTIPINCH==ACTIVATED && (rub_state==state_up_aut || rub_state==state_up_manual))
	{
		lub_count_antipinch++;
		if(lub_count_antipinch>t_10ms_antipinch)
		{
			lub_count_antipinch=0;
			rub_state=state_antipinch;
				
		}
		
	}
	
}

/**************************************************************
 *  Name                 : Out_Leds
 *  Description          :	Translate the value in variable rub_level to digital outputs
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [No]
 **************************************************************/
 
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
 
/**************************************************************
 *  Name                 : State_machine
 *  Description          :	contains the the main state machine controlling the system
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :	void
 *  Critical/explanation :    [yes]*read DSD for internal detail explanation
 **************************************************************/
 
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
				rub_level++;
				rul_count_gen=0;
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
				rub_level--;
				rul_count_gen=0;
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
				
				if(DOWN_PUSH==ACTIVATED)
				{
					rul_count_gen=0;
					rub_state= state_initial;
					delay_ms(500);
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
				
				if(UP_PUSH==ACTIVATED)
				{
					rul_count_gen=0;
					rub_state= state_initial;
					delay_ms(500);
				}
							
				}
			

			break;
		
		case state_up_manual:
			
			ON_LED_UP;
			rul_count_gen++;
			Out_Leds();
			
			if(rub_level<LEVEL_MAX && rul_count_gen>t_400ms)
			{
				
				rub_level++;
				rul_count_gen=0;
			}
				
			OFF_LED_UP;
			
			if(UP_PUSH==DEACTIVATED)
			{
				rub_state=state_initial;
				OFF_LED_UP;
			}
			
			
			

			break;
		
		
		case state_down_manual:
		
			ON_LED_DOWN;
			rul_count_gen++;
			Out_Leds();
			
			if(rub_level>LEVEL_MIN && rul_count_gen>t_400ms)
			{
				
				rub_level--;
				rul_count_gen=0;
			}
				
			OFF_LED_DOWN;
			
			if(DOWN_PUSH==DEACTIVATED)
			{
				rub_state=state_initial;
				OFF_LED_DOWN;
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
 


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


	
	
	
}









