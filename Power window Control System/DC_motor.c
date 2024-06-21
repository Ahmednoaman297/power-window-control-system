#include "GPIO.h"
#include "DC_motor.h"
#include <stdint.h>
#include "tm4c123gh6pm.h"


void motor_on_CCW(void)
{
    // SYSCTL_RCGCGPIO_R |= 0x00;   /* enable clock to PORTA */
	   GPIO_PORTA_DIR_R |= (1<<3)|(1<<2);            /* pin digital */
     GPIO_PORTA_DEN_R |= (1<<3)|(1<<2);            /* pin digital */
     GPIO_PORTA_DATA_R |=(1<<2);
		 GPIO_PORTA_DATA_R&=~(1<<3);
}


//Spin motor in other direction by giving IN1 and IN2 signals to L298N

void motor_on_CW(void)
{
	GPIO_PORTA_DIR_R |= (1<<3)|(1<<2);            /* pin digital */
     GPIO_PORTA_DEN_R |= (1<<3)|(1<<2);            /* pin digital */
     GPIO_PORTA_DATA_R |=(1<<3);
		GPIO_PORTA_DATA_R &=~(1<<2);
}
void motor_stop(void)
{

   // SYSCTL_RCGCGPIO_R |= 0x00;   /* enable clock to PORTA */
    GPIO_PORTA_DIR_R |= (1<<3)|(1<<2);            /* pin digital */
    GPIO_PORTA_DEN_R |= (1<<3)|(1<<2);            /* pin digital */
    GPIO_PORTA_DATA_R &= ~(1<<3);  // Set IN1 low
    GPIO_PORTA_DATA_R &= ~(1<<2);  // Set IN2 low

}
void PWM_Init(void) {
    // Enable PWM0 module (Timer0) and GPIO port A
    SYSCTL_RCGCPWM_R |= 2;       // Enable PWM module 0 (Timer0)
	   // SYSCTL_RCGCGPIO_R |= 0x20;      // Enable GPIO port A
  
	SYSCTL_RCC_R |= (1<<20);    /* Enable System Clock Divisor function  */
    SYSCTL_RCC_R|= 0x000E0000; /* Use pre-divider valur of 64 and after that feed clock to PWM1 module*/

    // Configure PWM pins (PA6 for PWM output)
    GPIO_PORTF_AFSEL_R = (1<<2);     // Enable alternate function on PA6
   GPIO_PORTF_PCTL_R &= ~(0x0000F00); // Clear bits for PF4
GPIO_PORTF_PCTL_R |= 0x00000500;    // Set PF4 as PWM output pin
GPIO_PORTF_DEN_R |= (1 << 2);       // Digital pin PF4

    // Configure PWM generator 0, timer mode and down-count mode
    PWM1_3_CTL_R &= ~(1<<0);   /* Disable Generator 3 counter */
  PWM1_3_CTL_R &= ~(1<<1);   /* select down count mode of counter 3*/  
	PWM1_3_GENA_R = 0X0000008C; /* Set PWM output when counter reloaded and clear when matches PWMCMPA */
    PWM1_3_LOAD_R = 5000; // Set PWM period
    PWM1_3_CMPA_R = 0;             /* set duty cyle to to minumum value*/
    PWM1_3_CTL_R =1 ; // start timer PWM generator 0

    // Enable PWM output on PWM0A (PA6)
    PWM1_ENABLE_R =0X40 ;  /* Enable PWM1 channel 6 output */
}
void Delay_ms(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* excute NOP for 1ms */
}
void set_dutycycle(uint16 duty)
{
	PWM1_3_CMPA_R = (5000*duty)/100;
}

