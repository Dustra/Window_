/*******************************************************************************/
/**
\file       APP.h
\brief      state machine for window lifter
\author     Erick Salinas
\version    1.0
\date       04/04/2014
*/
/*******************************************************************************/

#ifndef _APP_H        /*prevent duplicated includes*/
#define _APP_H

/*-- Includes ----------------------------------------------------------------*/

/** Core modules */
/** Variable types and common definitions */

#include "typedefs.h"

/*-- Variables ---------------------------------------------------------------*/

/*-- Types Definitions -------------------------------------------------------*/


/*-- Defines -----------------------------------------------------------------*/

#define		state_initial 		0
#define		state_up_aut		1
#define 	state_down_aut		2
#define		state_up_manual		3
#define		state_down_manual	4	
#define 	state_up_inter		5
#define 	state_down_inter	6
#define		state_antipinch		7

#define 	ON_LED_UP		LED_ON(RA14)
#define 	OFF_LED_UP		LED_OFF(RA14)

#define 	ON_LED_DOWN		LED_ON(RA15)
#define 	OFF_LED_DOWN	LED_OFF(RA15)

#define 	ANTIPINCH		INPUT(PUSH3)
#define		UP_PUSH			INPUT(PUSH1)
#define		DOWN_PUSH		INPUT(PUSH2)

#define 	LEVEL_MAX		10
#define		LEVEL_MIN		0
#define 	LEVEL1			1
#define 	LEVEL2			2
#define 	LEVEL3			3
#define 	LEVEL4			4
#define 	LEVEL5			5
#define 	LEVEL6			6
#define 	LEVEL7			7
#define 	LEVEL8			8
#define 	LEVEL9			9

#define		t_10ms			10
#define		t_500ms			500
#define		t_400ms			400
#define		t_5000ms		5000










/*-- Function Prototypes -----------------------------------------------------*/


extern void Func_500us(void);


#endif /* _DUMMY_H */

/*******************************************************************************/
