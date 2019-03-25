/*
 * Planner.h
 *
 *  Created on: 25/10/2015
 *      Author: Julieta
 */

#ifndef INC_PLANNER_H_
#define INC_PLANNER_H_


typedef struct
{
  uint8_t direction_bits[N_AXIS];		// direction of each axis
  uint16_t feed_rate[N_AXIS];			// feedrate of each axis in MM/Min?
  int  steps[N_AXIS];    			// Step count along each axis
  uint8_t max_step_flag[N_AXIS]; 		// The maximum step axis count and number of steps required to complete this block.
  uint8_t programFlow;
} plan_block_t;

#define		BUFF_TAM		80
#define		MICROPASOS		20			//!< cantidad minima de pasos, equivale 0.1mm
#define		MM_PER_SEGMENT	2			//!<
#define		PI				3.141592


uint8_t plan_move_manual(void);
uint8_t plan_move_serial_manual(void);
void goHome(uint8_t);
uint8_t setHome(uint8_t);

void plan_reset(void);
uint8_t mc_line ( float*, float , uint8_t );
void mc_arc( float *, float *, float *, float , float , uint8_t , uint8_t , uint8_t , uint8_t , uint8_t );
uint8_t pl_ckeck_buffer (void);
void pl_init (void);
void splindle_control (uint8_t);
void asignar_velocidades ( plan_block_t* );

#endif /* INC_PLANNER_H_ */
