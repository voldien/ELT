#!/bin/bash

MKDIR := mkdir -p
RM := rm -rf

#	has to be define manually for now TODO resolve 
NACL_SDK_ROOT ?= $(abspath $(dir $(THIS_MAKEFILE))../..)

GETOS := python $(NACL_SDK_ROOT)/tools/getos.py
OSNAME := $(shell $(GETOS))


PNACL_TC_PATH := $(abspath $(NACL_SDK_ROOT)/toolchain/$(OSNAME)_pnacl)
PNACL_CXX := $(PNACL_TC_PATH)/bin/pnacl-clang++
PNACL_FINALIZE := $(PNACL_TC_PATH)/bin/pnacl-finalize

VALID_TOOLCHAINS := pnacl newlib glibc


include $(NACL_SDK_ROOT)/tools/common.mk

TARGET := libEngineEx

CLIBS := ppapi_cpp ppapi

CFLAGS := -w -Wall -I"./../../include"

vpath %.c ./../../src
vpath %.h ./../../include

sources = $(wildcard ./../../src/*.c)
sources += $(wildcard ./../../src/system/*.c)
sources += $(wildcard ./../../src/input/*.c)
objects = $(subst .c,.bc, $(sources))

all : $(TARGET).pexe

$(TARGET).pexe : $(objects)
	$(PNACL_FINALIZE) -o $@ $<

%.bc : $(sources)
	$(PNACL_CXX) -o $^ -O2 $(CFLAGS) $(LIBS)

clean :
	$(RM) *.bc
