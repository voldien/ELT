#!/bin/bash

SHELL := /bin/bash
BASE = $(call my-dir)
MAKE := make
RM := rm -rf
MKDIR :=  mkdir -p
CP := cp
ARMCC := arm-linux-gnueabihf-gcc
WINCC := x86_64-w64-mingw32-gcc
CC := gcc
AR := ar

ifdef ComSpec	#	Windows
	TARGETSUFFIX :=.dll
	INCLUDE := -I"include" 
	CLIBS := 
else
	TARGETSUFFIX :=.so
	INCLUDE := -I"include" 
	CLIBS := -lGL -lX11 -lEGL -lXrender -lOpenCL -lpthread -ldl -lrt -lxcb -lX11-xcb -lXrandr -lm
endif

vpath %.c src			#	pattern rule for c source file.
vpath %.h include		#	pattern rule for header file.

sources  = $(wildcard src/*.c)
sources += $(wildcard src/input/*.c)
sources += $(wildcard src/system/*.c)

ifndef ComSpec
sources += $(wildcard src/system/unix/*.c)	# TODO resolve internal directory
endif

sources += $(wildcard src/math/*.c)
sources += $(wildcard src/graphic/*.c)
#sources -= src/main.c 

objects = $(subst .c,.o,$(sources))


CFLAGS :=  -w -Wall -fPIC  $(DEFINE) $(INCLUDE) -DENGINE_INTERNAL=1
TARGET = libEngineEx$(TARGETSUFFIX)
BUILD_DIR := build/					#	
OUTPUT_DIR := build/


all: $(TARGET)
	echo -en "$(TARGET) has succfully been compiled and linked.\n" 
	du -h $(TARGET)



$(TARGET) : CFLAGS += -O2  -msse3
$(TARGET) : $(objects)
	$(MKDIR) build
	$(CC) $(CFLAGS) -shared $(notdir $^) -o build/$@  $(CLIBS)
	

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $(notdir $(subst .c,.o,$^))


debug : CFLAGS += -g -D_DEBUG=1
debug : $(objects)
	$(CC) $(CFLAGS) -shared $(notdir $^) -o build/$(TARGET)  $(CLIBS)


arm : CFLAGS += -marm -O2
arm : CFLAGS += -L"/usr/lib/"
arm : CC := $(ARMCC)
arm : $(objects)
	$(ARMCC) $(CFLAGS)  -shared $(notdir $^ ) -o  build/$(TARGET) # $(CLIBS)



x86 : CFLAGS += -m32 -O2
x86 : $(objects)
	$(CC) $(CFLAGS)  $(notdir $(objects)) -o $(TARGET) $(CLIBS)


x64 : CFLAGS += -m64 -O2
x64 :$(objects)
	$(CC) $(CFLAGS)  $(notdir $(objects)) -o $(TARGET) $(CLIBS)


.PHONY : static
static : TARGETSUFFIX :=.a
static : $(objects)
	$(AR) -rcs $(TARGET) -f $(notdir $(objects))


.PHONY : win32
win32 : CFLAGS += -mwin32 -municode -mwindows -I"External/OpenCL/Include" -I"/usr/x86_64-w64-mingw32/include" -DDLLEXPORT=1 -DEX_INCLUDE_DIRECTX=1 
win32 : sources += $(wildcard /src/system/Win32/*.c)
win32 : TARGET := EngineEx32.dll
win32 : CC := $(WINCC)
win32 : $(objects)
	$(WINCC) $(CFLAGS)  $(objects) -o $(TARGET) $(CLIBS)


.PHONY : win64
win64 : CFLAGS += -municode -mwindows -I"/usr/x86_64-w64-mingw32/include" -DDLLEXPORT=1 -DEX_INCLUDE_DIRECTX=1
win32 : sources += $(wildcard /src/system/Win32/*.c)
win64 : TARGET := EngineEx64.dll
win64 : CC ;= $(WINCC)
win64 : $(objects)
	$(WINCC) $(CFLAGS)  $(objects) -o $(TARGET) $(CLIBS)


.PHONY : nacl
nacl : 
	$(MAKE) -C ./port/nacl/ $@
#	make V=1 -f port/nacl/Makefile $@

.PHONY : pnacl
pnacl : 
	$(MAKE) -C ./port/nacl/ $@


.PHONY : android
android :
	$(MAKE) -C ./port/android/jni/
		


.PHONY : avr
avr : $(objects)
	

# make sure that all dependecy are installed. 
.PHONY : dependency 
dependency :
	sudo apt-get install mesa-common-dev libx11-dev libx11-xcb-dev libegl1-mesa-dev libxrandr-dev libgles2-mesa-dev


install :
	echo -en "installing ELT"
	sudo $(MKDIR) /usr/include/ELT
	sudo $(MKDIR) /usr/include/ELT/input
	sudo $(MKDIR) /usr/include/ELT/system
	sudo $(MKDIR) /usr/include/ELT/system/android/
	sudo $(MKDIR) /usr/include/ELT/graphic
	sudo $(CP) include/*.h /usr/include/ELT/
	sudo $(CP) include/input/*.h /usr/include/ELT/input/
	sudo $(CP) include/system/*.h /usr/include/ELT/system/
	sudo $(CP) include/system/android/*.h /usr/include/ELT/system/android/
	sudo $(CP) include/graphic/*.h /usr/include/ELT/graphic
	sudo $(CP) build/$(TARGET) /usr/lib/$(TARGET)

	
uninstall : 
	


clean:
	$(RM) *.o
	$(RM) src/*.o
	$(RM) src/input/*.o
	$(RM) src/system/*.o	
	echo -en "every object files removed"

