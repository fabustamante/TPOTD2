/*
 * Planner.c
 *
 *  Created on: 20 de nov. de 2017
 *      Author: Fernando
 */

#include <TD2CNC.h>

settings_t settings;

void vPlannerTask (void* Parameters)
{
	plan_block_t  pl_block_aux;
	st_block_t st_block;
	float valorxyz;
	uint8_t i;
	memset(&pl_block_aux,0,sizeof(pl_block_aux));
	for(;;)
	{
		xQueueReceive( xQueue_PlannerBlock, &pl_block_aux, portMAX_DELAY );
		for ( i=0 ; i<N_AXIS; i++)
		{
			if ( !soft_check_limit ( i, pl_block_aux.direction_bits[i], pl_block_aux.steps[i]))
			{
				switch(i)
				{
				case X_AXIS:
					sys.alarm = SOFT_LIMIT_ERROR_X;
					break;
				case Y_AXIS:
					sys.alarm = SOFT_LIMIT_ERROR_Y;
					break;
				case Z_AXIS:
					sys.alarm = SOFT_LIMIT_ERROR_Z;
					break;
				}
			}
			if (pl_block_aux.steps[i]  >= 0)
				sys.planner_position[i]+=pl_block_aux.steps[i];
			else
				sys.planner_position[i]-=pl_block_aux.steps[i];

		}
		asignar_velocidades(&pl_block_aux);

		xQueueSendToBack( xQueue_StepperBlock, &st_block, portMAX_DELAY );
	}
}
///**
//	@fn uint8_t mc_line(void)
//	@brief Carga la velocidad, direccion y cantidad de pasos en plan_block_buffer
// 	@details Buffer circular
// 	@return uint8_t
// */
//uint8_t mc_line( float *xyz, float feed_rate, uint8_t feed_rate_mode)
//{
//
//
//}

/*
 *	@fn  void asignar_velocidades ( plan_block_t* pl_block_aux )
 *	@brief Asigna velocidades a cada eje
 *  @details Al manejar cada motor individualmente es necesario asignar
 *  velocidades diferentes a cada uno para trazar una diagonal
 *  @return void
 */
void asignar_velocidades ( plan_block_t* pl_block_aux )
{
	uint8_t axis_0, axis_1, axis_linear;
	long int deltaA, deltaB, velA, velB, velocidad;

	velocidad = pl_block_aux->feed_rate[0];

	if (pl_block_aux->steps[X_AXIS] != 0 && pl_block_aux->steps[Y_AXIS] != 0 && pl_block_aux->steps[Z_AXIS] != 0 )
	{
		velA = velB = velocidad;
	}
	else
	{
		if (pl_block_aux->steps[X_AXIS] == 0)
		{
			axis_0 = Y_AXIS;
			axis_1 = Z_AXIS;
			axis_linear = X_AXIS;
		}
		if (pl_block_aux->steps[Y_AXIS] == 0)
		{
			axis_0 = Z_AXIS;
			axis_1 = X_AXIS;
			axis_linear = Y_AXIS;
		}
		if (pl_block_aux->steps[Z_AXIS] == 0)
		{
			axis_0 = X_AXIS;
			axis_1 = Y_AXIS;
			axis_linear = Z_AXIS;
		}

		deltaA = (pl_block_aux->steps[axis_0]);
		deltaB = (pl_block_aux->steps[axis_1]);

		if ( deltaB > deltaA )
		{
			velB = velocidad;
			velA = (int) ((deltaA * velB)/deltaB);
		}
		if ( deltaA > deltaB )
		{
			velA = velocidad;
			velB = (int) ((deltaB * velA)/deltaA);
		}
		if (deltaA==deltaB)
			velA=velB=velocidad;
	}

	pl_block_aux->feed_rate[axis_0]= velA;
	pl_block_aux->feed_rate[axis_1]= velB;
	pl_block_aux->feed_rate[axis_linear]= velocidad;
}

/**
	@fn uint8_t soft_check_limit( uint8_t axis, uint8_t dir, uint32_t steps)
	@brief Chequea si va a haber un sobrepaso del limite fisico.
 	@details Si el punto donde va a terminar nuestro movimiento supera el limite fisico de alguno de los ejes retorna FALSO
 	@return uint8_t
 */
uint8_t soft_check_limit ( uint8_t axis, uint8_t dir, uint32_t steps){

	int aux,position;
	if(sys.state!=S_AUTO)
		position=sys.position[axis];
	else
		position=sys.planner_position[axis];

	if(axis==Z_AXIS)
	{
		dir++;
		dir%=2;
	}
	if(dir == CW){
		aux = (steps + position + sys.new_Home_Ref[axis]);
		if(aux > settings.max_travel_steps[axis])
			return FALSE;
	}
	if (dir == CCW){
		aux = ( position + sys.new_Home_Ref[axis] - steps);
		if( aux < 0)
			return FALSE;
	}
	return TRUE;
}
