/*
 * appinit.c
 *
 *  Created on: 20 de nov. de 2017
 *      Author: Fernando
 */
#include <TD2CNC.h>
settings_t settings;

void prvSetupHardware(void)
{

   /* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();
	/* Initialize Tact Switch */
//	Board_Buttons_Init();
#ifdef UART0
	Board_UART_Init(LPC_UART0,9600);
#endif
#ifdef LCD
	Board_InitLCD ( );
#endif
//	EINTInit( );
#ifdef MATRIX_KEYBOARD
	Board_MatrixKeyboard_4x4_Init();
#endif

#ifdef LEDS
	/* Initialize LEDs */
	Board_LED_Init();
	///Initial LED state is off
	Board_TurnOff_All_LEDs();
#endif

	Board_Steppers_Init();
	Board_Spindle_Init();
	Board_Steppers_OFF();

}
void init_system_var (void)
{
	sys.state = SysINIT;
	sys.alarm = NO_ALARM;
	sys.firstHome = TRUE;
	sys.abort = FALSE;
	sys.endstop_rached = FALSE;
	sys.manual_key = NO_KEY;
	sys.suspend = FALSE;

	sys.new_Home_Ref[X_AXIS] = 0;
	sys.new_Home_Ref[Y_AXIS] = 0;
	sys.new_Home_Ref[Z_AXIS] = 0;
	sys.S_Auto.flag_all_blocks_finished = FALSE;
	sys.S_Auto.flag_gcode_finished = FALSE;
	sys.S_Auto.flag_end_block[X_AXIS] = true;
	sys.S_Auto.flag_end_block[Y_AXIS] = true;
	sys.S_Auto.flag_end_block[Z_AXIS] = true;
}
void settings_restore_global_settings()
{
	  settings.steps_per_mm[X_AXIS] = DEFAULT_X_STEPS_PER_MM;
	  settings.steps_per_mm[Y_AXIS] = DEFAULT_Y_STEPS_PER_MM;
	  settings.steps_per_mm[Z_AXIS] = DEFAULT_Z_STEPS_PER_MM;
	  settings.max_feed_rate[X_AXIS] = DEFAULT_X_MAX_RATE;
	  settings.max_feed_rate[Y_AXIS] = DEFAULT_Y_MAX_RATE;
	  settings.max_feed_rate[Z_AXIS] = DEFAULT_Z_MAX_RATE;
	  settings.max_travel_steps[X_AXIS] = DEFAULT_X_MAX_TRAVEL;
	  settings.max_travel_steps[Y_AXIS] = DEFAULT_Y_MAX_TRAVEL;
	  settings.max_travel_steps[Z_AXIS] = DEFAULT_Z_MAX_TRAVEL;
	  settings.work_plane = DEFAULT_PLANE;
	  settings.units = DEFAULT_UNITS;
	  settings.def_feed_rate[X_AXIS]= DEFAULT_FEEDRATE_XY;
	  settings.def_feed_rate[Y_AXIS]= DEFAULT_FEEDRATE_XY;
	  settings.def_feed_rate[Z_AXIS]= DEFAULT_FEEDRATE_Z;
	  settings.manual_steps[X_AXIS] = DEFAULT_MANUAL_STEPS_XY;
	  settings.manual_steps[Y_AXIS] = DEFAULT_MANUAL_STEPS_XY;
	  settings.manual_steps[Z_AXIS] = DEFAULT_MANUAL_STEPS_Z;
	  settings.def_motion_mode	= DEFAUL_MOTION_MODE;
	  settings.def_distance_mode = DEFAUL_DISTANSCE_MODE;
	  settings.spindle  = DEFAULT_SPINDLE_MODE;
	  settings.def_feedrate_mode = DEFAULT_FEEDRATE_MODE;
}
