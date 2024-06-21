
#include <stdint.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include "FreeRTOS.h"
#include "common_macros.h"
#include "task.h"
#include "timers.h"
#include "queue.h"
#include "semphr.h" 
#include "DC_motor.h"
#include "UART.h"
#include "buttons.h"

#define QUEUE_LENGTH 1

#define LSUPB 5 //limit switch up
#define LSDPB 6 //limit switch down 
#define PPB1 0   //button up portB
#define PPB2 7  //button down portB
#define DPB1 2   //button up portB
#define DPB2 3  //button down portB
#define SPB 0  //safety button
#define ALPB 4  //autoLOck PORTB
QueueHandle_t xQueue;

SemaphoreHandle_t xmutex;

TaskHandle_t   stop_windowOPEN;
TaskHandle_t   stop_windowCLOSE;

SemaphoreHandle_t binarysemaphore_safety;


void QueueInit(void);
void window_open_driver(void *pvParameters);
void window_close_driver(void *pvParameters);
void window_open_passenger(void *pvParameters);
void window_close_passenger(void *pvParameters);

void safety(void *pvParameters);
void auto_lock(void *pvParameters);
void interrupt_INIT_PORTF(void);
//void interrupt_INIT_PORTB(void);
void UART_TASK(void *pvParameters);
//void GPIOF_Handler(void);


int main(void)
{
	GPIO_Port_INIT(PORTF_ID);
	GPIO_Port_INIT(PORTA_ID);
	GPIO_Port_INIT(PORTB_ID);

buttons_init(LSUPB);
buttons_init(LSDPB);
buttons_init(PPB1);
buttons_init(PPB2);
buttons_init(DPB1);
buttons_init(DPB2);
buttons_init(ALPB);
	/*
	GPIO_PORTB_CR_R |= (1 << ALPB);    // Allow changes to the corresponding pin
    GPIO_PORTB_DIR_R &= ~(1 << ALPB);  // Set as input
    GPIO_PORTB_DEN_R |= (1 << ALPB);   // Enable digital function
	*/
interrupt_INIT_PORTF();

	PWM_Init();
	UART_init();

	
   xmutex = xSemaphoreCreateMutex();
   
   binarysemaphore_safety = xSemaphoreCreateBinary();
    
    
    QueueInit();

//window driver	
       xTaskCreate(window_open_driver, "manual_open", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
        xTaskCreate(window_close_driver, "manual_close", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
	//window passenger
	
	     xTaskCreate(window_open_passenger, "manual_open", configMINIMAL_STACK_SIZE, NULL, 1, &stop_windowOPEN);
        xTaskCreate(window_close_passenger, "manual_close", configMINIMAL_STACK_SIZE, NULL, 1, &stop_windowCLOSE);
			
        xTaskCreate(safety, "safety", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    
			xTaskCreate(auto_lock, "auto_lock", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

xTaskCreate(UART_TASK, "UARTTask", configMINIMAL_STACK_SIZE, NULL, 2, NULL);


    vTaskStartScheduler();

    while (1) {}
}

void QueueInit(void)
{
    xQueue = xQueueCreate(QUEUE_LENGTH, sizeof(uint32));
    if (xQueue == NULL)
    {
        // Queue creation failed
        // Handle error
    }
}

void GPIOF_Handler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  
            
         xSemaphoreGiveFromISR(binarysemaphore_safety, &xHigherPriorityTaskWoken);
					 GPIO_PORTF_ICR_R = 0x11;
   			portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
                  
           
}



void window_open_driver(void *pvParameters)
{
	
//xSemaphoreTake(xmutex, 0);  //mutex
 
	int DO=0;
    while (1)
 {

	//		xSemaphoreTake(xmutex, portMAX_DELAY);

       if(!GPIO_readPin(PORTB_ID,DPB1)){
          Delay_ms(200);
				 if(GPIO_readPin(PORTB_ID,DPB1))
					 
					 {
						 while(GPIO_readPin(PORTB_ID,LSDPB))
	           {
							set_dutycycle(25);
             motor_on_CW();
		         Delay_ms(50);
	            }
				 
				 }
      else
			{
				
			while(GPIO_readPin(PORTB_ID,LSDPB)&& !GPIO_readPin(PORTB_ID,DPB1))
	           {
					 set_dutycycle(25);
             motor_on_CW();
		         Delay_ms(250);
	            }

	  }
		set_dutycycle(0);
			motor_stop();
		
		       xQueueSendToBack(xQueue, &DO, 0);

			
}
		//	 xSemaphoreGive(xmutex);
			  taskYIELD();
}
 }

void window_close_driver(void *pvParameters){
	
	int DC =1;
	//xSemaphoreTake(xmutex, 0);  //mutex

while(1){
	
     //  	xSemaphoreTake(xmutex, portMAX_DELAY);  //mutex

       if(!GPIO_readPin(PORTB_ID,DPB2)){
          Delay_ms(200);
				 if(GPIO_readPin(PORTB_ID,DPB2)) 
				 {
					 while(GPIO_readPin(PORTB_ID,LSUPB))
	           {
							set_dutycycle(25);
             motor_on_CCW();
		         Delay_ms(250);
	            }
						}
      else
			{
				
			while(GPIO_readPin(PORTB_ID,LSUPB)&& !GPIO_readPin(PORTB_ID,DPB2))
	           {
					 set_dutycycle(25);
             motor_on_CCW();
		         Delay_ms(250);
	            }

	  }
		set_dutycycle(0);
			motor_stop();
			       xQueueSendToBack(xQueue, &DC, 0);

    	

	}
 //xSemaphoreGive(xmutex);
			  taskYIELD();
}
}


void window_open_passenger(void *pvParameters){
int PO=2;
//xSemaphoreTake(xmutex, 0);  //mutex

    while (1)
 {
		//	xSemaphoreTake(xmutex, portMAX_DELAY);

       if(!GPIO_readPin(PORTB_ID,PPB1)){
          Delay_ms(200);
				 if(GPIO_readPin(PORTB_ID,PPB1)){
				 while(GPIO_readPin(PORTB_ID,LSDPB))
	           {
							set_dutycycle(25);
             motor_on_CW();
		         Delay_ms(250);
	            }
						}
      else
			{
				
			while(GPIO_readPin(PORTB_ID,LSDPB)&& !GPIO_readPin(PORTB_ID,PPB1))
	           {
					 set_dutycycle(25);
             motor_on_CW();
		         Delay_ms(250);
	            }

	  }
		set_dutycycle(0);
			motor_stop();
		  xQueueSendToBack(xQueue, &PO, 0);
			 

}
// xSemaphoreGive(xmutex);
			   taskYIELD();
}
 }
void window_close_passenger(void *pvParameters){
int PC=3;
//xSemaphoreTake(xmutex, 0);  //mutex

while(1){
       //	xSemaphoreTake(xmutex, portMAX_DELAY);  //mutex

       if(!GPIO_readPin(PORTB_ID,PPB2)){
          Delay_ms(200);
				 if(GPIO_readPin(PORTB_ID,PPB2)){ 
					 while(GPIO_readPin(PORTB_ID,LSUPB))
	           {
							set_dutycycle(25);
             motor_on_CCW();
		         Delay_ms(250);
	            }
						}
      else
			{
				
			while(GPIO_readPin(PORTB_ID,LSUPB)&& !GPIO_readPin(PORTB_ID,PPB2))
	           {
					 set_dutycycle(25);
             motor_on_CCW();
		         Delay_ms(250);
	            }

	  }
		set_dutycycle(0);
			motor_stop();
			 
	       xQueueSendToBack(xQueue, &PC, 0);

	}

// xSemaphoreGive(xmutex);
			   taskYIELD();
}
}

void safety(void *pvParameters)
{
	int SO=4;
	xSemaphoreTake(binarysemaphore_safety, 0);
	while(1)
	{
	xSemaphoreTake(binarysemaphore_safety, portMAX_DELAY);
				set_dutycycle(25);
		motor_on_CCW();
	  Delay_ms(500);
				set_dutycycle(0);
		motor_stop();
			       xQueueSendToBack(xQueue, &SO, 0);

	}
}

void auto_lock(void *pvParameters)
{
	int AL=5;
	while(1)
	{
       if(GPIO_readPin(PORTB_ID,ALPB))
				 {
					 vTaskSuspend(stop_windowOPEN);
					 vTaskSuspend(stop_windowCLOSE);
           xQueueSendToBack(xQueue, &AL, 0);
				 }
				 else if(!GPIO_readPin(PORTB_ID,ALPB))
				 {
					 	vTaskResume(stop_windowOPEN);
					 vTaskResume(stop_windowCLOSE);

				 }
		       

    }
	taskYIELD();
	}

void UART_TASK(void *pvParameters)
{
    int received=0;
    while (1) {
			xQueueReceive(xQueue, &received, pdMS_TO_TICKS(500)) ;
        
					switch(received)
					{
						case 0:
							UART_Send_String("DRIVER OPENES HIS WINDOW\r\n");
							
							break;
case 1:
							UART_Send_String("DRIVER CLOSES HIS WINDOW\r\n");
		
							break;
case 2:
							UART_Send_String("PASSENGER OPENES HIS WINDOW\r\n");

							break;
case 3:
							UART_Send_String("PASSENGER CLOSES HIS WINDOW\r\n");

							break;
case 4:
							UART_Send_String("SAFETY SENSOR OPENED \r\n");

							break;
case 5:
							UART_Send_String("DRIVER OPENED AUTO LOCK\r\n");

							break;
					}
					received=7;
				vTaskDelay(200/portMAX_DELAY);
    }
}

void interrupt_INIT_PORTF(void)
{
    // Initialize GPIO and Interrupts
    GPIO_Port_INIT(PORTF_ID);
    GPIOF->CR = 0x1F;
    GPIOF->AMSEL = 0x00;
    GPIOF->PCTL = 0x0;
    GPIOF->DIR = 0x0E;
    GPIOF->AFSEL = 0x00;
    GPIOF->PUR = 0x11;
    GPIOF->DEN = 0x1F;
    GPIOF->DATA = 0x00;

    GPIOF->ICR = 0x11;
    GPIOF->IM |= 0x11;
    GPIOF->IS |= 0x11;
    GPIOF->IEV &= ~0x11;

    NVIC_EnableIRQ(30); // Enable the interrupt
	
}