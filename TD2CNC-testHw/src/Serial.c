/*
 * Serial.c
 *
 *  Created on: 20 de nov. de 2017
 *      Author: Fernando
 */
#include <TD2CNC.h>
struct AMessage xMessage;
/* TAREA UART */
void vSerialTask(void* pvParameters)
{
	/* Declare the variable that will hold the values received from the queue. */
	char rxChar,command,serialState=SERIAL_HEADER_ev;
	char defFlag = false;
	char line[LINE_BUFFER_SIZE],Trama=Ser_AUTO_HEADER;

	struct AMessage * pxMessage;
	uint8_t i=0;

	//const portTickType xTicksToWait = 1 / portTICK_RATE_MS;

	/* This task is also defined within an infinite loop. */
	for( ;; )
	{
		/* The first parameter is the queue from which data is to be received.  The
		queue is created before the scheduler is started, and therefore before this
		task runs for the first time.
			The second parameter is the buffer into which the received data will be
		placed.  In this case the buffer is simply the address of a variable that
		has the required size to hold the received data.
			the last parameter is the block time – the maximum amount of time that the
		task should remain in the Blocked state to wait for data to be available should
		the queue already be empty. */
		if (serialState==SERIAL_AUTO_ev && Trama==Ser_AUTO_FOOTER)
			xQueueReceive( xQueue_Rx, &rxChar, 100 / portTICK_RATE_MS );
		else
			xQueueReceive( xQueue_Rx, &rxChar, portMAX_DELAY );

		/* Data was successfully received from the queue, print out the received
		value. */
		if (rxChar == Ser_ABORT_AUTO  )
		{
			serialState=SERIAL_HEADER_ev;
		}
		switch(serialState)
		{
			case SERIAL_HEADER_ev:
				switch (rxChar)
				{
					case Ser_AUTO:
						settings_restore_global_settings();
						init_system_var();
						memset(&line,0,sizeof(line));
						serialState=SERIAL_AUTO_ev;
						break;
					case Ser_MANUAL:
						serialState=SERIAL_MANUAL_ev;
						break;
					case Ser_SET_SETTINGS:
						serialState=SERIAL_SET_SETTINGS_ev;
						break;
					case Ser_SET_HOME:
						serialState=SERIAL_SET_HOME_ev;
						break;
					case Ser_GO_HOME:
						serialState=SERIAL_GO_HOME_ev;
						break;
					case Ser_ABORT_AUTO:
						sys.alarm=ABORT_AUTO;
						Trama=Ser_AUTO_HEADER;
						i = 0;
						memset(&line,0,sizeof(line));
						serialState=SERIAL_HEADER_ev;
					default:
						serialState=SERIAL_HEADER_ev;
				}
				defFlag = false;
				break;
			case SERIAL_AUTO_ev:
				switch(Trama)
				{
					case Ser_AUTO_HEADER:
						if ( rxChar == Ser_LINE_AUTO)
							Trama=Ser_AUTO_FRAME;
						break;
					case Ser_AUTO_FRAME:
						if ( rxChar != '\n' && rxChar != '\r')
						{
							if ( i >= (LINE_BUFFER_SIZE-1))
							{
								sys.alarm = OVERFLOW_LINE;
								i = 0;
							}
							else
							{
								if ( rxChar != '$')
								{
									line[i] = rxChar;
									i++;
								}
							}
						}
						else
						{
							line[i]='\0';
							strcpy(xMessage.ucMsg,line);
							pxMessage = & xMessage;
//								xSemaphoreGive(xsemGCode);
//								xSemaphoreTake(xsemSerialAuto, 0);
//								xSemaphoreTake(xsemSerialAuto, portMAX_DELAY);
							xQueueSendToBack( xQueue_GCodeLine, &pxMessage, portMAX_DELAY );

							sendSerialString("$");

							i = 0;
							memset(&line,0,sizeof(line));
							if ( sys.S_Auto.flag_gcode_finished ==FALSE)
							{
								Trama = Ser_AUTO_HEADER;
							}
							else
							{
								Trama = Ser_AUTO_FOOTER;
							}
						}
						break;
					case Ser_AUTO_FOOTER:
						if ( (sys.S_Auto.flag_gcode_finished ==TRUE || rxChar == Ser_FIN_AUTO)
							&& sys.S_Auto.flag_all_blocks_finished==TRUE)
						{
							serialState=SERIAL_HEADER_ev;
							Trama = Ser_AUTO_HEADER;
						}
						break;
				}
				serialState=SERIAL_FOOTER_ev;
				break;
			case SERIAL_MANUAL_ev:
				switch (rxChar)
				{
					case Ser_XR:
						command = key_XR;
						break;
					case Ser_XL:
						command = key_XL;
						break;
					case Ser_YR:
						command = key_YR;
						break;
					case Ser_YL:
						command = key_YL;
						break;
					case Ser_ZD:
						command = key_ZD;
						break;
					case Ser_ZU:
						command = key_ZU;
						break;
					case Ser_SPINDLE_ON:
						command = key_Spindle_ONOFF;
						break;
					default:
						defFlag=true;
				}
				if(!defFlag)
					serialState=SERIAL_FOOTER_ev;
				else
					serialState=SERIAL_HEADER_ev;
				break;
			case SERIAL_SET_SETTINGS_ev:
				///To do
				serialState=SERIAL_FOOTER_ev;
				break;
			case SERIAL_GO_HOME_ev:
				switch (rxChar)
				{
					case Ser_GO_HOME:
						command = key_GO_HOME;
						break;

					case Ser_GO_VIEW:
						command = key_GO_VIEW;
						break;
					default:
						defFlag=true;
				}
				if(!defFlag)
					serialState=SERIAL_FOOTER_ev;
				else
					serialState=SERIAL_HEADER_ev;
				break;
			case SERIAL_SET_HOME_ev:
				switch (rxChar)
				{
					case Ser_SET_ZERO_ALL:
						command = key_SET_ZERO_ALL;
						break;
					case Ser_SET_ZERO_X:
						command = key_SET_ZERO_X;
						break;
					case Ser_SET_ZERO_Y:
						command = key_SET_ZERO_Y;
						break;
					case Ser_SET_ZERO_Z:
						command = key_SET_ZERO_Z;
						break;
					default:
						defFlag=true;
				}
				if(!defFlag)
					serialState=SERIAL_FOOTER_ev;
				else
					serialState=SERIAL_HEADER_ev;
				break;
			case SERIAL_ERROR_ev:
				//To do
				break;
			case SERIAL_FOOTER_ev:
				if(rxChar==Ser_FOOTER)
				{
					xQueueSendToBack( xQueue_KBCommands, &command, portMAX_DELAY );
				}
				serialState=SERIAL_HEADER_ev;
				break;
			default:
				serialState=SERIAL_HEADER_ev;
		}
	}
}

