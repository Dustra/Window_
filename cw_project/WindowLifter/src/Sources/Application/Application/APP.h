/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        APP.h
* Instance:         RPL_1
* %version:         1 %
* %created_by:      uid02495 %
* %date_created:    Wed July 6 13:41:01 2003 %
*=============================================================================*/
/* DESCRIPTION : Header file template                                         */
/*============================================================================*/
/* FUNCTION COMMENT : Contains header for APP.C function              		  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 02/07/2015  | SAR/SIF/SCN_xxx               | Erick Salinas    */
/* Integration under Continuus CM                                             */
/*============================================================================*/


#ifndef _APP_H        /*prevent duplicated includes*/
#define _APP_H

/* Includes */
/* -------- */

#include "typedefs.h"


/*==================================================*/ 
/* Declaration of exported constants                */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTES */


/* WORDS */


/* LONGS and STRUCTURES */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */

extern void Func_500us(void);


/* Functions macros */

/* Exported defines */

/*
#define		state_initial 		0
#define		state_up_aut		1
#define 	state_down_aut		2
#define		state_up_manual		3
#define		state_down_manual	4	
#define 	state_up_inter		5
#define 	state_down_inter	6
#define		state_antipinch		7
*/

enum N_STATES
{
	
		state_initial=0,		
		state_up_aut,	
	 	state_down_aut,		
		state_up_manual,		
		state_down_manual,		
 		state_up_inter,		
 		state_down_inter,	
		state_antipinch			
		
};

#define 	ON_LED_UP		LED_ON(RA14)
#define 	OFF_LED_UP		LED_OFF(RA14)

#define 	ON_LED_DOWN		LED_ON(RA15)
#define 	OFF_LED_DOWN	LED_OFF(RA15)

#define 	ANTIPINCH		INPUT(PUSH3)
#define		UP_PUSH			INPUT(PUSH1)
#define		DOWN_PUSH		INPUT(PUSH2)

/*
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
*/

enum N_LEVELS
{
	LEVEL_MIN=0,
	LEVEL1,
	LEVEL2,
	LEVEL3,
	LEVEL4,
	LEVEL5,
	LEVEL6,
	LEVEL7,
	LEVEL8,
	LEVEL9,
	LEVEL_MAX 
	
};



#define		t_10ms			10
#define		t_500ms			500
#define		t_400ms			400
#define		t_5000ms		5000
#define 	t_10ms_antipinch	10




#endif 

