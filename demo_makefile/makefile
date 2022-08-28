# Make file based on 
# https://github.com/peakhunt/freertos_atmega328p/blob/master/Makefile
# and modified by Tiago Lobao
#
# 
# make (default) = compile project
#
# make clean = delete all binaries
#
# make program = flash through AVRDUDE
#

# ---------------------------------------
# -------- MAKEFILE USER DEFINES --------
# ---------------------------------------

# ---------------------------------------
# Microcontroller specific
MCU=atmega328p
F_CPU=16000000UL

# ---------------------------------------
# Directiory for the freeRTOS
FREERTOS_DIR=..

# ---------------------------------------
# Flashing options
# using standard arduino bootloader
AVRDUDE_PROGRAMMER = arduino
AVRDUDE_PORT = COM3
AVRDUDE_BAUDRATE = 115200

# ---------------------------------------
# Target file name options
TARGET=main

# ---------------------------------------
# compiler / programmer options
CC=avr-gcc
AVRDUDE = avrdude

# ---------------------------------------
# Sources/includes to be used
FREERTOS_SRC  :=  \
	$(FREERTOS_DIR)/list.c \
	$(FREERTOS_DIR)/timers.c \
	$(FREERTOS_DIR)/stream_buffer.c \
	$(FREERTOS_DIR)/heap_3.c \
	$(FREERTOS_DIR)/event_groups.c \
	$(FREERTOS_DIR)/hooks.c \
	$(FREERTOS_DIR)/port.c \
	$(FREERTOS_DIR)/queue.c \
	$(FREERTOS_DIR)/tasks.c


SOURCES :=	$(FREERTOS_SRC) \
	main.c

INC_PATH=-I$(FREERTOS_DIR) -I./


# ---------------------------------------
# ---------- MAKEFILE CODE --------------
# ---------------------------------------

AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
AVRDUDE_FLAGS = -p $(MCU) -b $(AVRDUDE_BAUDRATE)
AVRDUDE_FLAGS += -P $(AVRDUDE_PORT)
AVRDUDE_FLAGS += -c $(AVRDUDE_PROGRAMMER)

MCUFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU)

CFLAGS = $(MCUFLAGS)  $(INC_PATH) -c $(SOURCES)
LFLAGS = $(MCUFLAGS) -o $(TARGET).elf *.o

# ---------------------------------------
# Optimization choice
# This will avoid not used code and guarantee proper delays
CFLAGS += -ffunction-sections -O2
LFLAGS += -Wl,--gc-sections

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS)
	$(CC) $(LFLAGS)
	avr-objcopy -O ihex $(TARGET).elf $(TARGET).hex

program:
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)

clean:
	@echo "Cleaning $(TARGET)"
	rm -f $(BINARY)
	rm -f $(MAPFILE)
	rm -f $(SYMFILE)
	rm -f $(LSSFILE)
	@echo "Cleaning Objects"
	rm -f *.o
	rm -f $(TARGET)*.hex
	rm -f $(TARGET)*.elf
	rm -rf obj
	rm -rf .dep
