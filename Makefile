#!/bin/bash
# Makefile
CC = gcc
# archive 
ARCHIVE=ar

ifdef ComSpec
	TARGETSUFFIX :=.dll
	INCLUDE = -
	LINK_PATH := 
	CLIBS :=
	ASSEMBLY_INSTRUCTION = 
	DEFINE := -DENGINE_INTERNAL=1
else
	TARGETSUFFIX := .so
	INCLUDE := -I"include" 
	CLIBS= -lGL -lX11 -lEGL -lXrender -lOpenCL -lpthread -ldl -lrt -lxcb -lX11-xcb -lXrandr
	ASSEMBLY_INSTRUCTION =  $(ARCHIVE) -rcs libcmdlib.a -f *.o 	

	DEFINE := -DENGINE_INTERNAL=1	
endif

vpath %.c src			#	pattern rule for c source file.
vpath %.h include		#	pattern rule for header file.
vpath %.o .			#	pattern rule for machine code file. 


SRCS  = $(wildcard src/*.c)
SRCS += $(wildcard src/input/*.c)
SRCS += $(wildcard src/system/*.c)
SRCS += $(wildcard src/system/unix/*.c)
SRCS -= src/main.c 
OBJS = $(subst %.c,%.o,$(SRCS))


CFLAGS= -O3 -fPIC  $(DEFINE) $(INCLUDE) $(LINK_PATH)


TARGET=libEngineEx$(TARGETSUFFIX)			# target
	

all: $(TARGET)
	echo -en "$(TARGET) has succfully been compiled and linked $(du -h $(TARGET))"

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -shared $^ -o build/$@  $(CLIBS)
	
%.o : %.c %.h 
	$(CC) $(CFLAGS) -c $^ $(CLIBS)



debug : 
	$(CC) $(INCLUDE) -fPIC -g -c  $(SRCS) $(CLIBS)
	$(CC) $(INCLUDE) -fPIC -shared  $(SRCS) -o $(TARGET) $(CLIBS)


arm : $(SRCS)
	

x86 : $(SRCS)
	$(CC) -fPIC -O3 -c $^ $(CLIBS)

x64 : $(SRCS)
	$(CC) $(CFLAGS) -fPIC -m64 -O3 -c $^ $(CLIBS) 
	$(CC) $(CFLAGS) -fPIC -m64 -O3 $(OBJS) -o $(TARGET) $(CLIBS)

static_library : $(SRCS)
	$(CC) $(CFLAGS) 




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
	rm *.o
	rm -f src/*.o
	rm src/input/*.o
	rm src/system/*.o	
	echo -en "EveryThing removed"
