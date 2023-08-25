/*
 * dc.h
 *
 *  Created on: Jun 27, 2023
 *      Author: Dell
 */

#ifndef DC_H_
#define DC_H_
typedef enum  {CW,A_CW,STOP}DcMotor_State;
void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);


#endif /* DC_H_ */
