/*
 * MatrixKeypad.c
 *
 *  Created on: 20 de nov. de 2017
 *      Author: Fernando
 */
#include <TD2CNC.h>

/*------------------------------------------------------------------*/
void vDebounceMKTask(void *parametros)
{
 	int debounce = 0;
 	char key=NO_KEY;

 	for(;;)
 	{
 		vTaskDelay(100/portTICK_RATE_MS);
 		debounce<<=1;
 		key= Board_MatrixKeyboard_4x4();
 		if(key!=NO_KEY)
 		{
 			debounce|=1;
 		}
 		debounce&=0xF;
 		if(debounce == 0x03)
 		{
			xQueueSendToBack( xQueue_KBCommands, &key, portMAX_DELAY );
 		}
 	}
}
/*------------------------------------------------------------------*/
//-----------------------------------------------------------------------------
//void vDebounce(void *parametros)
//{
//	uint8_t debounce = 0,x=0,i=0;
//	struct data_Display mensaje;
//	xSemaphoreTake( xSemPulsador, 0 );
//	for(;;)
//	{
//		vTaskDelay(20/portTICK_RATE_MS);
//		debounce<<=1;
//		x = Endstops_GetStatus();
//		if(x!=NO_ENDSTOP_PRESSED)
//		{
//					debounce|=1;
//		}
//		debounce&=0xF;
//		if(debounce == 0x03)
//		{
////			xSemaphoreTake( xSemPulsador, portMAX_DELAY );
////			xQueueSendToBack( xQueue_EndStop, &x, portMAX_DELAY );
//
//			mensaje.entero=x;
//			mensaje.context=2;
//			mensaje.col=1;
//			xQueueSendToBack( xQueue_Display, &mensaje, portMAX_DELAY );
//			i++;
//
//		}
//	}
//}




