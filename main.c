////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////    main.c
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <avr/io.h>
#include <avr/interrupt.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/*-----------------------------------------------------------*/

static void TaskBlinkRedLED(void *pvParameters); // Main Arduino Mega 2560 (Red) LED Blink

static void TaskBlinkGreenLED(void *pvParameters); // Main Arduino Uno 328p (Green) LED Blink

/*-----------------------------------------------------------*/

/* Main program loop */
int main(void) __attribute__((OS_main));

int main(void)
{
    xTaskCreate(
		TaskBlinkRedLED
		,  (const portCHAR *)"RedLED" // Main Arduino Mega 2560, Freetronics EtherMega (Red) LED Blink
		,  256				// Stack Size
		,  NULL
		,  3				// Priority
		,  NULL ); // */

    xTaskCreate(
		TaskBlinkGreenLED
		,  (const portCHAR *)"GreenLED" // Main Arduino Uno 328p (Green) LED Blink
		,  256				// Stack Size
		,  NULL
		,  3				// Priority
		,  NULL ); // */

	vTaskStartScheduler();
}
/*-----------------------------------------------------------*/

static void TaskBlinkRedLED(void *pvParameters) // Main Red LED Flash
{
    (void) pvParameters;
    TickType_t xLastWakeTime;
	/* The xLastWakeTime variable needs to be initialised with the current tick
	count.  Note that this is the only time we access this variable.  From this
	point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
	API function. */
	xLastWakeTime = xTaskGetTickCount();

	DDRB |= _BV(DDB7);

    for(;;)
    {
    	PORTB |=  _BV(PORTB7);       // main (red IO_B7) LED on. EtherMega LED on
		vTaskDelayUntil( &xLastWakeTime, ( 128 / portTICK_PERIOD_MS ) );

		PORTB &= ~_BV(PORTB7);       // main (red IO_B7) LED off. EtherMega LED off
		vTaskDelayUntil( &xLastWakeTime, ( 384 / portTICK_PERIOD_MS ) );
    }
}
/*-----------------------------------------------------------*/

static void TaskBlinkGreenLED(void *pvParameters) // Main Green LED Flash
{
    (void) pvParameters;
    TickType_t xLastWakeTime;
	/* The xLastWakeTime variable needs to be initialised with the current tick
	count.  Note that this is the only time we access this variable.  From this
	point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
	API function. */
	xLastWakeTime = xTaskGetTickCount();

	DDRB |= _BV(DDB5);

    for(;;)
    {
    	PORTB |=  _BV(PORTB5);       // main (red PB5) LED on. Arduino LED on
		vTaskDelayUntil( &xLastWakeTime, ( 128 / portTICK_PERIOD_MS ) );

		PORTB &= ~_BV(PORTB5);       // main (red PB5) LED off. Arduino LED off
		vTaskDelayUntil( &xLastWakeTime, ( 384 / portTICK_PERIOD_MS )  );
    }
}
/*-----------------------------------------------------------*/
