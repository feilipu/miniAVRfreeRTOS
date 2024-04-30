# Description

AVR ATmega port of freeRTOS. A port of freeRTOS configured to use the Watchdog Timer on AVR ATmega devices and will operate with almost any classic Arduino device from Arduino, SeeedStudio, Sparkfun, Freetronics or Pololu.

The [Goldilocks Analogue story of adding a dual channel DAC to a 1284p classic Arduino board is told here](https://feilipu.me/?s=Goldilocks+Analogue).
The [Goldilocks Analogue - Kickstarter Campaign](https://www.kickstarter.com/projects/feilipu/goldilocks-analogue-classic-arduino-audio-superpow/) was successfully funded. 
It was also a Hackaday Prize 2015 Quarter Finalist.

![Goldilocks Analogue](https://a.fsdn.com/con/app/proj/avrfreertos/screenshots/Title%20Image.JPG "Goldilocks Analogue")

The first [Goldilocks 1284p story is here](https://feilipu.me/2013/03/08/goldilocks-1284p-arduino-uno-clone/).
Ths idea was launched as a [Pozible campaign in 2013](https://www.pozible.com/goldilocks/).
It was successfully funded and the [Goldilocks](https://freetronics.com/goldilocks/) was developed and supported by Freetronics. 

The main repo has been hosted on [Sourceforge avrfreertos](https://sourceforge.net/projects/avrfreertos/) since 2011, and has been [downloaded over 35,000 times](https://sourceforge.net/projects/avrfreertos/files/stats/timeline?dates=2011-09-22+to+2022-12-31).

Over the past few years freeRTOS development has become increasingly 32-bit orientated, with little change or improvement for the 8-bit world. As such I'm treating this 22nd April 2024 v11.1.0 release as my LTS release.

Going forward Sourceforge will be updated less often and only with major releases.

Please [follow @_feilipu](https://twitter.com/_feilipu) on Twitter.

# Getting Started

To get started, follow the instructions on [freeRTOS & libraries for AVR ATmega](https://feilipu.me/freertos-and-libraries-for-avr-atmega).
Then do some further reading on the [freeRTOS Quick Start Guide](https://www.freertos.org/FreeRTOS-quick-start-guide.html).

For the Arduino platform there is a [freeRTOS Library](https://github.com/feilipu/Arduino_FreeRTOS_Library)
available in the Arduino IDE Library manager, or by directly downloading the ZIP file and importing it into your Arduino IDE.

# Features
The freeRTOS scheduler can be driven by any of the AVR ATmega timers, down to one millisecond (or less) time slices, depending on the application requirements.
By using the Watchdog Timer for scheduling no externally useful system resources are consumed, but time slicing is limited to 15 millisecond increments.
Generally, I use the freeRTOS scheduler for loose timing (15ms) and hardware timers for tight (microsecond) timing, but each application is different.

FreeRTOS has a multitude of configuration options, which can be specified from within the FreeRTOSConfig.h file., but some sensible defaults have been selected.

The AVR Watchdog Timer is configured to generate 30ms time slices, but Tasks that finish before their allocated time will hand execution back to the Scheduler.
Time slices can be selected from 15ms up to 500ms. Slower time slicing can allow the Arduino MCU to sleep for longer, without the complexity of a Tickless idle.

Note that Timer resolution is affected by integer math division and the time slice selected. Trying to measure 100ms accurately, using a 60ms time slice for example, won't work.

Watchdog period options:
* WDTO_15MS
* WDTO_30MS
* WDTO_60MS
* WDTO_120MS
* WDTO_250MS
* WDTO_500MS

There are [multiple options for configuring the heap in freeRTOS](https://www.freertos.org/a00111.html). Please read the freeRTOS descriptions for the appropriate solution relevant to the application.
Heap 3 has been implemented for this repository.

# Compatibility

  * ATmega328 @ 16MHz : Arduino UNO, Arduino Duemilanove, Arduino Diecimila, etc.
  * ATmega328 @ 16MHz : Adafruit Pro Trinket 5V, Adafruit Metro 328, Adafruit Metro Mini
  * ATmega328 @ 16MHz : Seeed Studio Stalker
  * ATmega328 @ 16MHz : Freetronics Eleven
  * ATmega328 @ 12MHz : Adafruit Pro Trinket 3V
  * ATmega32u4 @ 16MHz : Arduino Leonardo, Arduino Micro, Arduino Yun, Teensy 2.0
  * ATmega32u4 @ 8MHz : Adafruit Flora, Bluefruit Micro
  * ATmega1284p @ 24.576MHz : Seeed Studio Goldilocks, Seeed Studio Goldilocks Analogue
  * ATmega2560 @ 16MHz : Arduino Mega, Arduino ADK
  * ATmega2560 @ 16MHz : Seeed Studio ADK
  * ATmegaXXXX @ XXMHz : Anything with an ATmega MCU, really.

# Errors

* Stack Overflow: If any stack (for the loop() or) for any Task overflows, there will be a slow LED blink, with 4 second cycle.
* Heap Overflow: If any Task tries to allocate memory and that allocation fails, there will be a fast LED blink, with 100 millisecond cycle.

# Further Reading

The canonical source for information is the [FreeRTOS Web Site](https://www.freertos.org/).
Within this site, the [Getting Started](https://www.freertos.org/FreeRTOS-quick-start-guide.html) page is very useful.
It is worth having a view from another user, and [manicbug](https://maniacbug.wordpress.com/2012/01/31/freertos/) has some interesting examples.
This AVRfreeRTOS Repository has plenty of examples, ranging from [Blink](https://github.com/feilipu/avrfreertos/blob/master/MegaBlink/main.c) through to a [Synthesiser](https://github.com/feilipu/avrfreertos/tree/master/GA_Synth) for the Goldilocks Analogue.
