/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %dummy.h%
* Instance:         RPL_1
* %version:         1 %
* %created_by:      Mario Alberto Rivera González %
* %date_created:    Fri jun 30 13:41:01 2015 %
*=============================================================================*/
/* DESCRIPTION : Header file template                                         */
/*============================================================================*/
/* FUNCTION COMMENT : contains only symbols which are exported to internal    */
/* platform modules. This will not be delivered with the library              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 30/06/2015  | SAR/SIF/SCN_xxx               | Mario Rivera     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

#ifndef _DUMMY_H                               /* To avoid double inclusion */
#define _DUMMY_H

/* Includes */
#include "typedefs.h"
/* -------- */


/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */
#define _400Mili 			400
#define _5000Mili 			50000
#define _500Mili  			500
#define _10Mili 			10
#define reset_counter		0

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
typedef struct{
	T_UWORD  ruw_Counter;
	T_UWORD  ruw_TopCount;
	tCallbackFunction   cpfu_PerFunct;
}TASKSTRUCT;


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */
void dummy_500us(void);
void dummy_endless_loop(void);

void Task_1ms( void );
void Task_10ms( void );
void Show_Leds( void );
void machine( void );
void Set_Direction( void );
void Set_Mode( void );

/* Functions macros */


/* Exported defines */


#endif /* _DUMMY_H */