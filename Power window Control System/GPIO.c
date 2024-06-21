#include "tm4c123gh6pm.h"
#include "common_macros.h"
#include "GPIO.h"



uint8 GPIO_readPin(uint8 port_num, uint8 pin_num) {
  switch (port_num) {
  case PORTA_ID:
    if (BIT_IS_SET( GPIO_PORTA_DATA_R  , pin_num)) {
      return LOGIC_HIGH;
    } else {
      return LOGIC_LOW;
    }
    break;
  case PORTB_ID:
    if (BIT_IS_SET(GPIO_PORTB_DATA_R , pin_num)) {
      return LOGIC_HIGH;
    } else {
      return LOGIC_LOW;
    }
    break;
  case PORTC_ID:
    if (BIT_IS_SET(GPIO_PORTC_DATA_R , pin_num)) {
      return LOGIC_HIGH;
    } else {
      return LOGIC_LOW;
    }
    break;
  case PORTD_ID:
    if (BIT_IS_SET(GPIO_PORTD_DATA_R , pin_num)) {
      return LOGIC_HIGH;
    } else {
      return LOGIC_LOW;
    }
    break;
    
  case PORTE_ID:
    if (BIT_IS_SET(GPIO_PORTE_DATA_R , pin_num)) {
      return LOGIC_HIGH;
    } else {
      return LOGIC_LOW;
    }
    break;
    
  case PORTF_ID:
    if (BIT_IS_SET(GPIO_PORTF_DATA_R , pin_num)) {
      return LOGIC_HIGH;
    } else {
      return LOGIC_LOW;
    }
    break;
    
  }
  return 0;
}



uint8 GPIO_readPort(uint8 port_num) {
  switch (port_num) {
  case PORTA_ID:
    if (GPIO_PORTA_DATA_R  != 0) {
      return GPIO_PORTA_DATA_R ;
    } else {
      return 0;
    }
    break;
  case PORTB_ID:
    if (GPIO_PORTB_DATA_R  != 0) {
      return GPIO_PORTB_DATA_R ;
    } else {
      return 0;
    }
    break;
  case PORTC_ID:
    
    if (GPIO_PORTC_DATA_R  != 0) {
      return GPIO_PORTC_DATA_R ;
    } else {
      return 0;
    }
    break;
  case PORTD_ID:
    if (GPIO_PORTD_DATA_R  != 0) {
      return GPIO_PORTD_DATA_R ;
    } else {
      return 0;
    }
    break;
    
    
    
    
  case PORTE_ID:
    if (GPIO_PORTE_DATA_R  != 0) {
      return GPIO_PORTE_DATA_R ;
    } else {
      return 0;
    }
    break;
    
    
  case PORTF_ID:
    if (GPIO_PORTF_DATA_R  != 0) {
      return GPIO_PORTF_DATA_R ;
    } else {
      return 0;
    }
    break;
    
    
  }
  
  return LOGIC_LOW;
}


void GPIO_writePort(uint8 port_num, uint8 value) {
  switch (port_num) {
  case PORTA_ID:
    GPIO_PORTA_DATA_R = value;
    break;
  case PORTB_ID:
    GPIO_PORTB_DATA_R = value;
    break;
  case PORTC_ID:
    GPIO_PORTC_DATA_R = value;
    break;
    
  case PORTD_ID:
    GPIO_PORTD_DATA_R = value;
    break;
    
  case PORTE_ID:
    GPIO_PORTE_DATA_R = value;
    break;
    
    
  case PORTF_ID:
    GPIO_PORTF_DATA_R = value;
    break;
    
    
  }
}







void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value) {
  
  switch (port_num) {
  case PORTA_ID:
    if (value == LOGIC_HIGH) {
      SET_BIT(GPIO_PORTA_DATA_R, pin_num);
    } else {
      CLEAR_BIT(GPIO_PORTA_DATA_R, pin_num);
    }
    break;
  case PORTB_ID:
    if (value == LOGIC_HIGH) {
      SET_BIT(GPIO_PORTB_DATA_R, pin_num);
    } else {
      CLEAR_BIT(GPIO_PORTB_DATA_R, pin_num);
    }
    break;
  case PORTC_ID:
    if (value == LOGIC_HIGH) {
      SET_BIT(GPIO_PORTC_DATA_R, pin_num);
    } else {
      CLEAR_BIT(GPIO_PORTC_DATA_R, pin_num);
    }
    break;
  case PORTD_ID:
    if (value == LOGIC_HIGH) {
      SET_BIT(GPIO_PORTD_DATA_R, pin_num);
    } else {
      CLEAR_BIT(GPIO_PORTD_DATA_R, pin_num);
    }
    break;
    
    
    
    
  case PORTE_ID:
    if (value == LOGIC_HIGH) {
      SET_BIT(GPIO_PORTE_DATA_R, pin_num);
    } else {
      CLEAR_BIT(GPIO_PORTE_DATA_R, pin_num);
    }
    break;
    
  case PORTF_ID:
    if (value == LOGIC_HIGH) {
      SET_BIT(GPIO_PORTF_DATA_R, pin_num);
    } else {
      CLEAR_BIT(GPIO_PORTF_DATA_R, pin_num);
    }
    break;
    
    
    
    
    
    
    
    
  }
  
}

void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
  /*
  * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
  * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
  * In this case the input is not valid port/pin number
  */
  
  
  
  /* Setup the pin direction as required */
  switch(port_num)
  {
  case PORTA_ID:
    if(direction == PIN_OUTPUT)
    {
      SET_BIT(GPIO_PORTA_DIR_R,pin_num);
    }
    else
    {
      CLEAR_BIT(GPIO_PORTA_DIR_R,pin_num);
    }
    break;
  case PORTB_ID:
    if(direction == PIN_OUTPUT)
    {
      SET_BIT(GPIO_PORTB_DIR_R,pin_num);
    }
    else
    {
      CLEAR_BIT(GPIO_PORTB_DIR_R,pin_num);
    }
    break;
  case PORTC_ID:
    if(direction == PIN_OUTPUT)
    {
      SET_BIT(GPIO_PORTC_DIR_R,pin_num);
    }
    else
    {
      CLEAR_BIT(GPIO_PORTC_DIR_R,pin_num);
    }
    break;
  case PORTD_ID:
    if(direction == PIN_OUTPUT)
    {
      SET_BIT(GPIO_PORTD_DIR_R,pin_num);
    }
    else
    {
      CLEAR_BIT(GPIO_PORTD_DIR_R,pin_num);
    }
    break;
  case PORTE_ID:
    if(direction == PIN_OUTPUT)
    {
      SET_BIT(GPIO_PORTE_DIR_R,pin_num);
    }
    else
    {
      CLEAR_BIT(GPIO_PORTE_DIR_R,pin_num);
    }
    break;
  case PORTF_ID:
    if(direction == PIN_OUTPUT)
    {
      SET_BIT(GPIO_PORTF_DIR_R,pin_num);
    }
    else
    {
      CLEAR_BIT(GPIO_PORTF_DIR_R,pin_num);
    }
    break;
  }
  
}
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
  /*
  * Check if the input number is greater than NUM_OF_PORTS value.
  * In this case the input is not valid port number
  */
  
  
  /* Setup the port direction as required */
  switch(port_num)
  {
  case PORTA_ID:
    GPIO_PORTA_DIR_R = direction;
    break;
  case PORTB_ID:
    GPIO_PORTB_DIR_R = direction;
    break;
  case PORTC_ID:
    GPIO_PORTC_DIR_R = direction;
    break;
  case PORTD_ID:
    GPIO_PORTD_DIR_R = direction;
    break;
  case PORTE_ID:
    GPIO_PORTE_DIR_R = direction;
    break;
  case PORTF_ID:
    GPIO_PORTF_DIR_R = direction;
    break;
  }
  
}
void GPIO_Port_INIT(uint8 PORT_ID)
{
  
  SYSCTL_RCGCGPIO_R|=(1<<PORT_ID);
  while((SYSCTL_PRGPIO_R&(1<<PORT_ID))==0);
  
  switch(PORT_ID)
  {
  case 0:
    GPIO_PORTA_LOCK_R=GPIO_LOCK_KEY;
    
    
    break;
  case 1:
    GPIO_PORTB_LOCK_R=GPIO_LOCK_KEY;
    
    
    
    break;
  case 2:
    GPIO_PORTC_LOCK_R=GPIO_LOCK_KEY;
   
    
    break;
  case 3:
    GPIO_PORTD_LOCK_R=GPIO_LOCK_KEY;
   
    
    break;
  case 4:
    GPIO_PORTE_LOCK_R=GPIO_LOCK_KEY;
    
    
    break;
  case 5:
    GPIO_PORTF_LOCK_R=GPIO_LOCK_KEY;
   
    
    break;
  }
  
}
void RED_LED_Init(void)
{
  GPIO_PORTF_CR_R|=(1<<1);
  GPIO_PORTF_DEN_R|=(1<<1);
  GPIO_PORTF_DIR_R|=(1<<1);
}
void BLUE_LED_Init(void)
{
  GPIO_PORTF_CR_R|=(1<<2);
  GPIO_PORTF_DEN_R|=(1<<2);
  GPIO_PORTF_DIR_R|=(1<<2);
}
void GREEN_LED_Init(void)
{
  GPIO_PORTF_CR_R|=(1<<3);
  GPIO_PORTF_DEN_R|=(1<<3);
  GPIO_PORTF_DIR_R|=(1<<3);
}
void Gpio_init_Allports(void)
{
    GPIO_Port_INIT(PORTF_ID);
  GPIO_Port_INIT(PORTA_ID);
  GPIO_Port_INIT(PORTB_ID);
  GPIO_Port_INIT(PORTC_ID);
  GPIO_Port_INIT(PORTD_ID);  
  GPIO_Port_INIT(PORTE_ID); 
  //
   GPIO_PORTA_CR_R |= 0xFF;
  GPIO_PORTA_DIR_R |= 0xFF;
  GPIO_PORTA_DEN_R |= 0xFF;
  //
  GPIO_PORTB_CR_R |= 0xFF;
  GPIO_PORTB_DIR_R |= 0XFF;
  GPIO_PORTB_DEN_R |= 0XFF;
  //
  GPIO_PORTD_CR_R |= 0xFF;
  GPIO_PORTD_DIR_R |= 0XFF;
  GPIO_PORTD_DEN_R |= 0XFF;
  //
   GPIO_PORTC_CR_R |= 0xFF;
  GPIO_PORTC_DIR_R |= 0XFF;
  GPIO_PORTC_DEN_R |= 0XFF;
  //
 
}
void init_buttons(void)
{
	GPIO_Port_INIT(PORTF_ID);
		GPIO_PORTF_CR_R|=(1<<0);
		GPIO_PORTF_CR_R|=(1<<4);

  GPIO_PORTF_DIR_R &= ~(1<<0);
	  GPIO_PORTF_DIR_R &=~(1<<4);

  GPIO_PORTF_DEN_R |=(1<<0);
	  GPIO_PORTF_DEN_R |=(1<<4);
	GPIO_PORTF_PUR_R |=(1<<0);
		GPIO_PORTF_PUR_R |=(1<<4);

}
