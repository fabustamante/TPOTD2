/*
 * Planner.c
 *
 *  Created on: 20 de nov. de 2017
 *      Author: Fernando
 */

#include <TD2CNC.h>

settings_t settings;


/**
	@fn uint8_t plan_move_manual(void)
	@brief Mira que eje debe mover y en que direccion
 	@details Si no se pudo retorna undone
 	@return uint8_t
 */

void vCncControllerTask(void* pvParameters)
{
	char systemCommands=NO_KEY,displayCommands=UPDATE_POS;
	uint8_t spindle_ONOFF = SPINDLE_DISABLE;
	settings_restore_global_settings();
	init_system_var();
	sys.state=S_IDLE;
	splindle_control (spindle_ONOFF);
	spindle_ONOFF = SPINDLE_ENABLE;

	for(;;)
	{
		xQueueReceive(xQueue_KBCommands, &systemCommands,portMAX_DELAY);
		xQueueSendToBack(xQueue_Display, &displayCommands,portMAX_DELAY);
//		st_wake_up();
		switch(systemCommands)
		{
		case key_XR:
			st_move_line( X_AXIS, CW, settings.manual_steps[X_AXIS], settings.def_feed_rate[X_AXIS]);
			break;
		case key_XL:
			st_move_line( X_AXIS, CCW, settings.manual_steps[X_AXIS], settings.def_feed_rate[X_AXIS]);
			break;
		case key_YR:
			st_move_line( Y_AXIS, CW, settings.manual_steps[Y_AXIS], settings.def_feed_rate[Y_AXIS]);
			break;
		case key_YL:
			st_move_line( Y_AXIS, CCW, settings.manual_steps[Y_AXIS], settings.def_feed_rate[Y_AXIS]);
			break;
		case key_ZD:
			st_move_line( Z_AXIS, CW, settings.manual_steps[Z_AXIS]/5, settings.def_feed_rate[Z_AXIS]);
			break;
		case key_ZU:
			st_move_line( Z_AXIS, CCW, settings.manual_steps[Z_AXIS]/5, settings.def_feed_rate[Z_AXIS]);
			break;
		case key_Spindle_ONOFF:
			if(spindle_ONOFF)
				splindle_control (SPINDLE_ENABLE);
			else
				splindle_control (SPINDLE_DISABLE);
			spindle_ONOFF ++;
			spindle_ONOFF %= 2;
			break;
		case key_SET_ZERO_ALL:
			setHome(Ser_SET_ZERO_ALL);
			break;
		case key_SET_ZERO_X:
			setHome(Ser_SET_ZERO_X);
			break;
		case key_SET_ZERO_Y:
			setHome(Ser_SET_ZERO_Y);
			break;
		case key_SET_ZERO_XY:
			setHome(Ser_SET_ZERO_X);setHome(Ser_SET_ZERO_Y);
			break;
		case key_SET_ZERO_Z:
			setHome(Ser_SET_ZERO_Z);
			break;
		case key_GO_HOME:
			goHome(Ser_GO_HOME);
			break;
		case key_GO_VIEW:
			goHome(Ser_GO_VIEW);
			break;
		}
	}
}


/**
	@fn uint8_t goHome (void)
	@brief Mueve los ejes al valor seteado como "home"
 	@details
 	@return uint8_t
 */
void goHome(uint8_t aux)
{
	uint8_t flag=0;

	if (aux == Ser_GO_HOME )
	{
		st_move_line( Z_AXIS, CW, sys.position[Z_AXIS], settings.def_feed_rate[Z_AXIS]);
		sys.planner_position[Z_AXIS]=0;
//		if(sys.S_Auto.flag_end_block[Z_AXIS])
//		{
//			st_move_line( X_AXIS, CCW, sys.position[X_AXIS], settings.def_feed_rate[X_AXIS]);
//			sys.planner_position[X_AXIS]=0;
//
//			st_move_line( Y_AXIS, CCW, sys.position[Y_AXIS], settings.def_feed_rate[Y_AXIS]);
//			sys.planner_position[Y_AXIS]=0;
//		}
	}
//	else
//	{
		st_move_line( X_AXIS, CCW, sys.position[X_AXIS], settings.def_feed_rate[X_AXIS]);
		sys.planner_position[X_AXIS]=0;

		st_move_line( Y_AXIS, CCW, sys.position[Y_AXIS], settings.def_feed_rate[Y_AXIS]);
		sys.planner_position[Y_AXIS]=0;
//	}

}

/**
	@fn uint8_t setHome(void)
	@brief Setea "home" en el lugar actual de los ejes
 	@details Actualiza la posicion de sys y planner
 	@return uint8_t
 */
uint8_t setHome(uint8_t teclaAux)
{
	uint8_t Flag_firsthome[4] = {FALSE,FALSE,FALSE,FALSE};
	char command;
	switch (teclaAux)
	{
	case Ser_SET_ZERO_ALL:
		memset (sys.planner_position,0,sizeof(sys.planner_position));
		memset (sys.position,0,sizeof(sys.position));
		Flag_firsthome[0] = TRUE;
		break;
	case Ser_SET_ZERO_X:
		memset (&sys.planner_position[X_AXIS],0,sizeof(sys.planner_position[X_AXIS]));
		memset (&sys.position[X_AXIS],0,sizeof(sys.position[X_AXIS]));
		Flag_firsthome[1] = TRUE;
		break;
	case Ser_SET_ZERO_Y:
		memset (&sys.planner_position[Y_AXIS],0,sizeof(sys.planner_position[Y_AXIS]));
		memset (&sys.position[Y_AXIS],0,sizeof(sys.position[Y_AXIS]));
		Flag_firsthome[2] = TRUE;
		break;
	case Ser_SET_ZERO_Z:
		memset (&sys.planner_position[Z_AXIS],0,sizeof(sys.planner_position[Z_AXIS]));
		memset (&sys.position[Z_AXIS],0,sizeof(sys.position[Z_AXIS]));
		Flag_firsthome[3] = TRUE;
		break;
	}
	command = UPDATE_POS;
	xQueueSendToBack( xQueue_Display, &command, portMAX_DELAY );
	if ( Flag_firsthome[1] && Flag_firsthome[2] && Flag_firsthome[3]) //<! sys.firstHome habilita o deshabilita soft_check_limits();
		sys.firstHome = 0;
	if (Flag_firsthome[0])
		sys.firstHome = 0;

	return DONE;
}

/**
	@fn void splindle_control (uint8_t spinlde)
	@brief  controla el estado del spindle
 	@details  --
 	@return void
 */
void splindle_control (uint8_t spindle)
{
	xQueueSendToBack( xQueue_Display, &spindle, portMAX_DELAY );
	if (spindle == SPINDLE_ENABLE)
	{
		Board_LED_Set(SPINDLE_GPIO_PORT_NUM,SPINDLE_GPIO_BIT_NUM, true);
	}
	else
	{
		Board_LED_Set(SPINDLE_GPIO_PORT_NUM,SPINDLE_GPIO_BIT_NUM, false);
	}
}
