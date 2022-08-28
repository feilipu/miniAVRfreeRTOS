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
# Target options
TARGET=main.hex

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

AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET)
AVRDUDE_FLAGS = -p $(MCU) -b $(AVRDUDE_BAUDRATE)
AVRDUDE_FLAGS += -P $(AVRDUDE_PORT)
AVRDUDE_FLAGS += -c $(AVRDUDE_PROGRAMMER)
AVRDUDE_VERBOSE = -v -v

CFLAGS = -mmcu=$(MCU)
CFLAGS += -funsigned-char -funsigned-bitfields -DDEBUG
CFLAGS += -DF_CPU=$(F_CPU) 
CFLAGS += $(INC_PATH)
CFLAGS += -O2 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums
CFLAGS += -mrelax -Wall -Wstrict-prototypes
CFLAGS += -std=gnu11 -Wundef
CFLAGS += -MMD -MP -MF .dep/$(@F).d
CFLAGS += -DBMP180_API

LFLAGS = -mmcu=$(MCU)
LFLAGS += -Wl,-Map=$(MAPFILE),--cref,--gc-sections
LFLAGS += -lm

OBJECTS := $(addprefix  obj/,$(SOURCES:.c=.o))
LINKED := $(addprefix obj/, $(TARGET:.hex=.elf))
BINARY := $(addprefix obj/, $(TARGET:.hex=.bin))
MAPFILE := $(addprefix obj/, $(TARGET:.hex=.map))
SYMFILE := $(addprefix obj/, $(TARGET:.hex=.sym))
LSSFILE := $(addprefix obj/, $(TARGET:.hex=.lss))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "[LD]		$(TARGET)"
	$Qavr-gcc $(LFLAGS) -o $(LINKED) $^
	$Qavr-objcopy -O ihex -R .eeprom $(LINKED) $@
	$Qavr-objcopy -I ihex $(TARGET) -O binary $(BINARY)
	$Qavr-size --format=berkeley $(LINKED)
	$Qavr-nm -n $(LINKED) > $(SYMFILE)
	$Qavr-objdump -h -S $(LINKED) > $(LSSFILE)

obj/%.o: %.c
	@echo "[CC]		$(notdir $<)"
	$Qmkdir -p $(dir $@)
	$Q$(CC) $(CFLAGS) -c -o $@ $<

program: $(TARGET)
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)

clean:
	@echo "Cleaning $(TARGET)"
	$Qrm -f $(TARGET)
	$Qrm -f $(BINARY)
	$Qrm -f $(MAPFILE)
	$Qrm -f $(SYMFILE)
	$Qrm -f $(LSSFILE)
	@echo "Cleaning Objects"
	$Qrm -f *.o
	$Qrm -f $(TARGET)*.hex
	$Qrm -rf obj
	$Qrm -rf .dep

-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)