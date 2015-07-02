/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %template.c%
* Instance:         RPL_1
* %version:         2 %
* %created_by:      uid02495 %
* %date_created:    Fri Jan  9 14:38:03 2004 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source template according to  */
/* the new software platform                                                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | DD/MM/YYYY  |                               | Mr. Template     */
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


/* LONG and STRUCTURE RAM variables */

T_ULONG rul_Leds_ON_OFF;
T_ULONG rul_counter_M_A;
T_ULONG rul_counter_Pinch;

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
 *  Description          :
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/
 
 void Task_1ms(void)
{
	rul_Leds_ON_OFF++;
	if( rub_option_M_A == PINCH )
	{}
	else if( rub_counter_Button_OK )
	{
		if( PUSH_PRESSED(OPEN_PUSH) )
		{
			rul_counter_M_A++;
			rub_Option_Direction = OPEN;
			LED_ON(LED_OPEN);
			LED_OFF(LED_CLOSED);
		}
		else if( PUSH_PRESSED(CLOSED_PUSH) )
		{
			rul_counter_M_A++;
			rub_Option_Direction = CLOSED;
			LED_ON(LED_CLOSED);
			LED_OFF(LED_OPEN);
		}
		else if( PUSH_PRESSED(PINCH_PUSH) )
		{
			if( rub_Option_Direction == CLOSED )
			{
				rul_counter_M_A = reset_counter;
				rul_counter_Pinch = reset_counter;
				rub_option_M_A = PINCH;
				rub_Option_Direction = OPEN;
				LED_OFF(LED_CLOSED);
				LED_ON(LED_OPEN);
			}
		}
		else
			rul_counter_M_A = reset_counter;
	}
	Set_Mode();
	machine();	
}


/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Task_10ms	
 *  Description          :
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
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
 *  Description          :
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
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
 *  Description          :
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void machine( void )
{
	if( rul_Leds_ON_OFF >= _400Mili )
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
			case PINCH://check
				Show_Leds();
				Set_Direction();
				if( rul_counter_Pinch >= _5000Mili )
					rub_option_M_A = STANDBY;	
			break;
			default:
			break;
		}
		rul_Leds_ON_OFF = reset_counter;
	}

}

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : Set_Direction	
 *  Description          :
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
 *  Description          :
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void Set_Mode( void )
{
	if( rub_option_M_A == AUTOMATIC){}
	if( rub_option_M_A == PINCH ){
		rul_counter_Pinch++;
	}
	else
	{
		if( rul_counter_M_A >= _10Mili && rul_counter_M_A < _500Mili )
			rub_option_M_A = AUTOMATIC;
		else if( rul_counter_M_A >= _500Mili )
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
 *  Description          :
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
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
 *  Description          :
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void dummy_endless_loop(void)
{
	rps_TaskPtr = function_table_def;
	rub_start = LED1;
	rub_option_M_A = STANDBY;
	rub_counter_Button_OK = reset_counter;
	rul_Leds_ON_OFF = reset_counter;
	rul_counter_M_A = reset_counter;
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
