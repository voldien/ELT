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

VALID_TOOLCHAINS := pnacl newlib glibc


include $(NACL_SDK_ROOT)/tools/common.mk

TARGET := libEngineEx

CLIBS := -lppapi_cpp -lppapi -lm -ldl -lOpenCL

CFLAGS := -w -Wall -I"./../../include" -DDONT_SUPPORT_OPENCL=1 -I"$(NACL_SDK_ROOT)/include"	#TODO resolve include dependency 

vpath %.c ./../../src
vpath %.h ./../../include

sources = $(wildcard ./../../src/*.c)
sources += $(wildcard ./../../src/system/*.c)
sources += $(wildcard ./../../src/input/*.c)
objects = $(subst .c,.o, $(sources))


all : $(TARGET).a

$(TARGET).a : $(objects)
	$(PNACL_AR) -rcs $(nodir $^) -f $@

%.o : %.c
	$(PNACL_CXX) -c  $^ -O2 $(CFLAGS) $(CLIBS)

clean :
	$(RM) *.o
