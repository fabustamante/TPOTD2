/*
 * Display.c
 *
 *  Created on: 20 de nov. de 2017
 *      Author: Fernando
 */

#include <TD2CNC.h>

void vDisplayTask(void* pvParameters)
{
	char posx[30], posy[30] ,posz[30];
	char displayCommands = UPDATE_POS;
	uint8_t i;
	float pos_mm[N_AXIS];

	portTickType xWakeup;
	xWakeup = xTaskGetTickCount();

	Board_Dato_LCD(LCD_CLEARDISPLAY ,LCD_CONTROL);
	Board_Display_lcd ("Posiciones: ", RENGLON0, 0);
	Board_Display_lcd ("Spindle: ", RENGLON1, 10);

	for(;;)
	{
//		xSemaphoreTake( mutex_Display , portMAX_DELAY);
		xQueueReceive(xQueue_Display, &displayCommands,0);
//		xSemaphoreGive(mutex_Display);

		if(displayCommands!=NO_KEY)
		{
			switch(displayCommands)
			{
			case SPINDLE_ENABLE:
				if(sys.state==S_IDLE)
				sendSerialString("T");
				Board_Display_lcd(" ON",RENGLON2,12);
				displayCommands=NO_KEY;
				break;
			case SPINDLE_DISABLE:
				if(sys.state==S_IDLE)
				sendSerialString("S");
				Board_Display_lcd("OFF",RENGLON2,12);
				displayCommands=NO_KEY;
				break;
			case UPDATE_POS:
				if(	   sys.position[X_AXIS]%DEF_STEP_MIN_PITCH==0
					|| sys.position[Y_AXIS]%DEF_STEP_MIN_PITCH==0
					|| sys.position[Z_AXIS]%DEF_STEP_MIN_PITCH==0)
				{
					for ( i=0; i< N_AXIS; i++)
					{
						pos_mm[i] = sys.position[i] / (float) settings.steps_per_mm[i];
					}
					if( pos_mm[X_AXIS]<0)
						sprintf(posx, "X: %3.2f", (float) pos_mm[X_AXIS] );
					else
						sprintf(posx, "X:  %3.2f", (float) pos_mm[X_AXIS] );
					if( pos_mm[Y_AXIS]<0)
						sprintf(posy, "Y: %3.2f", (float) pos_mm[Y_AXIS] );
					else
						sprintf(posy, "Y:  %3.2f", (float) pos_mm[Y_AXIS] );
					if( pos_mm[Z_AXIS]<0)
						sprintf(posz, "Z: %3.2f", (float) pos_mm[Z_AXIS] );
					else
						sprintf(posz, "Z:  %3.2f", (float) pos_mm[Z_AXIS] );
					sendSerialString(posx);
					sendSerialString("%");
					sendSerialString(posy);
					sendSerialString("%");
					sendSerialString(posz);
					sendSerialString("%");
					Board_Display_lcd(posx,RENGLON1,0);
					Board_Display_lcd(posy,RENGLON2,0);
					Board_Display_lcd(posz,RENGLON3,0);
					if (!sys.S_Auto.flag_end_block[X_AXIS] &&
						!sys.S_Auto.flag_end_block[Y_AXIS] &&
						!sys.S_Auto.flag_end_block[Z_AXIS] )
							displayCommands=NO_KEY;
				}
				break;
			}
		}
		vTaskDelayUntil(&xWakeup,20/portTICK_RATE_MS);
	}
}

void sendSerialString(char *str)
{
	while (*str != '\0')
		send_byte(*str++);
}

void send_byte(char ch)
{
	/* Wait until the RS232 port can receive another byte (this semaphore
	 * is "given" by the RS232 port interrupt when the buffer has room for
	 * another byte.
	 */
	while (!xSemaphoreTake(serial_tx_wait_sem, portMAX_DELAY));

	/* Send the byte and enable the transmit interrupt (it is disabled by
	 * the interrupt).
	 */
	Chip_UART_SendByte(LPC_UART0, (uint8_t) ch);
	Chip_UART_IntEnable(LPC_UART0, UART_IER_THREINT);
}
