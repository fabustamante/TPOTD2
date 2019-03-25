/*
===============================================================================
 Name        : Ex12_FreeRtos.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
/* FreeRTOS.org includes. */
#include <TD2CNC.h>

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
system_t sys;

/*Defino los semáforos y el buffer*/

xSemaphoreHandle serial_tx_wait_sem;
xSemaphoreHandle xsemTimer0, xsemTimer1, xsemTimer2;
//xSemaphoreHandle xsemSerialAuto;
//xSemaphoreHandle xsemGCode;
//xSemaphoreHandle xsemEndProgram;
//xSemaphoreHandle mutex_Pos;

/**
 *  Declare a variable of type xQueueHandle.  This is used to store the queue
 *  that is accessed by all three tasks.
 */
xQueueHandle xQueue_Rx;
xQueueHandle xQueue_Display;
xQueueHandle xQueue_KBCommands;
xQueueHandle xQueue_GCodeLine;
//xQueueHandle xQueue_GCodeToken;
xQueueHandle xQueue_GCodeBlock;
xQueueHandle xQueue_PlannerBlock;
xQueueHandle xQueue_StepperBlock;

xTaskHandle vSystemInit_Handler = NULL;
xTaskHandle vCncController_Handler = NULL;

xTaskHandle vSerial_Handler = NULL;
xTaskHandle vGCodeDispatch_Handler = NULL;
//xTaskHandle vGCodeParser_Handler = NULL;
xTaskHandle vRobot_Handler = NULL;
xTaskHandle vPlanner_Handler = NULL;
xTaskHandle vStepperMove_Handler = NULL;

/*****************************************************************************
 * Private functions
 ****************************************************************************/
//-----------------------------------------------------------------------------

int main( void )
{
	uint8_t i=0;
	prvSetupHardware();

	vSemaphoreCreateBinary( serial_tx_wait_sem );
//	mutex_Pos = xSemaphoreCreateMutex();

	xQueue_Rx = xQueueCreate( 32, sizeof( char ) );
	xQueue_KBCommands = xQueueCreate( 1, sizeof( char ) );
	if( xQueue_KBCommands != NULL && xQueue_Rx!= NULL)
	{
		if(xTaskCreate(vSystemInit,"vSystemInit",configMINIMAL_STACK_SIZE,
					NULL,tskIDLE_PRIORITY+2,&vSystemInit_Handler ) == pdPASS)
			i++;
		if(xTaskCreate(vSerialTask,"vSerialTask",configMINIMAL_STACK_SIZE,
					NULL,tskIDLE_PRIORITY+1,&vSerial_Handler) == pdPASS)
			i++;
		if(xTaskCreate(vDebounceMKTask,"vDebounceMKTask",configMINIMAL_STACK_SIZE,
					NULL,tskIDLE_PRIORITY+1,NULL ) == pdPASS)
			i++;
	}

	vTaskStartScheduler();

	return 0;
}

void vSystemInit(void *pvParameters)
{
	char key,command = UPDATE_POS;
	uint8_t i=0;

	settings_restore_global_settings();
	init_system_var();

	welcomeMsg();

	for(;;)
	{
		xQueueReceive(xQueue_KBCommands, &key,portMAX_DELAY);
		if(key==key_Enter)
		{
			vSemaphoreCreateBinary( xsemTimer0 );
			vSemaphoreCreateBinary( xsemTimer1 );
			vSemaphoreCreateBinary( xsemTimer2 );

			xQueue_Display = xQueueCreate( 1, sizeof( char ) );
			xQueue_GCodeBlock = xQueueCreate( 8, sizeof( parser_block_t) );
			xQueue_GCodeLine = xQueueCreate( 8, sizeof( struct AMessage *) );
			xQueue_PlannerBlock = xQueueCreate( 8, sizeof( plan_block_t ) );
			xQueue_StepperBlock = xQueueCreate( 8, sizeof(st_block_t));

			if( 	xQueue_Display 		!= NULL
				&& 	xQueue_GCodeBlock	!= NULL
				&& 	xQueue_GCodeLine	!= NULL
				&& 	xQueue_PlannerBlock	!= NULL
				&& 	xQueue_StepperBlock	!= NULL)
			{
				if(xTaskCreate(vCncControllerTask,"vCncControllerTask",configMINIMAL_STACK_SIZE,
							NULL,tskIDLE_PRIORITY+2,&vCncController_Handler) == pdPASS)
					i++;
				if(xTaskCreate(vDisplayTask, "vDisplayLCD",configMINIMAL_STACK_SIZE,
							NULL, tskIDLE_PRIORITY+1, NULL) == pdPASS)
					i++;
				if(xTaskCreate(vXMoveTask,"vXMoveTask",configMINIMAL_STACK_SIZE,
							NULL,tskIDLE_PRIORITY+1,NULL) == pdPASS)
					i++;
				if(xTaskCreate(vYMoveTask,"vYMoveTask",configMINIMAL_STACK_SIZE,
							NULL,tskIDLE_PRIORITY+1,NULL) == pdPASS)
					i++;
				if(xTaskCreate(vZMoveTask,"vZMoveTask",configMINIMAL_STACK_SIZE,
							NULL,tskIDLE_PRIORITY+1,NULL ) == pdPASS)
					i++;
				if(xTaskCreate(vStepperMoveTask,"vStepperMoveTask",configMINIMAL_STACK_SIZE,
							NULL,tskIDLE_PRIORITY+1,&vStepperMove_Handler ) == pdPASS)
					i++;
				if(xTaskCreate(vGCodeDispatchTask,"vGCodeDispatchTask",configMINIMAL_STACK_SIZE,
							NULL,tskIDLE_PRIORITY+1,&vGCodeDispatch_Handler ) == pdPASS)
					i++;
				if(xTaskCreate(vRobotTask,"vRobotTask",configMINIMAL_STACK_SIZE,
							NULL,tskIDLE_PRIORITY+1,&vRobot_Handler ) == pdPASS)
					i++;
				if(xTaskCreate(vPlannerTask,"vPlannerTask",configMINIMAL_STACK_SIZE,
							NULL,tskIDLE_PRIORITY+1,&vPlanner_Handler ) == pdPASS)
					i++;
			}
			xQueueSendToBack( xQueue_Display, &command, portMAX_DELAY );
			vTaskSuspend(NULL);
		}
	}
}

void welcomeMsg(void)
{
	char msg1[]="TD2 TPO CNC r00",msg2[]="Hit Enter",msg3[]="Fernando Bustamante";
	portTickType xWakeup;
	xWakeup = xTaskGetTickCount();
	Board_Display_lcd( msg1 , RENGLON0 , 2 );
	Board_Display_lcd( msg3 , RENGLON3 , 0 );
	vTaskDelayUntil(&xWakeup,2000/portTICK_RATE_MS);
	Board_Dato_LCD(LCD_CLEARDISPLAY ,LCD_CONTROL);
	Board_Display_lcd( msg2 , RENGLON1 , 2 );
}

/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing. */
}
