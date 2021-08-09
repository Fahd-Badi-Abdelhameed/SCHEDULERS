/*****************************************************************************/
/* Title        	: 	RTOS Driver									         */
/* File Name    	: 	RTOS_interface.h   		                             */
/* Author       	: 	Fahd Badi                                            */
/* Version      	: 	1.0.0                                                */
/* Origin Date  	: 	10/10/2020                                           */
/* Notes        	: 	None                                                 */
/*****************************************************************************/

/******************************************************************************
* Description 	: Guard to protect this File from include more 			      *
*                 than one time.                               	 	 		  *
******************************************************************************/
#ifndef RTOS_INTERFACE_H
#define RTOS_INTERFACE_H


/******************************************************************************
***************************** Function Prototypes *****************************
******************************************************************************/

/******************************************************************************
* Description 	: This function is used to enable GIE and                     *
*                 timer0 initialization.                                      *
* Parameters  	: none.                                                       *
* Return type 	: void.                                                  	  *
*******************************************************************************
* Pre_condition : none.                                                       *
******************************************************************************/
void RTOS_voidStart(void);

/******************************************************************************
* Description 	: This function is used to create task.				          *
* Parameters  	: uint8 Copy_u8Priority, uint16 Copy_u16Periodicity,          *
*                 *Copy_pvTaskFunc, uint16 Copy_u16FirstDelay.                *
* Return type 	: uint8 --> Error State.                                   	  *
*******************************************************************************
* Pre_condition : This function must be used after RTOS Start function.       *
******************************************************************************/
uint8 RTOS_u8CreateTask(uint8 Copy_u8Priority, uint16 Copy_u16Periodicity, 
						void(*Copy_pvTaskFunc)(void), uint16 Copy_u16FirstDelay);
						
/******************************************************************************
* Description 	: This function is used to suspend its specific task.         *
* Parameters  	: uint8 Copy_u8Priority.                                      *
* Return type 	: void.                                                  	  *
*******************************************************************************
* Pre_condition : This function must be used after RTOS Create Task Function. *
******************************************************************************/
void RTOS_voidSuspendTask(uint8 Copy_u8Priority);

/******************************************************************************
* Description 	: This function is used to resume its specific task.	      *
* Parameters  	: uint8 Copy_u8Priority.                                      *
* Return type 	: void.                                                  	  *
*******************************************************************************
* Pre_condition : This function must be used after RTOS Suspend Task Function.*
******************************************************************************/
void RTOS_voidResumeTask(uint8 Copy_u8Priority);

/******************************************************************************
* Description 	: This function is used to delete its specific task.	      *
* Parameters  	: uint8 Copy_u8Priority.                                      *
* Return type 	: void.                                                  	  *
*******************************************************************************
* Pre_condition : This function must be used after RTOS Create Task Function. *
******************************************************************************/
void RTOS_voidDeleteTask(uint8 Copy_u8Priority);

#endif 
/*** !comment : End of gaurd [PROS_INTERFACE_H] ******************************/