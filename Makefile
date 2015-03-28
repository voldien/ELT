#!/bin/bash
# Makefile
CC = gcc
# archive 
ARCHIVE=ar

ifdef ComSpec
	EXE_EXT=.dll
	INCLUDE_PATH = -
	LINK_PATH = 
	LIBS=
	ASSEMBLY_INSTRUCTION = 
	ENVIROMENT_PRE_PROCESSOR= _ENGINE_INTERNAL GLEW_BUILD
else
	EXE_EXT=.so
	INCLUDE_PATH = -I"include" 
	CLIBS= -lGL -lGLU -lX11 -lEGL -lXrender -lOpenCL
	ASSEMBLY_INSTRUCTION =  $(ARCHIVE) -rcs libcmdlib.a -f *.o 	
	# pre processor
	ENVIROMENT_PRE_PROCESSOR= -D_ENGINE_INTERNAL=1
endif

#check if cmdlib exist! otherwise, error! 

vpath %.c src
vpath %.h include
vpath %.o .

SRCS := $(wildcard src/*.c)
SRCS += $(wildcard src/Input/*.c)
SRCS += $(wildcard src/System/*.c)

OBJS = $(subst %.c,%.o,$(SRCS))


CFLAGS= -O3 -Wall -fPIC -shared  $(ENVIROMENT_PRE_PROCESSOR) $(INCLUDE_PATH) $(LINK_PATH)

# target 
LINK_TARGET=libEngineEx$(EXE_EXT)
	

all: $(LINK_TARGET)
	echo -en "$(LINK_TARGET) has succfully been compiled and linked $(du -h libEngineEx.so)"

$(LINK_TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o build/$(LINK_TARGET)  $(CLIBS)
	
%.o : %.c
	$(CC) $(CFLAGS) -c $< $(CLIBS)


install :
	sudo mkdir -p /usr/include/ELT
	sudo mkdir -p /usr/include/ELT/input
	sudo mkdir -p /usr/include/ELT/system
	sudo mkdir -p /usr/include/ELT/system/android/
	sudo cp include/*.h /usr/include/ELT/
	sudo cp include/input/*.h /usr/include/ELT/input/
	sudo cp include/system/*.h /usr/include/ELT/system/
	sudo cp include/system/android/*.h /usr/include/ELT/system/android/
	sudo cp build/libEngineEx.so /usr/lib/libEngineEx.so

uninstall : 	

clean:
	rm -f src/*.o
	rm src/input/*.o
	rm src/system/*.o	
	echo EveryThing removed
