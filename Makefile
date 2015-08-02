#!/bin/bash

SHELL := /bin/bash
BASE = $(call my-dir)
MAKE := make
RM := rm -rf
MKDIR :=  mkdir -p
CP := cp
ARMCC := arm-linux-gnueabihf-gcc
WINCC := x86_64-w64-mingw32-gcc
CLANGCC := clang
CC ?= gcc
AR := ar

ifdef ComSpec
	INCLUDE := -I"include" 
	CLIBS := 
else
	INCLUDE := -I"include" 
	CLIBS := -lGL -lX11 -lEGL -lXrender -lOpenCL -lpthread -ldl -lrt -lxcb -lX11-xcb -lXrandr -lm
endif
CFLAGS := 


ifeq ($(OS),Windows_NT)
	TARGETSUFFIX :=.dll
    CFLAGS += -D WIN32
    ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
        CFLAGS += -D AMD64
    endif
    ifeq ($(PROCESSOR_ARCHITECTURE),x86)
        CFLAGS += -D IA32
    endif
else
	TARGETSUFFIX :=.so
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CFLAGS += -D LINUX
    endif
    ifeq ($(UNAME_S),Darwin)
        CFLAGS += -D OSX
    endif
    UNAME_P := $(shell uname -p)
    ifeq ($(UNAME_P),x86_64)
        CFLAGS += -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CFLAGS += -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CFLAGS += -D ARM
    endif
endif






VPATH = src src/system src/input src/system/unix src/audio src/math src/graphic src/system/win src/system/android

vpath %.c src
vpath %.h include

sources  = $(wildcard src/*.c)
sources += $(wildcard src/input/*.c)
sources += $(wildcard src/system/*.c)
sources += $(wildcard src/math/*.c)
sources += $(wildcard src/graphic/*.c)

objects = $(notdir $(subst .c,.o,$(sources)) )


CFLAGS += -w -Wall -fPIC  $(DEFINE) $(INCLUDE) -DENGINE_INTERNAL=1
TARGET = libEngineEx$(TARGETSUFFIX)

# debian packaging todo resolve later!
BUILD_DIR := build/
OUTPUT_DIR := build/





.PHONY : nacl
.PHONY : pnacl
.PHONY : linux32
.PHONY : linux64
.PHONY : android
.PHONY : ios
.PHONY : win32 
.PHONY : win64
.PHONY : arm




all: $(TARGET)
	@echo -en "$(TARGET) has succfully been compiled and linked.\n" 
	@du -h build/$(TARGET)



$(TARGET) : CFLAGS += -O3 
$(TARGET) : $(objects)  $(notdir $(subst .c,.o, $(wildcard src/system/unix/*.c) ) ) 
	$(MKDIR) build
	$(CC) $(CFLAGS) -shared $^ -o build/$@  $(CLIBS)
	

%.o : %.c
	@echo -en "($(CC))" $^ "\n" 
	@ $(CC) $(CFLAGS) -c $^ -o $(notdir $(subst .c,.o,$^))


debug : CFLAGS += -g -D_DEBUG=1
debug : $(objects)
	$(CC) $(CFLAGS) -shared $(notdir $^) -o build/$(TARGET)  $(CLIBS)
	@du -h build/$(TARGET)


arm : CFLAGS += -marm -O3
arm : CFLAGS += -L"/usr/lib/"
arm : CC := $(ARMCC)
arm : $(objects)
	$(ARMCC) $(CFLAGS)  -shared $(notdir $^ ) -o  build/$(TARGET) # $(CLIBS)



x86 : CFLAGS += -m32 -O3
x86 : $(objects)
	$(CC) $(CFLAGS)  $(notdir $(objects)) -o $(TARGET) $(CLIBS)


x64 : CFLAGS += -m64 -O3
x64 :$(objects)
	$(CC) $(CFLAGS)  $(notdir $(objects)) -o $(TARGET) $(CLIBS)


.PHONY : static
static : TARGETSUFFIX :=.a
static : $(objects)
	$(AR) -rcs $(TARGET) -f $(notdir $(objects))



linux32 : CFLAGS += -m32
linux32 : $(objects)
	$(CC) $(CFLAGS) -shared $^ -o $@ $(TARGET) $(CLIBS)

linux64 : CFLAGS += -m64
linux64 : $(objects)
	$(CC) $(CFLAGS) -shared $^ -o build/$(TARGET) $(CLIBS)



CWINCLIBS := -lopengl32 -lgdi32 -lglu32  -lwininet -lws2_32 -lkernel32 -luser32 -lwinmm  -lpsapi -legl -ldbghelp #-lopencl


win32 : CFLAGS += -mwin32 -municode -mwindows -I"External/OpenCL/Include" -I"/usr/x86_64-w64-mingw32/include" -DDLLEXPORT=1  -DDONT_SUPPORT_OPENCL=1
win32 : TARGET := EngineEx32.dll
win32 : CLIBS := $(CWINCLIBS)
win32 : winobjects = 
win32 : CC := $(WINCC)
win32 : $(objects) $(notdir $(subst .c,.o, $(wildcard src/system/win/*.c) ))
	$(WINCC) $(CFLAGS) -shared $^ -o $(TARGET) $(CLIBS)



win64 : CFLAGS += -municode -mwindows -I"External/OpenCL/Include" -I"/usr/x86_64-w64-mingw32/include" -DDLLEXPORT=1   
win64 : sources += $(wildcard src/system/win/*.c)
win64 : TARGET := EngineEx64.dll
win64 : CLIBS := $(CWINCLIBS)
win64 : CC := $(WINCC)
win64 : $(objects)
	$(WINCC) $(CFLAGS)   $^ -o $(TARGET) $(CLIBS)



nacl : 
	$(MAKE) -C ./port/nacl/ $@
#	make V=1 -f port/nacl/Makefile $@


pnacl : 
	$(MAKE) -C ./port/nacl/ $@



android :
	$(MAKE) -C ./port/android/jni/
			

# make sure that all dependecy are installed. 
.PHONY : dependency
dependency :
	sudo apt-get install mesa-common-dev libx11-dev libx11-xcb-dev libegl1-mesa-dev libxrandr-dev libgles2-mesa-dev


install : $(TARGET)
	@echo -en "installing ELT!\n"
	sudo $(MKDIR) /usr/include/ELT
	sudo $(MKDIR) /usr/include/ELT/input
	sudo $(MKDIR) /usr/include/ELT/system
	sudo $(MKDIR) /usr/include/ELT/system/android/
	sudo $(MKDIR) /usr/include/ELT/graphic
	sudo $(MKDIR) /usr/include/ELT/math
	sudo $(CP) include/*.h /usr/include/ELT/
	sudo $(CP) include/input/*.h /usr/include/ELT/input/
	sudo $(CP) include/system/*.h /usr/include/ELT/system/
	sudo $(CP) include/system/android/*.h /usr/include/ELT/system/android/
	sudo $(CP) include/graphic/*.h /usr/include/ELT/graphic/
	sudo $(CP) include/math/*.h /usr/include/ELT/math/
	sudo $(CP) build/$(TARGET) /usr/lib/$(TARGET)

	
uninstall : 
	


clean:
	$(RM) *.o
	@echo -en "every object files removed"

