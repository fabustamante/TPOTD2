///*
// * GCodeDispatch.c
// *
// *  Created on: 20 de nov. de 2017
// *      Author: Fernando
// */
//#include <TD2CNC.h>
//
//
//
///**
//	@fn void gc_init(void)
//	@brief Inicializa los bloques gc
// 	@details  Carga con valores por default las variables necesarias
// 	@return void
// */
//void gc_init(parser_block_t* gc_block,parser_state_t* gc_state,
//		uint8_t* axis_0,uint8_t* axis_1,uint8_t* axis_linear)
//{
//	int i;
//	memset( gc_state, 0, sizeof(*gc_state));
//	memset( gc_block, 0, sizeof(*gc_block));
//
//	for(i=0;i<N_AXIS;i++)
//		gc_state->position[i]=(float)sys.planner_position[i] /  settings.steps_per_mm[i];
//
//	gc_block->modal.distance 		= 	settings.def_distance_mode;
//	gc_block->modal.feed_rate 		= 	settings.def_feedrate_mode;
//	gc_block->modal.motion			= 	settings.def_motion_mode;
//	gc_block->modal.plane_select	= 	settings.work_plane;
//	gc_block->modal.spindle  		= 	settings.spindle;
//	gc_block->modal.units 			=	settings.units;
//	gc_block->values.f				=   settings.def_feed_rate[0];
//	*axis_0 = Y_AXIS;
//	*axis_1 = Z_AXIS;
//	*axis_linear = X_AXIS;
//}
//
///*
// *	@fn  uint8_t gcode_execute_line (char* linea)
// *	@brief Separa por espacios y retornos de carro
// * 	@details Cada token es enviado para ser analizado, cuando se encuentra el fin de linea, se llena el gcode_block
// * 	@return uint8_t
// */
//void vGCodeDispatchTask (void* Parameters)
//{
//	char str[LINE_BUFFER_SIZE];
//	char token[LINE_BUFFER_SIZE];//,linea;
//	struct AMessage *pxRxedMessage;
////	char* token;
//	parser_block_t gc_block;
//	parser_state_t gc_state;
//	uint8_t axis_0, axis_1, axis_linear;
//
//	gc_init(&gc_block,&gc_state,&axis_0,&axis_1,&axis_linear);
//
//	for(;;)
//	{
//		xQueueReceive( xQueue_GCodeLine, &( pxRxedMessage ), portMAX_DELAY );
//
//		memset( &gc_block.values, 0, sizeof(gc_block.values));
//		gc_block.values.f	=   settings.def_feed_rate[0];
//		strcpy (str,pxRxedMessage->ucMsg);
//		strcpy(token , strtok (str," \n"));
////		token = strtok (str,"\n");
//		while(token[0]!='\0')
//		{
////			gcode_parser(token);
//			xQueueSendToBack( xQueue_GCodeToken, &token, portMAX_DELAY );
//			strcpy(token , strtok (NULL," "));
////			token = strtok (NULL," ");
//			xQueueReceive( xQueue_GCBlock, &gc_block, portMAX_DELAY );
//		}
//
////		if (sys.alarm != NO_ALARM)
////			return;
//
//
//
//		vTaskDelay(50/portTICK_RATE_MS);
//	}
//}
//
///**
//	@fn  void gcode_parser (char *line)
//	@brief Recibe tokens y carga valores de gc_block
// 	@details --
// 	@return void
// */
//void vGCodeParserTask (void* Parameters) {
//	char line[LINE_BUFFER_SIZE];
//	char letter;
//	float value;
//	short int_value = 0;
//	short mantissa = 0;
//	parser_block_t gc_block;
//	memset( &gc_block.values, 0, sizeof(gc_block.values));
//	gc_block.values.f	=   settings.def_feed_rate[0];
//	for(;;)
//	{
//
//		xQueueReceive( xQueue_GCodeToken, &line, portMAX_DELAY );
//
//		letter = line [0];
//		if ( (letter < 'A' || letter > 'Z')){
//			sys.alarm = STATUS_EXPECTED_COMMAND_LETTER;
//			//return;
//		}
//		read_float ( line, &value);
//
//		int_value = (int) value;
//		mantissa =  (int) 100*(value - int_value);
//
//		switch(letter) {
//		if ( mantissa == 0){
//		case 'G':
//			switch(int_value)
//			{
//				case 0: gc_block.modal.motion = MOTION_MODE_SEEK; break;
//				case 1: gc_block.modal.motion = MOTION_MODE_LINEAR; break;
//				case 2: gc_block.modal.motion = MOTION_MODE_CW_ARC; break;
//				case 3: gc_block.modal.motion = MOTION_MODE_CCW_ARC; break;
//
//				case 17: gc_block.modal.plane_select = PLANE_SELECT_XY; break;
//				case 18: gc_block.modal.plane_select = PLANE_SELECT_ZX; break;
//				case 19: gc_block.modal.plane_select = PLANE_SELECT_YZ; break;
//
//				case 90: gc_block.modal.distance = DISTANCE_MODE_ABSOLUTE; break;
//				case 91: gc_block.modal.distance = DISTANCE_MODE_INCREMENTAL; break;
//
//				case 93: gc_block.modal.feed_rate = FEED_RATE_MODE_INVERSE_TIME; break;
//				case 94: gc_block.modal.feed_rate = FEED_RATE_MODE_UNITS_PER_MIN; break;
//
//				case 20: gc_block.modal.units = UNITS_MODE_INCHES; break;
//				case 21: gc_block.modal.units = UNITS_MODE_MM; break;
//
//				case 4:  gc_block.non_modal_command = NON_MODAL_DWELL; break;
//				case 28: gc_block.non_modal_command = NON_MODAL_GO_HOME; break;
//
//				default: sys.alarm = STATUS_GCODE_UNSUPPORTED_COMMAND;
//			} break;
//
//			case 'M':
//				switch(int_value)
//				{
//					case 2: case 30: gc_block.modal.program_flow = PROGRAM_FLOW_COMPLETED; break;
//					case 3: case 4:  gc_block.modal.spindle = SPINDLE_ENABLE; break;
//					case 5: gc_block.modal.spindle = SPINDLE_ENABLE; break;
//					default: sys.alarm = STATUS_GCODE_UNSUPPORTED_COMMAND; //return ;
//				}break;
//		}
//		case 'F': gc_block.values.f = value / 10; break;
//		case 'I': gc_block.values.ijk[X_AXIS] = value;  break;
//		case 'J': gc_block.values.ijk[Y_AXIS] = value;  break;
//		case 'K': gc_block.values.ijk[Z_AXIS] = value;  break;
//		case 'P': gc_block.values.p = value; break;
//		case 'R': gc_block.values.r = value; break;
//		case 'S': gc_block.values.s = value; break;
//		case 'X': gc_block.values.xyz[X_AXIS] = value; break;
//		case 'Y': gc_block.values.xyz[Y_AXIS] = value; break;
//		case 'Z': gc_block.values.xyz[Z_AXIS] = value; break;
//		default: sys.alarm = STATUS_GCODE_UNSUPPORTED_COMMAND; //return ;
//		}
//		xQueueSendToBack( xQueue_GCBlock, &gc_block, portMAX_DELAY );
//		vTaskDelay(50/portTICK_RATE_MS);
//	}
//}
//
///**
//	@fn void read_float(char *linea, float *valor)
//	@brief  extrae el valor flotante de un string
// 	@details guarda el valor en una variable pasada por referencia
// 	@return void
// */
//void read_float (char *linea, float *valor){
//
//	char *pos_inicial = linea + 1;
//	*valor = atof (pos_inicial);
//
//	return;
//}
