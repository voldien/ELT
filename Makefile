#!/bin/bash

RM := rm -rf
MKDIR :=  mkdir -p
CP := cp
ARMCC := gcc-arm-linux-gnueabi-gcc 
CC := gcc
AR := ar

ifdef ComSpec
	TARGETSUFFIX :=.dll
	INCLUDE = 
	CLIBS :=
	ASSEMBLY_INSTRUCTION = 
	DEFINE := -DENGINE_INTERNAL=1
else
	TARGETSUFFIX := .so
	INCLUDE := -I"include" 
	CLIBS := -lGL -lX11 -lEGL -lXrender -lOpenCL -lpthread -ldl -lrt -lxcb -lX11-xcb -lXrandr
	ASSEMBLY_INSTRUCTION :=  $(AR) -rcs libcmdlib.a -f *.o

	DEFINE := -DENGINE_INTERNAL=1
endif

vpath %.c src			#	pattern rule for c source file.
vpath %.h include		#	pattern rule for header file.
vpath %.o .			#	pattern rule for machine code file. 

sources  = $(wildcard src/*.c)
sources += $(wildcard src/input/*.c)
sources += $(wildcard src/system/*.c)
sources += $(wildcard src/system/unix/*.c)
#sources -= src/main.c 
objects = $(subst %.c,%.o,$(sources))


CFLAGS := -O2 -fPIC  $(DEFINE) $(INCLUDE)
TARGET := libEngineEx$(TARGETSUFFIX)			# target
BUILD_DIR := build/					#	


all: $(TARGET)
	echo -en "$(TARGET) has succfully been compiled and linked $(du -h $(TARGET))"


$(TARGET) : $(objects)
	$(CC) $(CFLAGS) -shared $^ -o build/$@  $(CLIBS)
	

%.o : %.c %.h 
	$(CC) $(CFLAGS) -c $^ $(CLIBS)



debug : $(sources)
	$(CC) $(INCLUDE) -fPIC -g -D_DEBUG=1 -c  $^ $(CLIBS)
	$(CC) $(INCLUDE) -fPIC -shared $(objects) -o $(TARGET) $(CLIBS)


arm : $(sources)
	$(ARMCC) $(CFLAGS) -marm -shared -c $^ $(CLIBS)
	$(ARMCC) $(CFLAGS) -marm -shared $(objects) $(CLIBS) 


x86 : $(sources)
	$(CC) -fPIC -O3 -c $^ $(CLIBS)

x64 : $(sources)
	$(CC) $(CFLAGS) -fPIC -m64 -O3 -c $^ $(CLIBS) 
	$(CC) $(CFLAGS) -fPIC -m64 -O3 $(objects) -o $(TARGET) $(CLIBS)

static_library : $(sources)
	$(CC) $(CFLAGS) 




install :
	sudo $(MKDIR) /usr/include/ELT
	sudo $(MKDIR) /usr/include/ELT/input
	sudo $(MKDIR) /usr/include/ELT/system
	sudo $(MKDIR) /usr/include/ELT/system/android/
	sudo $(CP) include/*.h /usr/include/ELT/
	sudo $(CP) include/input/*.h /usr/include/ELT/input/
	sudo $(CP) include/system/*.h /usr/include/ELT/system/
	sudo $(CP) include/system/android/*.h /usr/include/ELT/system/android/
	sudo $(CP) build/libEngineEx.so /usr/lib/libEngineEx.so

uninstall : 	


clean:
	$(RM) *.o
	$(RM) src/*.o
	$(RM) src/input/*.o
	$(RM) src/system/*.o	
	echo -en "EveryThing removed"
