#==============================================================================
# Makefile NIIET K1921VG015
# Created by NIIET
# Modified by blackw2012 04.07.2025
# free to use
#==============================================================================
TARGET_NAME = vg015_test

COMPILER_PATH 	= /opt/vg015/xpack-riscv-none-elf-gcc-13.2.0-2/bin/
OPENOCD_PATH	= /opt/vg015/xpack-openocd-k1921vk-0.12.0-k1921vk/bin/openocd

SOURCES_PATH 	= ./platform/source/
LIBS_PATH		= $(COMPILER_PATH)../riscv-none-elf/lib/rv32imfc_zicsr/ilp32f/
ADD_LIBS_PATH   = $(COMPILER_PATH)../lib/gcc/riscv-none-elf/13.2.0/rv32imfc_zicsr/ilp32f/
INC_PATH 		= ./platform/include/
LINKER_PATH  	= ./platform/ldscripts/
BUILD_NAME		= build
BUILD_PATH  	= ./$(BUILD_NAME)



ELF_O_FILES := $(patsubst %.c, %.o, $(wildcard *.c)) $(patsubst %.c, %.o,$(wildcard $(SOURCES_PATH)/*.c)) $(patsubst %.S, %.o, $(wildcard $(SOURCES_PATH)/*.S))


			
INCLUDE_FOLDER = -I$(INC_PATH)

LIBS = -L$(LINKER_PATH) -L$(LIBS_PATH) -L$(ADD_LIBS_PATH)
LIBS_ACR = -lc_nano -lg_nano -lgcc

LD_SRC := $(LINKER_PATH)/k1921vg015_flash.ld
MARCH := rv32imfc_zicsr
MABI := ilp32f
LD_FLAGS = -Map=$(BUILD_PATH)/$(TARGET_NAME).map -static -march=$(MARCH) -melf32lriscv  $(LIBS)  $(LIBS_ACR)
DEFINES = -D SYSCLK_HSE -D HSECLK_VAL=16000000 -D RETARGET -D CKO_HSE

export RISCV-GCC	 ?= $(CROSS_PREFIX)gcc -c -Wall -O0 -g -ggdb3 $(DEFINES) -march=$(MARCH) -mabi=$(MABI) $(INCLUDE_FOLDER) -static -std=gnu99 $(LIBS) $(LIBS_ACR)
export CROSS_PREFIX  ?= $(COMPILER_PATH)riscv-none-elf-
export RISCV-AS 	 ?= $(CROSS_PREFIX)as -march=$(MARCH) -mno-arch-attr
export RISCV-LD 	 ?= $(CROSS_PREFIX)ld
export RISCV-OBJDUMP ?= $(CROSS_PREFIX)objdump -S
export RISCV-OBJCOPY ?= $(CROSS_PREFIX)objcopy
export RISCV-SIZE 	 ?= $(CROSS_PREFIX)size

all: header make_build clean $(BUILD_PATH)/$(TARGET_NAME).elf $(BUILD_PATH)/$(TARGET_NAME).dump hex size

make_build:
	-mkdir $(BUILD_NAME)
	-mkdir $(BUILD_NAME)/platform
	-mkdir $(BUILD_NAME)/platform/source

help:
	echo "help:\nmake all\nclean\nload"

header:
	echo "NIIET K1921VG015 MAKEFILE v.1.0 "$^""

%.o: %.c
	echo "COMPILE "$^""
	$(RISCV-GCC) $^ -o $(BUILD_PATH)/$@
	echo "...DONE"

%.o: %.S
	echo "ASSEMBLY "$^"" 
	$(RISCV-GCC) $^ -o $(BUILD_PATH)/$@
	echo "...DONE"

%.elf: $(ELF_O_FILES)
	echo "LINK "$^"" 
	$(RISCV-LD) -o $@ -L$(LINKER_PATH) -T $(LD_SRC) $(patsubst %.o, $(BUILD_PATH)/%.o, $^) $(LD_FLAGS)
	echo "...DONE" 

%.dump: %.elf
	echo "DUMP "$^"" 
	$(RISCV-OBJDUMP) $^ > $@
	echo "...DONE"

size: $(BUILD_PATH)/$(TARGET_NAME).elf
	echo "~~SIZE~~ """ 
	$(RISCV-SIZE) $^

clean:
	echo "CLEANING "$^""
	rm -rf *.o
	rm -rf *.elf
	rm -rf *.hex
	echo "...DONE"

hex:
	echo "HEX "
	$(RISCV-OBJCOPY) -O ihex $(BUILD_PATH)/$(TARGET_NAME).elf $(BUILD_PATH)/$(TARGET_NAME).hex
	echo "...DONE"

upload-jlink:
	$(OPENOCD_PATH) -f interface/jlink.cfg -f target/k1921vg015.cfg -c "init; reset halt; program $(BUILD_PATH)/$(TARGET_NAME).hex verify reset; exit"

upload-bp:
	$(OPENOCD_PATH) -f ../blueprog.cfg -f target/k1921vg015.cfg -c "init; reset halt; program $(BUILD_PATH)/$(TARGET_NAME).hex verify reset; exit"


