/**
 * @file main.c
 * 
 * @author Tiago Lobao
 * 
 * @brief Blink example based on the example for atmega328p
 * https://github.com/feilipu/avrfreertos/blob/master/UnoBlink/main.c
 * 
 */

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/*-----------------------------------------------------------*/
static void TaskBlinkLED(void *pvParameters);
/*-----------------------------------------------------------*/

int main(void)
{
    xTaskCreate(
		TaskBlinkLED
		,  (const char *)"GreenLED"
		,  256
		,  NULL
		,  3
		,  NULL );


	vTaskStartScheduler();    
}

/*-----------------------------------------------------------*/
static void TaskBlinkLED(void *pvParameters) // Main Green LED Flash
{
    (void) pvParameters;
    TickType_t xLastWakeTime;

	xLastWakeTime = xTaskGetTickCount();

	DDRB |= _BV(DDB5);

    for(;;)
    {
    	PORTB |=  _BV(PORTB5);       // main (red PB5) LED on. Arduino LED on
		vTaskDelayUntil( &xLastWakeTime, ( 500 / portTICK_PERIOD_MS ) );

		PORTB &= ~_BV(PORTB5);       // main (red PB5) LED off. Arduino LED off
		vTaskDelayUntil( &xLastWakeTime, ( 500 / portTICK_PERIOD_MS )  );

    }
}

/*---------------------------------------------------------------------------*/