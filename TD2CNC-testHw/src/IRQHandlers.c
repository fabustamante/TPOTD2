/*
 * IRQHandlers.c
 *
 *  Created on: 20 de nov. de 2017
 *      Author: Fernando
 */
#include <TD2CNC.h>

//void GPIO_IRQ_HANDLER (void)
//{
//	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
//
////	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, BUTTONS_BUTTON1_GPIO_PORT_NUM, 1 << 2);
////	 Chip_GPIOINT_GetStatusFalling(LPC_GPIOINT, BUTTONS_BUTTON1_GPIO_PORT_NUM);
//	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, XMAX_GPIO_PORT_NUM, 1 << XMAX_GPIO_BIT_NUM);
//	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, XMIN_GPIO_PORT_NUM, 1 << XMIN_GPIO_BIT_NUM);
//	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, YMAX_GPIO_PORT_NUM, 1 << YMAX_GPIO_BIT_NUM);
//	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, YMIN_GPIO_PORT_NUM, 1 << YMIN_GPIO_BIT_NUM);
//	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, ZMAX_GPIO_PORT_NUM, 1 << ZMAX_GPIO_BIT_NUM);
//	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, ZMIN_GPIO_PORT_NUM, 1 << ZMIN_GPIO_BIT_NUM);
////	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, AMAX_GPIO_PORT_NUM, 1 << AMAX_GPIO_BIT_NUM);
////	Chip_GPIOINT_ClearIntStatus(LPC_GPIOINT, AMIN_GPIO_PORT_NUM, 1 << AMIN_GPIO_BIT_NUM);
//	xSemaphoreGiveFromISR(xSemPulsador, &xHigherPriorityTaskWoken);
//
//	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
//}

void UART0_IRQHandler(void)
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	uint8_t char_rx=0;
	/* If this interrupt is for a receive... */
	if(Chip_UART_ReadLineStatus(LPC_UART0) & UART_LSR_RDR)
	{
		char_rx=Board_UARTGetChar(LPC_UART0);
		xQueueSendFromISR( xQueue_Rx, &char_rx, &xHigherPriorityTaskWoken  );
	}
	else if (Chip_UART_ReadLineStatus(LPC_UART0) & UART_LSR_THRE)
	{
		/* "give" the serial_tx_wait_sem semaphore to notfiy processes
		 * that the buffer has a spot free for the next byte.
		 */
		xSemaphoreGiveFromISR(serial_tx_wait_sem, &xHigherPriorityTaskWoken);

		/* Diables the transmit interrupt. */
		Chip_UART_IntDisable(LPC_UART0, UART_IER_THREINT);

	}
	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}
void TIMER0_IRQHandler(void)
{
	///Creation of flag to give the semaphore from ISR
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	///Verification of interrupt match source (expecting only Match 0)
	if (Chip_TIMER_MatchPending(LPC_TIMER0, 1))
	{
		xSemaphoreGiveFromISR(xsemTimer0, &xHigherPriorityTaskWoken);
		portEND_SWITCHING_ISR (xHigherPriorityTaskWoken);
		Chip_TIMER_ClearMatch(LPC_TIMER0, 1);
	}
}
void TIMER1_IRQHandler(void)
{
	///Creation of flag to give the semaphore from ISR
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	///Verification of interrupt match source (expecting only Match 0)
	if (Chip_TIMER_MatchPending(LPC_TIMER1, 1))
	{
		xSemaphoreGiveFromISR(xsemTimer1, &xHigherPriorityTaskWoken);
		portEND_SWITCHING_ISR (xHigherPriorityTaskWoken);
		Chip_TIMER_ClearMatch(LPC_TIMER1, 1);
	}
}
void TIMER2_IRQHandler(void)
{
	///Creation of flag to give the semaphore from ISR
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	///Verification of interrupt match source (expecting only Match 0)
	if (Chip_TIMER_MatchPending(LPC_TIMER2, 1))
	{
		xSemaphoreGiveFromISR(xsemTimer2, &xHigherPriorityTaskWoken);
		portEND_SWITCHING_ISR (xHigherPriorityTaskWoken);
		Chip_TIMER_ClearMatch(LPC_TIMER2, 1);
	}
}
