/*
 * @brief BaseBoar1769_R02 Board File
 *
 * @note
 * Ing Ruben Lozano
 * Ing Fabio Marano
 *
 */

#include "board.h"
#include <string.h>

#include "retarget.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/


/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/* System oscillator rate and RTC oscillator rate */
const uint32_t OscRateIn = 12000000;
const uint32_t RTCOscRateIn = 32768;

/*****************************************************************************
 * Private functions
 ****************************************************************************/

void EINTInit( void )
{
	/* Configure GPIO interrupt pin as input */
	Board_Endstops_Init();

	/* Configure the GPIO interrupt */
	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, XMAX_GPIO_PORT_NUM, 1 << XMAX_GPIO_BIT_NUM);
	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, XMIN_GPIO_PORT_NUM, 1 << XMIN_GPIO_BIT_NUM);
	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, YMAX_GPIO_PORT_NUM, 1 << YMAX_GPIO_BIT_NUM);
	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, YMIN_GPIO_PORT_NUM, 1 << YMIN_GPIO_BIT_NUM);
	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, ZMAX_GPIO_PORT_NUM, 1 << ZMAX_GPIO_BIT_NUM);
	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, ZMIN_GPIO_PORT_NUM, 1 << ZMIN_GPIO_BIT_NUM);
//	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, AMAX_GPIO_PORT_NUM, 1 << AMAX_GPIO_BIT_NUM);
//	Chip_GPIOINT_SetIntFalling(LPC_GPIOINT, AMIN_GPIO_PORT_NUM, 1 << AMIN_GPIO_BIT_NUM);
	/* Enable interrupt in the NVIC */
	NVIC_ClearPendingIRQ(GPIO_INTERRUPT_NVIC_NAME);
	NVIC_EnableIRQ(GPIO_INTERRUPT_NVIC_NAME);
}
/* Initializes board LED(s) */
void Board_LED_Init(void)
{
	/* Pins are configured as GPIO pin during SystemInit */
	/* Set the pins as output */
	Chip_GPIO_WriteDirBit(LPC_GPIO, LED0_GPIO_PORT_NUM, LED0_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, LED1_GPIO_PORT_NUM, LED1_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, LED2_GPIO_PORT_NUM, LED2_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, LED3_GPIO_PORT_NUM, LED3_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, LED4_GPIO_PORT_NUM, LED4_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, LED5_GPIO_PORT_NUM, LED5_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, LED6_GPIO_PORT_NUM, LED6_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, LED7_GPIO_PORT_NUM, LED7_GPIO_BIT_NUM, true);
}
///Turn off all LEDs
void Board_TurnOff_All_LEDs(void)
{
	Board_LED_Set(LED0_GPIO_PORT_NUM,LED0_GPIO_BIT_NUM, true);
	Board_LED_Set(LED1_GPIO_PORT_NUM,LED1_GPIO_BIT_NUM, true);
	Board_LED_Set(LED2_GPIO_PORT_NUM,LED2_GPIO_BIT_NUM, true);
	Board_LED_Set(LED3_GPIO_PORT_NUM,LED3_GPIO_BIT_NUM, true);
	Board_LED_Set(LED4_GPIO_PORT_NUM,LED4_GPIO_BIT_NUM, true);
	Board_LED_Set(LED5_GPIO_PORT_NUM,LED5_GPIO_BIT_NUM, true);
	Board_LED_Set(LED6_GPIO_PORT_NUM,LED6_GPIO_BIT_NUM, true);
	Board_LED_Set(LED7_GPIO_PORT_NUM,LED7_GPIO_BIT_NUM, true);
}
void Board_Steppers_Init(void)
{
	Chip_GPIO_WriteDirBit(LPC_GPIO, XEN_GPIO_PORT_NUM, XEN_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, YEN_GPIO_PORT_NUM, YEN_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, ZEN_GPIO_PORT_NUM, ZEN_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, XDIR_GPIO_PORT_NUM, XDIR_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, YDIR_GPIO_PORT_NUM, YDIR_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, ZDIR_GPIO_PORT_NUM, ZDIR_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, XSTEP_GPIO_PORT_NUM, XSTEP_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, YSTEP_GPIO_PORT_NUM, YSTEP_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, ZSTEP_GPIO_PORT_NUM, ZSTEP_GPIO_BIT_NUM, true);
}
void Board_Steppers_OFF(void)
{
	Board_LED_Set(XEN_GPIO_PORT_NUM,XEN_GPIO_BIT_NUM, true);
	Board_LED_Set(YEN_GPIO_PORT_NUM,YEN_GPIO_BIT_NUM, true);
	Board_LED_Set(ZEN_GPIO_PORT_NUM,ZEN_GPIO_BIT_NUM, true);

	Board_LED_Set(XSTEP_GPIO_PORT_NUM,XSTEP_GPIO_BIT_NUM, false);
	Board_LED_Set(YSTEP_GPIO_PORT_NUM,YSTEP_GPIO_BIT_NUM, false);
	Board_LED_Set(ZSTEP_GPIO_PORT_NUM,ZSTEP_GPIO_BIT_NUM, false);
}
void Board_Spindle_Init(void)
{
	Chip_GPIO_WriteDirBit(LPC_GPIO, SPINDLE_GPIO_PORT_NUM, SPINDLE_GPIO_BIT_NUM, true);
}
/*****************************************************************************
 * Public functions
 ****************************************************************************/
void Board_InitLCD ( void )
{
	unsigned int i,j;

	/* Pins are configured as GPIO pin during SystemInit */
	/* Set the pins as output */
	Chip_GPIO_WriteDirBit(LPC_GPIO, LCDD7_GPIO_PORT_NUM, LCDD7_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, LCDD6_GPIO_PORT_NUM, LCDD6_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, LCDD5_GPIO_PORT_NUM, LCDD5_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, LCDD4_GPIO_PORT_NUM, LCDD4_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, LCDEN_GPIO_PORT_NUM, LCDEN_GPIO_BIT_NUM, true);
	Chip_GPIO_WriteDirBit(LPC_GPIO, LCDRS_GPIO_PORT_NUM, LCDRS_GPIO_BIT_NUM, true);
	for( i = 0 ; i < 3 ; i++ )
	{
		LCD_E_OFF;
		for ( j = 0 ; j < 500000 ; j++ ); // 300000
		LCD_DATO(1,1,0,0);

		LCD_RS_OFF;
		LCD_E_ON;

		for( j = 0 ; j < 10000 ; j++ );//4500

		LCD_E_OFF;
	}

	LCD_E_OFF;

	for ( j = 0 ; j < 500000 ; j++ ); // 300000

	LCD_DATO(0,1,0,0);

	LCD_RS_OFF;
	LCD_E_ON;

	for( j = 0 ; j < 10000 ; j++ );//4500

	LCD_E_OFF;

	// A partir de aca pasa a 4 bits
	Board_Dato_LCD( 0x28 , LCD_CONTROL );
	Board_Dato_LCD( 0x08 , LCD_CONTROL);	// display OFF
	Board_Dato_LCD( 0x01 , LCD_CONTROL);	// clear display
	for( j = 0 ; j < 10000 ; j++ );	// delay por la instruccion clear display
	Board_Dato_LCD( 0x06 , LCD_CONTROL);	// programo el LCD para mis necesidades
	Board_Dato_LCD( 0x0C , LCD_CONTROL);	// display ON,sin cursor y blinking OFF del cursor

}
void Board_Dato_LCD ( unsigned char data , unsigned char control )
{
	int q , i = 1;
	uint16_t data_d4,data_d5,data_d6,data_d7;

	do
	{
		data_d4 = ( data >> ( 0 + i * 4 ) ) & 0x01 ;
		data_d5 = ( data >> ( 1 + i * 4 ) ) & 0x01 ;
		data_d6 = ( data >> ( 2 + i * 4 ) ) & 0x01 ;
		data_d7 = ( data >> ( 3 + i * 4 ) ) & 0x01 ;

		LCD_DATO(data_d4,data_d5,data_d6,data_d7);

		if( control == LCD_CONTROL )
			LCD_RS_OFF;
		else
			LCD_RS_ON;

		LCD_E_ON;
		for( q = 0 ; q < 400 ; q++ );
		LCD_E_OFF;
		for( q = 0 ; q < 14000 ; q++ );
	}
	while ( i-- );
}
void Board_Display_lcd( char *msg , char renglon , char posicion )
{
	unsigned char i ;

#ifdef LCD_16x2
	if( renglon )
		posicion = posicion + 0xc0 ;
	else
		posicion = posicion + 0x80 ;
#endif

#ifdef LCD_20x4
	switch( renglon )
	{
	case RENGLON0:
		posicion = posicion + 0x80 ;
		break;
	case RENGLON1:
		posicion = posicion + 0xc0 ;
		break;
	case RENGLON2:
		posicion = posicion + 0x94 ;
		break;
	case RENGLON3:
		posicion = posicion + 0xd4 ;
		break;
	}
#endif

	Board_Dato_LCD( posicion , LCD_CONTROL );
	for( i = 0 ; msg[ i ] != '\0' ; i++ )
		Board_Dato_LCD( msg[ i ] , LCD_DATA );

}
///Initialize 4x4 matrix keyboard
void Board_MatrixKeyboard_4x4_Init(void)
{
	///Here we set all Colum-related pins as General Propuose Output
	Chip_GPIO_SetPinDIR(LPC_GPIO, SW_PORT_COL1, SW_GPIO_BIT_COL1, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO, SW_PORT_COL2, SW_GPIO_BIT_COL2, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO, SW_PORT_COL3, SW_GPIO_BIT_COL3, false);
	Chip_GPIO_SetPinDIR(LPC_GPIO, SW_PORT_COL4, SW_GPIO_BIT_COL4, false);

	///Here we set all Row-related pins as General Propouse Input
	Chip_GPIO_SetPinDIR(LPC_GPIO, SW_PORT_ROW1, SW_GPIO_BIT_ROW1, true);
	Chip_GPIO_SetPinDIR(LPC_GPIO, SW_PORT_ROW2, SW_GPIO_BIT_ROW2, true);
	Chip_GPIO_SetPinDIR(LPC_GPIO, SW_PORT_ROW3, SW_GPIO_BIT_ROW3, true);
	Chip_GPIO_SetPinDIR(LPC_GPIO, SW_PORT_ROW4, SW_GPIO_BIT_ROW4, true);
}
///Barrido Matrix Keyboard
unsigned char Board_MatrixKeyboard_4x4( void )
 {
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW1, SW_GPIO_BIT_ROW1,false);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW2, SW_GPIO_BIT_ROW2,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW3, SW_GPIO_BIT_ROW3,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW4, SW_GPIO_BIT_ROW4,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW1, SW_GPIO_BIT_ROW1,false);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW2, SW_GPIO_BIT_ROW2,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW3, SW_GPIO_BIT_ROW3,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW4, SW_GPIO_BIT_ROW4,true);
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, SW_PORT_COL1, SW_GPIO_BIT_COL1))
		return MK1;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, SW_PORT_COL2, SW_GPIO_BIT_COL2))
		return MK2;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, SW_PORT_COL3, SW_GPIO_BIT_COL3))
		return MK3;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, SW_PORT_COL4, SW_GPIO_BIT_COL4))
		return MKA;

	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW1, SW_GPIO_BIT_ROW1,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW2, SW_GPIO_BIT_ROW2,false);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW3, SW_GPIO_BIT_ROW3,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW4, SW_GPIO_BIT_ROW4,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW1, SW_GPIO_BIT_ROW1,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW2, SW_GPIO_BIT_ROW2,false);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW3, SW_GPIO_BIT_ROW3,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW4, SW_GPIO_BIT_ROW4,true);
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, SW_PORT_COL1, SW_GPIO_BIT_COL1))
		return MK4;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, SW_PORT_COL2, SW_GPIO_BIT_COL2))
		return MK5;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, SW_PORT_COL3, SW_GPIO_BIT_COL3))
		return MK6;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, SW_PORT_COL4, SW_GPIO_BIT_COL4))
		return MKB;

	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW1, SW_GPIO_BIT_ROW1,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW2, SW_GPIO_BIT_ROW2,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW3, SW_GPIO_BIT_ROW3,false);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW4, SW_GPIO_BIT_ROW4,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW1, SW_GPIO_BIT_ROW1,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW2, SW_GPIO_BIT_ROW2,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW3, SW_GPIO_BIT_ROW3,false);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW4, SW_GPIO_BIT_ROW4,true);
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, SW_PORT_COL1, SW_GPIO_BIT_COL1))
		return MK7;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, SW_PORT_COL2, SW_GPIO_BIT_COL2))
		return MK8;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, SW_PORT_COL3, SW_GPIO_BIT_COL3))
		return MK9;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, SW_PORT_COL4, SW_GPIO_BIT_COL4))
		return MKC;

	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW1, SW_GPIO_BIT_ROW1,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW2, SW_GPIO_BIT_ROW2,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW3, SW_GPIO_BIT_ROW3,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW4, SW_GPIO_BIT_ROW4,false);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW1, SW_GPIO_BIT_ROW1,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW2, SW_GPIO_BIT_ROW2,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW3, SW_GPIO_BIT_ROW3,true);
	Chip_GPIO_WritePortBit(LPC_GPIO, SW_PORT_ROW4, SW_GPIO_BIT_ROW4,false);
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, SW_PORT_COL1, SW_GPIO_BIT_COL1))
		return MKast;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, SW_PORT_COL2, SW_GPIO_BIT_COL2))
		return MK0;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, SW_PORT_COL3, SW_GPIO_BIT_COL3))
		return MKnum;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, SW_PORT_COL4, SW_GPIO_BIT_COL4))
		return MKD;

 	return NO_KEY;
 }
///Initialize and set Timer
void Board_InitTimer(LPC_TIMER_T *pTMR,uint8_t channel, uint32_t matchVal)
{
	///Enable Timer 0 Clock
	Chip_TIMER_Init(pTMR);
	///Timer 0 Reset and prescale counts to 0
	Chip_TIMER_Reset(pTMR);
	///Enables a Match interrupt that fires an event
	Chip_TIMER_MatchEnableInt(pTMR, channel);
	///Sets a timer match value
	Chip_TIMER_SetMatch(pTMR, channel, matchVal);
	///Allows match counter to reset
	Chip_TIMER_ResetOnMatchEnable(pTMR, channel);
	///Start timer count
	Chip_TIMER_Enable(pTMR);
	if(pTMR==LPC_TIMER0)
	{
		///Clear Previous pending interruptions
		NVIC_ClearPendingIRQ(TIMER0_IRQn);
		///Enable NVIC IRQ handler for Timer 0
		NVIC_EnableIRQ(TIMER0_IRQn);
	}
	if(pTMR==LPC_TIMER1)
	{
		///Clear Previous pending interruptions
		NVIC_ClearPendingIRQ(TIMER1_IRQn);
		///Enable NVIC IRQ handler for Timer 0
		NVIC_EnableIRQ(TIMER1_IRQn);
	}
	if(pTMR==LPC_TIMER2)
	{
		///Clear Previous pending interruptions
		NVIC_ClearPendingIRQ(TIMER2_IRQn);
		///Enable NVIC IRQ handler for Timer 0
		NVIC_EnableIRQ(TIMER2_IRQn);
	}
}
void Board_TimerClose(LPC_TIMER_T *pTMR)
{
	Chip_TIMER_Disable(pTMR);
//	if(pTMR==LPC_TIMER0)
//		{
//			///Clear Previous pending interruptions
//			NVIC_ClearPendingIRQ(TIMER0_IRQn);
//			///Enable NVIC IRQ handler for Timer 0
//			NVIC_DisableIRQ(TIMER0_IRQn);
//		}
//		if(pTMR==LPC_TIMER1)
//		{
//			///Clear Previous pending interruptions
//			NVIC_ClearPendingIRQ(TIMER1_IRQn);
//			///Enable NVIC IRQ handler for Timer 0
//			NVIC_DisableIRQ(TIMER1_IRQn);
//		}
//		if(pTMR==LPC_TIMER2)
//		{
//			///Clear Previous pending interruptions
//			NVIC_ClearPendingIRQ(TIMER2_IRQn);
//			///Enable NVIC IRQ handler for Timer 0
//			NVIC_DisableIRQ(TIMER2_IRQn);
//		}
}

/* Initialize debug output via UART for board */
void Board_UART_Init(LPC_USART_T *pUART,uint32_t baud)
{
	if(pUART==LPC_UART3)
	{
		Chip_IOCON_PinMux(LPC_IOCON, USBBTXD_GPIO_PORT_NUM, USBBTXD_GPIO_BIT_NUM, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, USBBRXD_GPIO_PORT_NUM, USBBRXD_GPIO_BIT_NUM, IOCON_MODE_INACT, IOCON_FUNC2);
	}
	else
	{
		Chip_IOCON_PinMux(LPC_IOCON, USBBTXD_GPIO_PORT_NUM, USBBTXD_GPIO_BIT_NUM, IOCON_MODE_INACT, IOCON_FUNC1);
		Chip_IOCON_PinMux(LPC_IOCON, USBBRXD_GPIO_PORT_NUM, USBBRXD_GPIO_BIT_NUM, IOCON_MODE_INACT, IOCON_FUNC1);
	}

	// USART peripheral configuration
	Chip_UART_Init(pUART);            // 8-N-1 and FIFOs enabled
	Chip_UART_SetBaud(pUART, baud);
	Chip_UART_TXEnable(pUART);

	// Enable USART RBR and THRE interrupt
	Chip_UART_IntEnable(pUART, (UART_IER_RBRINT | UART_IER_THREINT));
	if(pUART==LPC_UART0)
	{
		// Enable USART interrupt in the NVIC
		NVIC_ClearPendingIRQ(UART0_IRQn);
		/* preemption = 1, sub-priority = 1 */
		NVIC_SetPriority(UART0_IRQn, 1);
		NVIC_EnableIRQ(UART0_IRQn);
	}
	if(pUART==LPC_UART1)
	{
		// Enable USART interrupt in the NVIC
		NVIC_ClearPendingIRQ(UART1_IRQn);
		/* preemption = 1, sub-priority = 1 */
		NVIC_SetPriority(UART1_IRQn, 1);
		NVIC_EnableIRQ(UART1_IRQn);
	}
	if(pUART==LPC_UART2)
	{
		// Enable USART interrupt in the NVIC
		NVIC_ClearPendingIRQ(UART2_IRQn);
		/* preemption = 1, sub-priority = 1 */
		NVIC_SetPriority(UART2_IRQn, 1);
		NVIC_EnableIRQ(UART2_IRQn);
	}
	if(pUART==LPC_UART3)
	{
		// Enable USART interrupt in the NVIC
		NVIC_ClearPendingIRQ(UART3_IRQn);
		/* preemption = 1, sub-priority = 1 */
		NVIC_SetPriority(UART3_IRQn, 1);
		NVIC_EnableIRQ(UART3_IRQn);
	}
}

/* Sends a character on the UART */
void Board_UARTPutChar(LPC_USART_T *pUART,char ch)
{
	while ((Chip_UART_ReadLineStatus(pUART) & UART_LSR_THRE) == 0) {}
	Chip_UART_SendByte(pUART, (uint8_t) ch);

}

/* Gets a character from the UART, returns EOF if no character is ready */
char Board_UARTGetChar(LPC_USART_T *pUART)
{
	return (char) Chip_UART_ReadByte(pUART);
	return EOF;
}

/* Outputs a string on the debug UART */
void Board_UARTPutSTR(LPC_USART_T *pUART,char *str)
{
	while (*str != '\0')
		Board_UARTPutChar(pUART,*str++);
}

/* Sets the state of a board LED to on or off */
void Board_LED_Set(uint8_t port, uint8_t bitnum, bool On)
{
	Chip_GPIO_WritePortBit(LPC_GPIO, port, bitnum, On);
}

/* Returns the current state of a board LED */
bool Board_LED_Test(uint8_t port, uint8_t bitnum)
{
	bool state = false;
	state = Chip_GPIO_ReadPortBit(LPC_GPIO, port, bitnum);
	return state;
}

void Board_LED_Toggle(uint8_t port, uint8_t bitnum)
{
	Board_LED_Set(port,bitnum, !Board_LED_Test( port, bitnum));
}

void Board_RGB_Set(uint8_t port, uint8_t bitnum, bool On)
{
	Chip_GPIO_WritePortBit(LPC_GPIO, port, bitnum, On);
}

void Board_Buttons_Init(void)
{
	Chip_GPIO_WriteDirBit(LPC_GPIO, BUTTONS_BUTTON1_GPIO_PORT_NUM, BUTTONS_BUTTON1_GPIO_BIT_NUM, false);
	Chip_GPIO_WriteDirBit(LPC_GPIO, BUTTONS_BUTTON2_GPIO_PORT_NUM, BUTTONS_BUTTON2_GPIO_BIT_NUM, false);
}

uint8_t Buttons_GetStatus(void)
{
	uint8_t ret = NO_BUTTON_PRESSED;
//	if (Chip_GPIO_ReadPortBit(LPC_GPIO, port, bitnum) == 0x00) {
//		if(bitnum==BUTTONS_BUTTON1)
//			ret |= BUTTONS_BUTTON1;
//		else
//			ret |= BUTTONS_BUTTON2;
//	}

	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, BUTTONS_BUTTON1_GPIO_PORT_NUM, BUTTONS_BUTTON1_GPIO_BIT_NUM))
		ret= BUTTONS_BUTTON1;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, BUTTONS_BUTTON2_GPIO_PORT_NUM, BUTTONS_BUTTON2_GPIO_BIT_NUM))
		ret= BUTTONS_BUTTON2;
	return ret;
}
void Board_Endstops_Init(void)
{
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, XMAX_GPIO_PORT_NUM, XMAX_GPIO_BIT_NUM);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, XMIN_GPIO_PORT_NUM, XMIN_GPIO_BIT_NUM);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, YMAX_GPIO_PORT_NUM, YMAX_GPIO_BIT_NUM);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, YMIN_GPIO_PORT_NUM, YMIN_GPIO_BIT_NUM);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, ZMAX_GPIO_PORT_NUM, ZMAX_GPIO_BIT_NUM);
	Chip_GPIO_SetPinDIRInput(LPC_GPIO, ZMIN_GPIO_PORT_NUM, ZMIN_GPIO_BIT_NUM);
//	Chip_GPIO_SetPinDIRInput(LPC_GPIO, AMAX_GPIO_PORT_NUM, AMAX_GPIO_BIT_NUM);
//	Chip_GPIO_SetPinDIRInput(LPC_GPIO, AMIN_GPIO_PORT_NUM, AMIN_GPIO_BIT_NUM);
}

uint8_t Endstops_GetStatus(void)
{
	uint8_t ret = NO_ENDSTOP_PRESSED;
//	if (Chip_GPIO_ReadPortBit(LPC_GPIO, port, bitnum) == 0x00) {
//		if(bitnum==BUTTONS_BUTTON1)
//			ret |= BUTTONS_BUTTON1;
//		else
//			ret |= BUTTONS_BUTTON2;
//	}

	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, XMAX_GPIO_PORT_NUM, XMAX_GPIO_BIT_NUM))
		ret= XMAX;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, XMIN_GPIO_PORT_NUM, XMIN_GPIO_BIT_NUM))
		ret= XMIN;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, YMAX_GPIO_PORT_NUM, YMAX_GPIO_BIT_NUM))
		ret= YMAX;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, YMIN_GPIO_PORT_NUM, YMIN_GPIO_BIT_NUM))
		ret= YMIN;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, ZMAX_GPIO_PORT_NUM, ZMAX_GPIO_BIT_NUM))
		ret= ZMAX;
	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, ZMIN_GPIO_PORT_NUM, ZMIN_GPIO_BIT_NUM))
		ret= ZMIN;
//	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, AMAX_GPIO_PORT_NUM, AMAX_GPIO_BIT_NUM))
//		ret= AMAX;
//	if (!Chip_GPIO_ReadPortBit(LPC_GPIO, AMIN_GPIO_PORT_NUM, AMIN_GPIO_BIT_NUM))
//		ret= AMIN;
	return ret;
}
/* Set up and initialize all required blocks and functions related to the
   board hardware */
void Board_Init(void)
{
	/* Sets up DEBUG UART */
	DEBUGINIT();

	/* Initializes GPIO */
	Chip_GPIO_Init(LPC_GPIO);
	Chip_IOCON_Init(LPC_IOCON);

}

/* Returns the MAC address assigned to this board */
void Board_ENET_GetMacADDR(uint8_t *mcaddr)
{
	const uint8_t boardmac[] = {0x00, 0x60, 0x37, 0x12, 0x34, 0x56};
	memcpy(mcaddr, boardmac, 6);
}

/* Initialize pin muxing for SSP interface */
void Board_SSP_Init(LPC_SSP_T *pSSP)
{
	if (pSSP == LPC_SSP1) {
		/* Set up clock and muxing for SSP1 interface */
		/*
		 * Initialize SSP0 pins connect
		 * P0.7: SCK
		 * P0.6: SSEL
		 * P0.8: MISO
		 * P0.9: MOSI
		 */
		Chip_IOCON_PinMux(LPC_IOCON, 0, 7, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 6, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 8, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 9, IOCON_MODE_INACT, IOCON_FUNC2);
	}
	else {
		/* Set up clock and muxing for SSP0 interface */
		/*
		 * Initialize SSP0 pins connect
		 * P0.15: SCK
		 * P0.16: SSEL
		 * P0.17: MISO
		 * P0.18: MOSI
		 */
		Chip_IOCON_PinMux(LPC_IOCON, 0, 15, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 16, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 17, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 18, IOCON_MODE_INACT, IOCON_FUNC2);
	}
}

/* Initialize pin muxing for SPI interface */
void Board_SPI_Init(bool isMaster)
{
	/* Set up clock and muxing for SSP0 interface */
	/*
	 * Initialize SSP0 pins connect
	 * P0.15: SCK
	 * P0.16: SSEL
	 * P0.17: MISO
	 * P0.18: MOSI
	 */
	Chip_IOCON_PinMux(LPC_IOCON, 0, 15, IOCON_MODE_PULLDOWN, IOCON_FUNC3);
	if (isMaster) {
		Chip_IOCON_PinMux(LPC_IOCON, 0, 16, IOCON_MODE_PULLUP, IOCON_FUNC0);
		Chip_GPIO_WriteDirBit(LPC_GPIO, 0, 16, true);
		Board_SPI_DeassertSSEL();

	}
	else {
		Chip_IOCON_PinMux(LPC_IOCON, 0, 16, IOCON_MODE_PULLUP, IOCON_FUNC3);
	}
	Chip_IOCON_PinMux(LPC_IOCON, 0, 17, IOCON_MODE_INACT, IOCON_FUNC3);
	Chip_IOCON_PinMux(LPC_IOCON, 0, 18, IOCON_MODE_INACT, IOCON_FUNC3);
}

/* Assert SSEL pin */
void Board_SPI_AssertSSEL(void)
{
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 16, false);
}

/* De-Assert SSEL pin */
void Board_SPI_DeassertSSEL(void)
{
	Chip_GPIO_WritePortBit(LPC_GPIO, 0, 16, true);
}

/* Sets up board specific I2C interface */
void Board_I2C_Init(I2C_ID_T id)
{
	switch (id) {
	case I2C0:
		Chip_IOCON_PinMux(LPC_IOCON, 0, 27, IOCON_MODE_INACT, IOCON_FUNC1);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 28, IOCON_MODE_INACT, IOCON_FUNC1);
		Chip_IOCON_SetI2CPad(LPC_IOCON, I2CPADCFG_STD_MODE);
		break;

	case I2C1:
		Chip_IOCON_PinMux(LPC_IOCON, 0, 19, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 20, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_EnableOD(LPC_IOCON, 0, 19);
		Chip_IOCON_EnableOD(LPC_IOCON, 0, 20);
		break;

	case I2C2:
		Chip_IOCON_PinMux(LPC_IOCON, 0, 10, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_PinMux(LPC_IOCON, 0, 11, IOCON_MODE_INACT, IOCON_FUNC2);
		Chip_IOCON_EnableOD(LPC_IOCON, 0, 10);
		Chip_IOCON_EnableOD(LPC_IOCON, 0, 11);
		break;
	}
}

void Serial_CreateStream(void *Stream)
{}

void Board_USBD_Init(uint32_t port)
{
	/* VBUS is not connected on the NXP LPCXpresso LPC1769, so leave the pin at default setting. */
	/*Chip_IOCON_PinMux(LPC_IOCON, 1, 30, IOCON_MODE_INACT, IOCON_FUNC2);*/ /* USB VBUS */
	
	Chip_IOCON_PinMux(LPC_IOCON, 0, 29, IOCON_MODE_INACT, IOCON_FUNC1);	/* P0.29 D1+, P0.30 D1- */
	Chip_IOCON_PinMux(LPC_IOCON, 0, 30, IOCON_MODE_INACT, IOCON_FUNC1);

	LPC_USB->USBClkCtrl = 0x12;                /* Dev, AHB clock enable */
	while ((LPC_USB->USBClkSt & 0x12) != 0x12); 
}

