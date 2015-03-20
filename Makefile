#!/bin/bash
# Engine Library ToolKit (ELT)
# Makefile
CC = gcc
CFLAGS=-Wall
CLIBS=-lGL -lX11 
# archive 
ARCHIVE=ar
DYNAMIC_FLAG=-shared

ifdef ComSpec
	EXE_EXT=.dll
	INCLUDE_PATH = -
	LINK_PATH = 
	LIBS=
	ASSEMBLY_INSTRUCTION = 
	ENVIROMENT_PRE_PROCESSOR= _ENGINE_INTERNAL GLEW_BUILD
else
	EXE_EXT=.so
	INCLUDE_PATH =
	LINK_PATH = 
	LIBS= -lGL -lGLU -lX11 -lcmdlib -lEGL -Xrender lOpenCL
	ASSEMBLY_INSTRUCTION =  $(ARCHIVE) -rcs libcmdlib.a -f *.o 	
	# pre processor
	ENVIROMENT_PRE_PROCESSOR= _ENGINE_INTERNAL GLEW_BUILD
endif

#check if cmdlib exist! otherwise, error! 
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))


CFLAGS=-g -Wall $(DYNAMIC_FLAG) $(ENVIROMENT_PRE_PROCESSOR) $(INCLUDE_PATH) $(LINK_PATH)

# target 
LINK_TARGET=EngineEx$(EXE_EXT)
	

all: $(LINK_TARGET)
	echo -en "Done $(du -h libEngineEx.so)"

$(LINK_TARGET) : $(OBJS)
	$(CC) $(CFLAGS) *.o -o $(LINK_TARGET)  $(LIBS)
	
%.o : %.c
	$(CC) $(CFLAGS) -c $< $(LIBS)

clean:
	rm -f *.o
	echo EveryThing removed
