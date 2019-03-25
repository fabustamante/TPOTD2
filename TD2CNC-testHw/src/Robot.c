/*
 * Robot.c
 *
 *  Created on: 20 de nov. de 2017
 *      Author: Fernando
 */
#include <TD2CNC.h>

void vRobotTask (void* Parameters)
{
	parser_block_t gc_block;
	parser_state_t gc_state;
	uint8_t axis_0, axis_1, axis_linear;
	uint8_t i=0;
	plan_block_t  pl_block_aux;

	memset(&pl_block_aux,0,sizeof(pl_block_aux));
	memset( &gc_state, 0, sizeof(gc_state));

	for(i=0;i<N_AXIS;i++)
		gc_state.position[i]=(float)sys.planner_position[i] /  settings.steps_per_mm[i];

	for(;;)
	{
		xQueueReceive( xQueue_GCodeBlock, &gc_block, portMAX_DELAY );

		gc_state.line_number = gc_block.values.n;
		gc_state.modal.feed_rate = gc_block.modal.feed_rate;
		gc_state.feed_rate = gc_block.values.f;
		gc_state.modal.spindle = gc_block.modal.spindle;
		gc_state.modal.plane_select = gc_block.modal.plane_select;
		gc_state.modal.units = gc_block.modal.units;
		gc_state.modal.distance = gc_block.modal.distance;
		gc_state.modal.motion = gc_block.modal.motion;
		gc_state.modal.program_flow = gc_block.modal.program_flow;

		splindle_control(gc_state.modal.spindle);

		switch (gc_block.modal.plane_select)
		{
			case PLANE_SELECT_YZ:
				axis_0 = Y_AXIS;
				axis_1 = Z_AXIS;
				axis_linear = X_AXIS;
				break;
			case PLANE_SELECT_ZX:
				axis_0 = Z_AXIS;
				axis_1 = X_AXIS;
				axis_linear = Y_AXIS;
				break;
			default:
				axis_0 = X_AXIS;
				axis_1 = Y_AXIS;
				axis_linear = Z_AXIS;
		}


		if(gc_state.modal.units==UNITS_MODE_INCHES)
		{
			gc_block.values.xyz[X_AXIS]*=25.4;
			gc_block.values.xyz[Y_AXIS]*=25.4;
			gc_block.values.xyz[Z_AXIS]*=25.4;
		}


		if (gc_state.modal.motion != MOTION_MODE_NONE)
		{
			if(gc_state.modal.distance == DISTANCE_MODE_ABSOLUTE)
			{
				gc_block.values.xyz[X_AXIS]-=gc_state.position[X_AXIS];
				gc_block.values.xyz[Y_AXIS]-=gc_state.position[Y_AXIS];
				gc_block.values.xyz[Z_AXIS]-=gc_state.position[Z_AXIS];
			}
			switch (gc_state.modal.motion)
			{
				case MOTION_MODE_SEEK:
//					mc_line(gc_block.values.xyz, -1.0, FALSE);
					gc_state.feed_rate=-1.0;
					gc_state.modal.feed_rate = FEED_RATE_MODE_UNITS_PER_MIN;
					break;
				case MOTION_MODE_LINEAR:
//					mc_line(gc_block.values.xyz, gc_state.feed_rate, gc_state.modal.feed_rate);
					break;
				case MOTION_MODE_CW_ARC:
	//				mc_arc(gc_state.position, gc_block.values.xyz, gc_block.values.ijk, gc_block.values.r,
	//						gc_state.feed_rate, gc_state.modal.feed_rate, axis_0, axis_1, axis_linear, CW);
					break;
				case MOTION_MODE_CCW_ARC:
	//				mc_arc(gc_state.position, gc_block.values.xyz, gc_block.values.ijk, gc_block.values.r,
	//						gc_state.feed_rate, gc_state.modal.feed_rate, axis_0, axis_1, axis_linear, CCW);
					break;
			}
			for ( i=0 ; i<N_AXIS; i++)
			{
				if ( gc_state.modal.feed_rate == FEED_RATE_MODE_UNITS_PER_MIN )
					pl_block_aux.feed_rate[i] = gc_state.feed_rate;
				if ( gc_state.modal.feed_rate == FEED_RATE_MODE_INVERSE_TIME )
					pl_block_aux.feed_rate[i] = 1/gc_state.feed_rate;

				pl_block_aux.steps[i] = (int)(gc_block.values.xyz[i] * (float)settings.steps_per_mm[i]);
				if(i==Z_AXIS)
				{
					if (pl_block_aux.steps[i]  >= 0)
						pl_block_aux.direction_bits[i] = CCW;
					else
					{
						pl_block_aux.direction_bits[i] = CW;
						pl_block_aux.steps[i]  *= -1;
					}
				}
				else
				{
					if (pl_block_aux.steps[i]  >= 0)
						pl_block_aux.direction_bits[i] = CW;
					else
					{
						pl_block_aux.direction_bits[i] = CCW;
						pl_block_aux.steps[i]  *= -1;
					}
				}
				gc_state.position[i]+=gc_block.values.xyz[i];
			}
			xQueueSendToBack( xQueue_PlannerBlock, &pl_block_aux, portMAX_DELAY );
		}

		if (gc_state.modal.program_flow == PROGRAM_FLOW_COMPLETED)
			sys.S_Auto.flag_gcode_finished=TRUE;

	}
}
