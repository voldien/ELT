#!/bin/bash


BASE := $(call my-dir)
SHELL := bash
OUTPUT_DIR := 
MAKE := make
RM := rm -rf
MKDIR :=  mkdir -p
CP := cp

ARMCC := arm-linux-gnueabihf-g++
WINCC := x86_64-w64-mingw32-c++
CPP := g++
ARMCC := arm-linux-gnueabihf-gcc
WINCC := x86_64-w64-mingw32-gcc
CLANGCC := clang
CC := gcc
SWIG := swig3.0

AR := ar
CPPFLAGS := -I"/usr/local/include" -I"./../../include/" -I"/usr/include/python2.7/" -fPIC  -DNX_DISABLE_FLUIDS -DCORELIB -DNX32 -DLINUX -DUNIX -DGLM_FORCE_RADIANS


VPATH := ./../../include  ./../../ ./../../src .


sources  = $(wildcard ./../../src/*.c)
header = $(wildcard ./../../include/*.h)
#header = $(wildcard ./../../include/input/*.h)
#header = $(wildcard ./../../include/system/*.h)
interface = $(notdir $(subst .h,.i,$(header)) )
cxxsource = $(notdir $(subst .i,.cxx,$(interface)) )
object = $(notdir $(subst .cxx,.o,$(cxxsource)) )


#
all :  $(copy) $(object) $(sources) $(cxxsource)
	$(CC) $(CPPFLAGS) -shared $(object) -o libEngineEx.so

#
%.o : %.cxx
	$(CC) $(CPPFLAGS) -c $^ -o $@ 

#
%.cxx : %.i
	$(SWIG) -module elt -I"/usr/include" $(macro) -cpperraswarn -python -o $@ $^ 

#
%.i : %.h
	$(CC) $(CPPFLAGS) -E $^ > $(notdir $(subst .h,.i, $^) )
	
	#cp $^ $(notdir $(subst .h,.i, $^) )
	#sed -i 's/.h"/.i"/g' $@





PARSEHEADER := echo ` for f in *.h; do mv "$$f" "$${f%%.*}.i"; done `
.PHONY : copy
copy : $(header)
	$(CP) -r ./../../include/*.h .
	$(PARSEHEADER)
	 sed -i 's/.h"/.i"/g' $(interface)
	#$(CPP) $(CPPFLAGS) -E $^
	# for f in *.h; do mv -i "$f" "${f%%.*}.i" ; done



clean:
	rm *.i
	rm *.o
