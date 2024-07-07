/*
 * Copyright (C) 2024 Phillip Stevens  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *
 * This file is NOT part of the FreeRTOS distribution.
 *
 */

/* freeRTOSBoardDefs.h
 *
 * Board (hardware) specific definitions for the AVR boards that I use regularly.
 * This includes
 * Arduino UNO with ATmega328p
 * Goldilocks with ATmega1284p
 * Arduino MEGA with ATmega2560
 *
 * And also Pololu SVP with ATmega1284p
 *
 * This file is NOT part of the FreeRTOS distribution.
 *
 */

#ifndef freeRTOSBoardDefs_h
#define freeRTOSBoardDefs_h

#include <avr/io.h>
#include <avr/wdt.h>

#ifdef __cplusplus
extern "C" {
#endif

// System Tick - Scheduler timer
// Use the Watchdog timer, and choose the rate at which scheduler interrupts will occur.

/* Watchdog Timer is 128kHz nominal, but 120 kHz at 5V DC and 25 degrees is actually more accurate, from data sheet. */

#ifndef portUSE_WDTO
    #define portUSE_WDTO        WDTO_15MS    // portUSE_WDTO to use the Watchdog Timer for xTaskIncrementTick
#endif

/* Watchdog period options:     WDTO_15MS
                                WDTO_30MS
                                WDTO_60MS
                                WDTO_120MS
                                WDTO_250MS
                                WDTO_500MS
                                WDTO_1S
                                WDTO_2S
*/

#if defined( portUSE_WDTO )

    #define configTICK_RATE_HZ  ( (TickType_t)( (uint32_t)128000 >> (portUSE_WDTO + 11) ) )  // 2^11 = 2048 WDT scaler for 128kHz Timer
    #define portTICK_PERIOD_MS  ( (TickType_t) _BV( portUSE_WDTO + 4 ) )
#else
    #warning "Variant configuration must define `configTICK_RATE_HZ` and `portTICK_PERIOD_MS` as either a macro or a constant"
    #define configTICK_RATE_HZ  1
    #define portTICK_PERIOD_MS  ( (TickType_t) ( 1000 / configTICK_RATE_HZ ) )
#endif

#ifdef __cplusplus
}
#endif

#endif // freeRTOSBoardDefs_h
