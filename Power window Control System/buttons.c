#include "buttons.h"
void buttons_init(uint16 REG)
{
	 GPIO_PORTB_CR_R |= (1 << REG);    // Allow changes to the corresponding pin
    GPIO_PORTB_DIR_R &= ~(1 << REG);  // Set as input
    GPIO_PORTB_DEN_R |= (1 << REG);   // Enable digital function
	if(REG!=5 || REG!=6)
	{
    GPIO_PORTB_PUR_R |= (1 << REG);   // Enable pull-up resistor
	}
}