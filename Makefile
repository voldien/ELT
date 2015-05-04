#!/bin/bash

BASE = $(call my-dir)
MAKE := make
RM := rm -rf
MKDIR :=  mkdir -p
CP := cp
ARMCC := arm-linux-gnueabihf-gcc
WINCC := x86_64-w64-mingw32-c++
CC := gcc
AR := ar

ifdef ComSpec	#	Windows
	TARGETSUFFIX :=.dll
	INCLUDE = 
	CLIBS := 
	DEFINE := -DENGINE_INTERNAL=1
else
	TARGETSUFFIX := .so
	INCLUDE := -I"include" 
	CLIBS := -lGL -lX11 -lEGL -lXrender -lOpenCL -lpthread -ldl -lrt -lxcb -lX11-xcb -lXrandr -lm

	DEFINE := -DENGINE_INTERNAL=1
endif

vpath %.c src			#	pattern rule for c source file.
vpath %.h include		#	pattern rule for header file.

sources  = $(wildcard src/*.c)
sources += $(wildcard src/input/*.c)
sources += $(wildcard src/system/*.c)
sources += $(wildcard src/system/unix/*.c)	# TODO resolve internal directory
sources += $(wildcard src/math/*.c)
#sources -= src/main.c 

objects = $(subst %.c,%.o,$(sources))


CFLAGS :=  -w -Wall -fPIC  $(DEFINE) $(INCLUDE)
TARGET := libEngineEx$(TARGETSUFFIX)			# target
BUILD_DIR := build/					#	
OUTPUT_DIR := build/


all: $(TARGET)
	echo -en "$(TARGET) has succfully been compiled and linked $(du -h $(TARGET))"



$(TARGET) : CFLAGS += -O2
$(TARGET) : $(objects)
	$(MKDIR) build
	$(CC) $(CFLAGS) -shared $^ -o build/$@  $(CLIBS)
	

%.o : %.c
	$(CC) $(CFLAGS) -c $< $(CLIBS)



debug : CFLAGS += -g -D_DEBUG=1
debug : $(objects)
	$(CC) $(CFLAGS)  -c  $^ $(CLIBS)
	$(CC) $(CFLAGS) -shared $(objects) -o build/$(TARGET) $(CLIBS)


arm : CFLAGS += -marm -O2
arm : CFLAGS += -L"/usr/lib/"
arm : $(sources)
	$(ARMCC) $(CFLAGS)  -shared -c $^ $(CLIBS)
	$(ARMCC) $(CFLAGS)  -shared $(objects) $(CLIBS) 



x86 : CFLAGS += -m32 -O2
x86 : $(sources)
	$(CC) $(CFLAGS) -c $^ $(CLIBS)


x64 : CFLAGS += -m64
x64 : $(sources)
	$(CC) $(CFLAGS) -c $^ $(CLIBS) 
	$(CC) $(CFLAGS)  $(objects) -o $(TARGET) $(CLIBS)


static_library : $(objects)
	$(AR) -rcs $(TARGET) -f $^


.PHONY : win32
win32 : CFLAGS += -mwin32 -municode -mwin32 -mwindows -I"/usr/x86_64-w64-mingw32/include" -DDLLEXPORT=1 	# improve later
win32 : sources += $(wildcard /src/system/Win32/*.c)
win32 : TARGET := EngineEx.dll
win32 : $(sources)
	$(WINCC) $(CFLAGS) -c  $^ $(CLIBS)
	$(WINCC) $(CFLAGS)  $(objects) -o $(TARGET) $(CLIBS)


.PHONY : win64
win64 : CFLAGS += -mwin64 -municode -mwin32 -mwindows -I"/usr/x86_64-w64-mingw32/include" -DDLLEXPORT=1	# improve later
win64 : TARGET := EngineEx.dll
win64 : $(sources)
	$(WINCC) $(CFLAGS) -c  $^ $(CLIBS)
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
		


# make sure that all dependecy are installed. 
.PHONY : dependency 
dependency :
	sudo apt-get install mesa-common-dev libx11-dev libx11-xcb-dev libegl1-mesa-dev libxrandr-dev


install :
	echo -en "installing ELT"
	sudo $(MKDIR) /usr/include/ELT
	sudo $(MKDIR) /usr/include/ELT/input
	sudo $(MKDIR) /usr/include/ELT/system
	sudo $(MKDIR) /usr/include/ELT/system/android/
	sudo $(CP) include/*.h /usr/include/ELT/
	sudo $(CP) include/input/*.h /usr/include/ELT/input/
	sudo $(CP) include/system/*.h /usr/include/ELT/system/
	sudo $(CP) include/system/android/*.h /usr/include/ELT/system/android/
	sudo $(CP) build/$(TARGET) /usr/lib/$(TARGET)

	
uninstall : 	


clean:
	$(RM) *.o
	$(RM) src/*.o
	$(RM) src/input/*.o
	$(RM) src/system/*.o	
	echo -en "EveryThing removed"
