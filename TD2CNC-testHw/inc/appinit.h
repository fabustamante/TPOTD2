
#ifndef INC_APPINIT_H_
#define INC_APPINIT_H_
/* On the LPC1769, the GPIO interrupts share the EINT3 vector. */
#define GPIO_IRQ_HANDLER  			EINT3_IRQHandler/* GPIO interrupt IRQ function name */
#define GPIO_INTERRUPT_NVIC_NAME    EINT3_IRQn	/* GPIO interrupt NVIC interrupt name */
void prvSetupHardware(void);
#define LCD
//#define LEDS
#define UART0
#define MATRIX_KEYBOARD
#endif /* INC_GCODE_H_ */
