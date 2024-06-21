/*
 * DC_motor.h
 *
 *  Created on: Oct 14, 2023
 *      Author: Ahmedmohamed
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "GPIO.h"

#define EN1_PORT_ID  PORTF_ID
#define EN1_PIN_ID   PIN4_ID

#define IN1_PORT_ID  PORTA_ID
#define IN1_PIN_ID   PIN3_ID

#define IN2_PORT_ID  PORTA_ID
#define IN2_PIN_ID   PIN2_ID



void DcMotor_Init(void);
void motor_on_CCW(void);
void motor_on_CW(void);
void motor_stop(void);
void PWM_Init(void) ;
void Delay_ms(int time_ms);
void set_dutycycle(uint16 duty);





#endif /* DC_MOTOR_H_ */
