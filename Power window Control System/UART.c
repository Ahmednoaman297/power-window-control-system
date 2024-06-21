/*
* UART.c
*
*  Created on: Oct 27, 2023
*      Author: Ahmedmohamed
*/
#include "common_macros.h"
#include "UART.h"
#include "tm4c123gh6pm.h"
#include "GPIO.h"

void UART_init(void)
{
    GPIO_Port_INIT(PORTA_ID); // Assuming you want to use Port A for UART0
    
    SYSCTL_RCGCUART_R |= 0x01; // Enable clock to UART0
    SYSCTL_RCGCGPIO_R |= 0x01; // Enable clock to Port A
    
    Delay(1); // Delay for clock stabilization
    
    /* UART0 initialization */
    UART0_CTL_R = 0;         // Disable UART0 while setting it up
    UART0_IBRD_R = 104;      // Integer portion of baud-rate divisor for 9600 baud rate
    UART0_FBRD_R = 11;       // Fractional portion of baud-rate divisor for 9600 baud rate
    UART0_CC_R = 0;          // Use system clock
    UART0_LCRH_R = 0x60;     // 8-bit data, no parity, 1 stop bit, no FIFO
    UART0_CTL_R = 0x301;     // Enable UART0 module, Rx and Tx
    
    /* UART0 TX and RX pins use PA0 and PA1. Configure them digital and enable alternate function */
    GPIO_PORTA_DEN_R |= 0x03;    // Set PA0 and PA1 as digital
    GPIO_PORTA_AFSEL_R |= 0x03;  // Use PA0 and PA1 alternate function
    GPIO_PORTA_PCTL_R |= 0x11;   // Configure PA0 and PA1 for UART
}

char UART_Receive_Byte(void)  
{
    char data;
    while((UART0_FR_R & (1<<4)) != 0); // Wait until Rx buffer is not full
    data = UART0_DR_R ;  // Read received data
    return data; 
}

void UART_Send_Byte(unsigned char data)  
{
    while((UART0_FR_R & (1<<5)) != 0); // Wait until Tx buffer not full
    UART0_DR_R= data;  // Send data
}

void UART_Send_String(char *str)
{
    while(*str != '\0')
    {
        UART_Send_Byte(*str);
        str++;
    }
}

void UART_Receive_String(uint8 *str)
{
    uint8 i = 0;
    str[i] = UART_Receive_Byte();
    while(str[i] != '#') // Assuming '#' is the termination character
    {
        i++;
        str[i] = UART_Receive_Byte();
    }
    str[i] = '\0'; // Add null terminator to indicate end of string
}

void Delay(unsigned long counter)
{
    unsigned long i = 0;
    for(i = 0; i < counter; i++);
}
