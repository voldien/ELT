#!/bin/bash

MKDIR := mkdir -p
RM := rm -rf

#	has to be define manually for now TODO resolve 
NACL_SDK_ROOT ?= $(abspath $(dir $(THIS_MAKEFILE))../..)

GETOS := python $(NACL_SDK_ROOT)/tools/getos.py
OSNAME := $(shell $(GETOS))


PNACL_TC_PATH := $(abspath $(NACL_SDK_ROOT)/toolchain/$(OSNAME)_pnacl)
PNACL_CXX := $(PNACL_TC_PATH)/bin/pnacl-gcc
PNACL_FINALIZE := $(PNACL_TC_PATH)/bin/pnacl-finalize
PNACL_AR := $(PNACL_TC_PATH)/bin/pnacl-ar

NACL_TC_PATH := $(abspath $(NACL_SDK_ROOT)/toolchain/$(OSNAME)_x86_glibc)
NACL_CXX := $(NACL_TC_PATH)/bin/x86_64-nacl-gcc
NACL_AR := $(NACL_TC_PATH)/bin/x86_64-nacl-ar
NACL_RANLIB := $(NACL_TC_PATH)/bin/x86_64-nacl-ranlib


VALID_TOOLCHAINS := pnacl newlib glibc dl pthread


include $(NACL_SDK_ROOT)/tools/common.mk

TARGET :=libEngineEx

CLIBS :=  -lppapi -lm -ldl -lOpenCL -lpthread -lglibc

CFLAGS :=  -fPIC -w -Wall -I"./../../include" -DDONT_SUPPORT_OPENCL=1 -I"$(NACL_SDK_ROOT)/include"	#TODO resolve include dependency 

vpath %.c ./../../src
vpath %.h ./../../include


sources = $(wildcard ./../../src/*.c)
sources += $(wildcard ./../../src/system/*.c)
sources += $(wildcard ./../../src/input/*.c)


objects = $(subst .c,.o, $(sources))



all : $(TARGET).a
	echo -en "finished compiling and link $(du -h $^)"

$(TARGET).a : $(objects)
	$(PNACL_AR) -rcs $(nodir $^) -f $@
	$(NACL_RANLIB) $@

%.o : %.c
	$(PNACL_CXX) -c  $^ -O2 $(CFLAGS) $(CLIBS)


nacl : CLFAGS += -O2
nacl : $(sources)
	$(NACL_CXX) -c $^ -O2 $(CFLAGS) $(CLIBS)
	$(NACL_AR) -rcs $(subst .c,.o, $(nodir $^)) -f $(TARGET).a
		


.PHONY : pnacl
pnacl : sources += $(wildcard ./../../src/pnacl/*.cc)
pnacl : $(sources)
	$(NACL_CXX) -c $^ $(CFLAGS) $(CLIBS)
	$(NACL_AR) -rcs $(subst .c,.o, $(nodir $^)) -f $(TARGET).a


debug: $(sources)
	

clean :
	$(RM) *.o
