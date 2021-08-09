/*****************************************************************************/
/* Title        	: 	RTOS Driver									         */
/* File Name    	: 	RTOS_program.c   		                             */
/* Author       	: 	Fahd Badi                                            */
/* Version      	: 	1.0.0                                                */
/* Origin Date  	: 	10/10/2020                                           */
/* Notes        	: 	None                                                 */
/*****************************************************************************/

/******************************************************************************
******************************* STD LIB DIRECTIVES ****************************
******************************************************************************/
#include "STD_TYPES.h"

/******************************************************************************
**************************** MCAL Component DIRECTIVES ************************
******************************************************************************/
#include "GIE_interface.h"
#include "TIMER0_interface.h"

/******************************************************************************
****************************** Component DIRECTIVES ***************************
******************************************************************************/
#include "RTOS_private.h"
#include "RTOS_interface.h"
#include "RTOS_config.h"


/******************************************************************************
************************** Module Variable Definitions ************************
******************************************************************************/
Task_t SystemTasks[TASK_NUM] = {{NULL}};

/******************************************************************************
**************************** Function Implementation **************************
******************************************************************************/
	
void RTOS_voidStart(void){
	
	TIMER0_voidCompareMatchSetCallBack(voidScheduler);
	GIE_voidEnable();
	TIMER0_voidInit(TIMER0_CTC_MODE, TIMER0_SCALER_64);
	TIMER0_voidSetOutputCompareValue(125);
	TIMER0_voidCompareMatchInterruptEnable();
	
}


uint8 RTOS_u8CreateTask(uint8 Copy_u8Priority, uint16 Copy_u16Periodicity, void(*Copy_pvTaskFunc)(void), uint16 Copy_u16FirstDelay){
	
	uint8 Local_u8ErrorState = OK;

	/* Check if the required priority is empty or used before for another task */
	if(SystemTasks[Copy_u8Priority].TaskFunc == NULL){

		SystemTasks[Copy_u8Priority].Periodicity = Copy_u16Periodicity;		/* Assign the Periodicity parameter */
		SystemTasks[Copy_u8Priority].TaskFunc 	 = Copy_pvTaskFunc;	    	/* Assign the Task Function parameter */
		SystemTasks[Copy_u8Priority].State       = TASK_RESUMED;        	/* Initialize the task state */
		SystemTasks[Copy_u8Priority].FirstDelay  = Copy_u16FirstDelay;  	/* Assign the first delay parameter */

	}
	else{

		/* Priority is reserved before, don't create the task */
		Local_u8ErrorState = NOK;

	}

	return Local_u8ErrorState;
}	


void RTOS_voidSuspendTask(uint8 Copy_u8Priority){

	SystemTasks[Copy_u8Priority].State = TASK_SUSPENDED;

}


void RTOS_voidResumeTask(uint8 Copy_u8Priority){

	SystemTasks[Copy_u8Priority].State = TASK_RESUMED;

}


void RTOS_voidDeleteTask(uint8 Copy_u8Priority){

	SystemTasks[Copy_u8Priority].TaskFunc = NULL;

}


static void voidScheduler(void){
	
	uint8 Local_u8TaskCounter;

	/* Loop on all tasks to check their Periodicity */
	for(Local_u8TaskCounter = 0; Local_u8TaskCounter < TASK_NUM; Local_u8TaskCounter++){
		
		/* Check if the task suspended or not */
		if(SystemTasks[Local_u8TaskCounter].State == TASK_RESUMED){

			/* Invoke the task function */
			if(SystemTasks[Local_u8TaskCounter].TaskFunc != NULL){

				if(SystemTasks[Local_u8TaskCounter].FirstDelay == 0){
				
					SystemTasks[Local_u8TaskCounter].TaskFunc();

					/* Assign the first delay parameter to the Periodicity minus 1 */
					SystemTasks[Local_u8TaskCounter].FirstDelay = (SystemTasks[Local_u8TaskCounter].Periodicity-1);

				}
				else{
				
					/* Decrement the first delay */
					SystemTasks[Local_u8TaskCounter].FirstDelay--;
				}
			}
		}
		else{

			/* Task is Suspended, do nothing */
		}
	}
}
	
	
/******************************************************************************
********************************* END OF PROGRAM ******************************
******************************************************************************/