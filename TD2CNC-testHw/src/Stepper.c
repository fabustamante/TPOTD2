/*
 * Stepper.c
 *
 *  Created on: 20 de nov. de 2017
 *      Author: Fernando
 */
#include <TD2CNC.h>

st_block_t st_auto_block;

/**
	@fn st_block_init(void)
	@brief llama a memset  y pone en cero a st_auto_block
 	@details  ---
 	@return void
 */
void st_block_init (void)
{
	memset(&st_auto_block, 0, sizeof(st_auto_block));
}

/*
 * 	@fn  void st_stepper_move (void)
 *	@brief Control de steppers a traves de timers asociados
 *  @details Entramos a esta funcion si no hay alarmas y hay bloques en el buffer
 *  Una vez dentro comprobamos la finalizacion del bloque anterior, en ese caso
 *  sacamos un nuevo bloque del buffer y cargamos los valores de match (que daran la velocidad),
 *  los contadoresde pasos y asignamos las direcciones de ese bloque.
 *	@param void
 *  @return void
 */
void vStepperMoveTask (void* Parameters)
{
	uint8_t i;
	st_block_t st_block_received,st_aux_auto_block;

	for ( i=0; i< N_AXIS ; i++)
	{
		sys.S_Auto.flag_end_block[i]=TRUE;
	}
	for(;;)
	{

		memset(&st_aux_auto_block, 0, sizeof(st_aux_auto_block));

		if (sys.S_Auto.flag_end_block[X_AXIS] &&
			sys.S_Auto.flag_end_block[Y_AXIS] &&
			sys.S_Auto.flag_end_block[Z_AXIS] )
		{
			if (uxQueueMessagesWaiting( xQueue_StepperBlock )==0)
			{
				sys.S_Auto.flag_all_blocks_finished=TRUE;
//					xSemaphoreGive(xsemEndProgram);
			}
			xQueueReceive( xQueue_StepperBlock, &st_block_received, portMAX_DELAY );

			for ( i=0; i< N_AXIS ; i++)
			{

				sys.S_Auto.flag_end_block[i] = FALSE;
				sys.S_Auto.flag_all_blocks_finished=FALSE;

				st_aux_auto_block.direction_bits[i] = st_block_received.direction_bits[i];
				st_aux_auto_block.steps[i] = st_block_received.steps[i];

				if(st_block_received.feed_rate[i] == 0 )
					st_aux_auto_block.feed_rate[i] = settings.def_feed_rate[i];
				else
					st_aux_auto_block.feed_rate[i] = st_block_received.feed_rate[i];

				st_move_line (  i,
						st_aux_auto_block.direction_bits[i],
						st_aux_auto_block.steps[i],
						st_aux_auto_block.feed_rate[i] );
			}
		}
		vTaskDelay(10/portTICK_RATE_MS);
	}

}

/**
	@fn st_move_line(void)
	@brief se fija que eje es el que se va a mover y lo setea
 	@details retorna DONE o UNDONE
 	@return uint8_t
 */
void st_move_line ( uint8_t axis, uint8_t dir, uint32_t steps, uint16_t feed_rate )
{
	///Auxiliary Variables
	uint32_t matchVal = 0;
	uint32_t timerFreq = 0;
	uint8_t channel = 1;
	uint8_t aux;
	st_wake_up();
	if ( sys.firstHome)
		aux = 1;
	else
		aux = soft_check_limit(axis, dir, steps);

	if( aux )
	{
		if(axis==X_AXIS)
		{
			st_auto_block.steps[X_AXIS]=steps;
			st_auto_block.direction_bits[X_AXIS]=dir;
			st_setdir(axis,dir);
			sys.S_Auto.flag_end_block[X_AXIS] = false;
			timerFreq = Chip_Clock_GetSystemClockRate();
			matchVal  = timerFreq / TICKRATE_HZ;
			matchVal=matchVal/feed_rate;
			Board_InitTimer(LPC_TIMER0,channel,matchVal);

		}
		if(axis==Y_AXIS)
		{
			st_auto_block.steps[Y_AXIS]=steps;
			st_auto_block.direction_bits[Y_AXIS]=dir;
			st_setdir(axis,dir);
			sys.S_Auto.flag_end_block[Y_AXIS] = false;
			timerFreq = Chip_Clock_GetSystemClockRate();
			matchVal  = timerFreq / TICKRATE_HZ;
			matchVal=matchVal/feed_rate;
			Board_InitTimer(LPC_TIMER1,channel,matchVal);
		}
		if(axis==Z_AXIS)
		{
			st_auto_block.steps[Z_AXIS]=steps;
			st_auto_block.direction_bits[Z_AXIS]=dir;
			st_setdir(axis,dir);
			sys.S_Auto.flag_end_block[Z_AXIS] = false;
			timerFreq = Chip_Clock_GetSystemClockRate();
			matchVal  = timerFreq / TICKRATE_HZ;
			matchVal=matchVal/feed_rate;
			Board_InitTimer(LPC_TIMER2,channel,matchVal);
		}
	}
}

/**
	@fn st_setdir(uint8_t axis, uint8_t dir)
	@brief setea la direccion a los ejes
 	@details  ---
 	@return void
 */
void st_setdir(uint8_t axis,uint8_t dir)
{
	if (axis == X_AXIS)
	{
		if(dir==CW	)
			Board_LED_Set(XDIR_GPIO_PORT_NUM,XDIR_GPIO_BIT_NUM, false);
		if(dir==CCW	)
			Board_LED_Set(XDIR_GPIO_PORT_NUM,XDIR_GPIO_BIT_NUM, true);
	}
	if (axis == Y_AXIS)
	{
		if(dir==CW	)
			Board_LED_Set(YDIR_GPIO_PORT_NUM,YDIR_GPIO_BIT_NUM, false);
		if(dir==CCW	)
			Board_LED_Set(YDIR_GPIO_PORT_NUM,YDIR_GPIO_BIT_NUM, true);
	}
	if (axis == Z_AXIS)
	{
		if(dir==CW	)
			Board_LED_Set(ZDIR_GPIO_PORT_NUM,ZDIR_GPIO_BIT_NUM, false);
		if(dir==CCW	)
			Board_LED_Set(ZDIR_GPIO_PORT_NUM,ZDIR_GPIO_BIT_NUM, true);
	}
}

/**
	@fn stepper_stop(void)
	@brief frena el movimiento de los ejes
 	@details  ---
 	@return void
 */
void stepper_stop(void)
{
	Board_Steppers_OFF();

	st_auto_block.steps[X_AXIS]=0;
	st_auto_block.steps[Y_AXIS]=0;
	st_auto_block.steps[Z_AXIS]=0;

	Board_TimerClose(LPC_TIMER0);
	Board_TimerClose(LPC_TIMER1);
	Board_TimerClose(LPC_TIMER2);

}

/**
	@fn st_wake_up(void)
	@brief habilita los motores
 	@details  logica inversa
 	@return void
 */
void st_wake_up(void)
{
	Board_LED_Set(XEN_GPIO_PORT_NUM,XEN_GPIO_BIT_NUM, st_ON);
	Board_LED_Set(YEN_GPIO_PORT_NUM,YEN_GPIO_BIT_NUM, st_ON);
	Board_LED_Set(ZEN_GPIO_PORT_NUM,ZEN_GPIO_BIT_NUM, st_ON);
}

/*------------------------------------------------------------------*/
void vXMoveTask (void* pvParameters )
{
	///Auxiliary Variables
	uint32_t counter = 0;

	///First take of Timer 0 Semaphore
	xSemaphoreTake(xsemTimer0, 0);
	Board_LED_Set(XSTEP_GPIO_PORT_NUM,XSTEP_GPIO_BIT_NUM, false);
	///Infinite Loop Start
	for (;;)
	{
		///Second take of Timer 0 Semaphore
		xSemaphoreTake(xsemTimer0, portMAX_DELAY);
		/**
		 * Here we start a for loop, that (starting StepCounter to STEPS
		 * value) decreases StepCounter. This process depends of the giving of
		 * xsemTimer0 via interruptions "machinery".
		 */
		///Inverting the value of the led in every iteration
		if(st_auto_block.steps[X_AXIS] > 0)
		{
			Board_LED_Toggle(XSTEP_GPIO_PORT_NUM,XSTEP_GPIO_BIT_NUM);
			if(counter)
			{

				st_auto_block.steps[X_AXIS]--;
				if(st_auto_block.direction_bits[X_AXIS]==CW)
					sys.position[X_AXIS]++;
				if(st_auto_block.direction_bits[X_AXIS]==CCW)
					sys.position[X_AXIS]--;
			}
			counter++;
			counter%=2;
		}
		if( !st_auto_block.steps[X_AXIS] )
		{
			Board_TimerClose(LPC_TIMER0);
			Board_LED_Set(XSTEP_GPIO_PORT_NUM,XSTEP_GPIO_BIT_NUM, false);
			sys.S_Auto.flag_end_block[X_AXIS] = true;
			xSemaphoreTake(xsemTimer0, 0);
		}
	}
}
/*------------------------------------------------------------------*/
void vYMoveTask (void* pvParameters )
{
	///Auxiliary Variables
	uint32_t counter = 0;

	///First take of Timer 1 Semaphore
	xSemaphoreTake(xsemTimer1, 0);
	Board_LED_Set(YSTEP_GPIO_PORT_NUM,YSTEP_GPIO_BIT_NUM, false);
	///Infinite Loop Start
	for (;;)
	{
		///Second take of Timer 1 Semaphore
		xSemaphoreTake(xsemTimer1, portMAX_DELAY);
		/**
		 * Here we start a for loop, that (starting StepCounter to STEPS
		 * value) decreases StepCounter. This process depends of the giving of
		 * xsemTimer0 via interruptions "machinery".
		 */
		///Inverting the value of the led in every iteration
		if(st_auto_block.steps[Y_AXIS] > 0)
		{
			Board_LED_Toggle(YSTEP_GPIO_PORT_NUM,YSTEP_GPIO_BIT_NUM);
			if(counter)
			{
				st_auto_block.steps[Y_AXIS]--;
				if(st_auto_block.direction_bits[Y_AXIS]==CW)
					sys.position[Y_AXIS]++;
				if(st_auto_block.direction_bits[Y_AXIS]==CCW)
					sys.position[Y_AXIS]--;
			}
			counter++;
			counter%=2;
		}
		if( !st_auto_block.steps[Y_AXIS] )
		{
			Board_TimerClose(LPC_TIMER1);
			Board_LED_Set(YSTEP_GPIO_PORT_NUM,YSTEP_GPIO_BIT_NUM, false);
			sys.S_Auto.flag_end_block[Y_AXIS] = true;
			xSemaphoreTake(xsemTimer1, 0);
		}
	}
}
void vZMoveTask (void* pvParameters )
{
	///Auxiliary Variables
	uint32_t counter = 0;

	///First take of Timer 2 Semaphore
	xSemaphoreTake(xsemTimer2, 0);
	Board_LED_Set(ZSTEP_GPIO_PORT_NUM,ZSTEP_GPIO_BIT_NUM, false);
	///Infinite Loop Start
	for (;;)
	{
		///Second take of Timer 2 Semaphore
		xSemaphoreTake(xsemTimer2, portMAX_DELAY);
		/**
		 * Here we start a for loop, that (starting StepCounter to STEPS
		 * value) decreases StepCounter. This process depends of the giving of
		 * xsemTimer2 via interruptions "machinery".
		 */
		///Inverting the value of the led in every iteration
		if(st_auto_block.steps[Z_AXIS] > 0)
		{
			Board_LED_Toggle(ZSTEP_GPIO_PORT_NUM,ZSTEP_GPIO_BIT_NUM);
			if(counter)
			{
				st_auto_block.steps[Z_AXIS]--;
				if(st_auto_block.direction_bits[Z_AXIS]==CCW)
					sys.position[Z_AXIS]++;
				if(st_auto_block.direction_bits[Z_AXIS]==CW)
					sys.position[Z_AXIS]--;
			}
			counter++;
			counter%=2;
		}
		if( !st_auto_block.steps[Z_AXIS] )
		{
			Board_TimerClose(LPC_TIMER2);
			Board_LED_Set(ZSTEP_GPIO_PORT_NUM,ZSTEP_GPIO_BIT_NUM, false);
			sys.S_Auto.flag_end_block[Z_AXIS] = true;
			xSemaphoreTake(xsemTimer2, 0);
		}
	}
}
