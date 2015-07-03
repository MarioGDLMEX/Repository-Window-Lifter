/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %dummy.c%
* Instance:         RPL_1
* %version:         1 %
* %created_by:      Mario Alberto Rivera González %
* %date_created:    Monday July  29 14:38:03 2015 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : Implements a module that controls windows movement.     */
/* I have in this file a few function that help me implements Close, Open.    */
/* A states machine that helpe to move trough Automatic, Manual and Anti-Pinch*/
/* mode.                                                                      */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 03/07/2015  |                               | Mario Rivera     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */


/** Own headers */
#include "dummy.h"

/* GPIO routines prototypes */
#include "GPIO.h"


#include "typedefs.h"



/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

void dummy_500us(void);
void dummy_endless_loop(void);

void Task_1ms( void );
void Task_10ms( void );
void Show_Leds( void );
void machine( void );
void Set_Direction( void );
void Set_Mode( void );

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */

TASKSTRUCT function_table_def[]={
	{ 0, 2,     &Task_1ms   },
	{ 0, 5,     &Task_10ms  },
};


/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */
TASKSTRUCT *rps_TaskPtr;
T_UBYTE rub_counter_Button_OK;
T_UBYTE rub_option_M_A;
T_UBYTE rub_Option_Direction;
T_UBYTE rub_start;

/* WORD RAM variables */
T_UWORD ruw_Leds_ON_OFF;
T_UWORD ruw_counter_M_A;
T_UWORD ruw_counter_Pinch;

/* LONG and STRUCTURE RAM variables */

enum re_states
{
	MANUAL,
	AUTOMATIC,
	OPEN,
	CLOSED,
	STANDBY,
	PINCH
};

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */



/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Task_1ms	
 *  Description          : This function controls all flows program.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    YES
 **************************************************************/
 
 void Task_1ms(void)
{
	ruw_Leds_ON_OFF++;
	if( rub_option_M_A == PINCH ){}
	else if( rub_counter_Button_OK )
	{
		if( PUSH_PRESSED(OPEN_PUSH) )
		{
			ruw_counter_M_A++;
			rub_Option_Direction = OPEN;
			LED_ON(LED_OPEN);
			LED_OFF(LED_CLOSED);
		}
		else if( PUSH_PRESSED(CLOSED_PUSH) )
		{
			ruw_counter_M_A++;
			rub_Option_Direction = CLOSED;
			LED_ON(LED_CLOSED);
			LED_OFF(LED_OPEN);
		}
		else if( PUSH_PRESSED(PINCH_PUSH) )
		{
			if( rub_Option_Direction == CLOSED )
			{
				ruw_counter_M_A = reset_counter;
				ruw_counter_Pinch = reset_counter;
				rub_option_M_A = PINCH;
				rub_Option_Direction = OPEN;
				LED_OFF(LED_CLOSED);
				LED_ON(LED_OPEN);
			}
		}
		else
			ruw_counter_M_A = reset_counter;
	}
	Set_Mode();
	if( ruw_Leds_ON_OFF >= _400Mili )
	{
		machine();
		ruw_Leds_ON_OFF = reset_counter;
	}	
}


/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Task_10ms	
 *  Description          : This function is call when I need to know
 						   if was pressed a correct button.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  YES
 **************************************************************/

void Task_10ms(void)
{
	if( PUSH_PRESSED(OPEN_PUSH) || 
		PUSH_PRESSED(CLOSED_PUSH) || 
		PUSH_PRESSED(PINCH_PUSH) )
		rub_counter_Button_OK = 1;
	else
		rub_counter_Button_OK = 0;
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Show_Leds	
 *  Description          : This function turn on or off a specific led.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation : YES
 **************************************************************/
void Show_Leds(void)
{
	if( rub_Option_Direction == OPEN )
			LED_OFF( rub_start );
	else if( rub_Option_Direction == CLOSED )
			LED_ON( rub_start );
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : machine	
 *  Description          : This function controls the mode that 
 						   the windows will move, Automatic, Manual
 						   Anti-Pinch or do not do anything(StandBy).
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  YES
 **************************************************************/
void machine( void )
{
	switch( rub_option_M_A )
	{
		case MANUAL:
			Show_Leds();
			if( rub_counter_Button_OK )
				Set_Direction();
			else
				rub_option_M_A = STANDBY;
		break;
		case AUTOMATIC:
			Show_Leds();
			Set_Direction();
		break;
		case STANDBY:
		break;
		case PINCH:
			Show_Leds();
			Set_Direction();
			if( ruw_counter_Pinch >= _5000Mili )
				rub_option_M_A = STANDBY;	
		break;
		default:
		break;
	}
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Set_Direction	
 *  Description          : Indicate wich led has to off or on 
 						   and sets direction.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void Set_Direction( void )
{

	if( rub_Option_Direction == OPEN )
	{
		if( rub_start < LED10 )
				rub_start++;
			else if( rub_start == LED10 )
			{
				rub_start = LED10;
				LED_OFF(LED_CLOSED);
				LED_OFF(LED_OPEN);
			}
	}
	else if( rub_Option_Direction == CLOSED )
	{
		if( rub_start > LED1)
				rub_start--;
			else if( rub_start == LED1 )
			{	
				rub_start = LED1;
				LED_OFF(LED_CLOSED);
				LED_OFF(LED_OPEN);
			}
	}
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Set_Mode	
 *  Description          : In this function I set a mode (Automatic, Anti-Pinch, Automatic or Manual
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation : YES
 **************************************************************/
void Set_Mode( void )
{
	if( rub_option_M_A == AUTOMATIC){}
	if( rub_option_M_A == PINCH ){
		ruw_counter_Pinch++;
	}
	else
	{
		if( ruw_counter_M_A >= _10Mili && ruw_counter_M_A < _500Mili )
			rub_option_M_A = AUTOMATIC;
		else if( ruw_counter_M_A >= _500Mili )
		{
			rub_option_M_A = MANUAL;	
			LED_OFF(LED_CLOSED);
			LED_OFF(LED_OPEN);
		}
	}
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : dummy_500us	
 *  Description          : It is call when a inturrptions occurs
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  YES
 **************************************************************/
void dummy_500us(void)
{
	int i=0;
	for(i = 0; i < 2; i++)
	{
		(rps_TaskPtr+i)->ruw_Counter++;
		if( (rps_TaskPtr+i)->ruw_Counter == (rps_TaskPtr+i)->ruw_TopCount   )
		{
			(rps_TaskPtr+i)->cpfu_PerFunct();
			(rps_TaskPtr+i)->ruw_Counter = reset_counter;
		}
	}
}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : dummy_endless_loop	
 *  Description          : This functions is called by the main.c
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  YES
 **************************************************************/
void dummy_endless_loop(void)
{
	rps_TaskPtr = function_table_def;
	rub_start = LED1;
	rub_option_M_A = STANDBY;
	rub_counter_Button_OK = reset_counter;
	ruw_Leds_ON_OFF = reset_counter;
	ruw_counter_M_A = reset_counter;
	LED_OFF(LED_CLOSED);
	LED_OFF(LED_OPEN);
	for(;;)
	{
	}
}


/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
