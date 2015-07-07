#!/bin/bash

LOCAL_SRC_DIR := ./../..
SHELL := bash
MKDIR2 ?= mkdir -p
RM := rm -rf
CC := gcc

#	has to be define manually for now TODO resolve 
NACL_SDK_ROOT ?= $(abspath $(dir $(THIS_MAKEFILE))../..)

GETOS := python $(NACL_SDK_ROOT)/tools/getos.py
OSNAME := $(shell $(GETOS))


include $(NACL_SDK_ROOT)/tools/common.mk

#
PNACL_TC_PATH := $(abspath $(NACL_SDK_ROOT)/toolchain/$(OSNAME)_pnacl)
PNACL_CXX := $(PNACL_TC_PATH)/bin/pnacl-clang
PNACL_FINALIZE := $(PNACL_TC_PATH)/bin/pnacl-finalize
PNACL_AR := $(PNACL_TC_PATH)/bin/pnacl-ar
PNACL_RANLIB := $(PNACL_TC_PATH)/bin/pnacl-ranlib
PNACL_TRANSLATE := $(PNACL_TC_PATH)/bin/pnacl-translate
PNACL_PNACL_ABICHECK := $(PNACL_TC_PATH)/bin/pnacl-abicheck

#
NACL_TC_PATH := $(abspath $(NACL_SDK_ROOT)/toolchain/$(OSNAME)_x86_glibc)
NACL_CXX := $(NACL_TC_PATH)/bin/x86_64-nacl-gcc
NACL_AR := $(NACL_TC_PATH)/bin/x86_64-nacl-ar
NACL_RANLIB := $(NACL_TC_PATH)/bin/x86_64-nacl-ranlib



VALID_TOOLCHAINS := pnacl newlib glibc dl pthread nacl_io rt clang-newlib ppapi_cpp


CHROME_ARGS += --allow-nacl-socket-api=localhost

TARGET :=libEngineEx

CLIBS :=  -lppapi -lm -ldl -lOpenCL -lpthread -lglibc -lrt -lnacl_io -lppapi_gles2 

CFLAGS := -w -fPIC -Wall -I$(LOCAL_SRC_DIR)/include -DDONT_SUPPORT_OPENCL=1 -I"$(NACL_SDK_ROOT)/include" -DGL_ES_VERSION_2_0=1

VPATH = $(LOCAL_SRC_DIR)/src 			\
	$(LOCAL_SRC_DIR)/src/math		\
	$(LOCAL_SRC_DIR)/src/input		\
	$(LOCAL_SRC_DIR)/src/system		\
	$(LOCAL_SRC_DIR)/src/pnacl		\
	$(LOCAL_SRC_DIR)/src/graphic




vpath %.c $(LOCAL_SRC_DIR)/src
vpath %.h $(LOCAL_SRC_DIR)/include


sources = $(wildcard  $(LOCAL_SRC_DIR)/src/*.c)
sources += $(wildcard $(LOCAL_SRC_DIR)/src/pnacl/*.c)
sources += $(wildcard $(LOCAL_SRC_DIR)/src/system/*.c)
sources += $(wildcard $(LOCAL_SRC_DIR)/src/input/*.c)
sources += $(wildcard $(LOCAL_SRC_DIR)/src/math/*.c)
#sources += $(wildcard ./../../src/graphic/*.c)



objects = $(notdir $(subst .c,.o, $(sources)))



all : $(TARGET).a #$(TARGT)64.a
	$echo -en "finished compiling and link $(du -h $^)"
	

%.o : CFLAGS += -O2
$(TARGET).a : $(objects)
	$(MKDIR2) build
	$(PNACL_AR) -rcs  $^ -f $@
	$(NACL_RANLIB) $@



%.o : %.c
	@echo -en $(notdir $(CC) ) $(notdir $^ ) "\n"
	 $(CC) $(CFLAGS) -c  $^ -o $@  


debug : CFlAGS += -g
debug : $(objects)
	$(NACL_AR) -rcs $(subst .c,.o, $^ ) -f $(TARGET).a


.PHONY : pnacl
.PHONY : nacl

nacl : CLFAGS += -O2 -DNACL=1
nacl : CLIBS += 
nacl : CC := $(NACL_CXX)
nacl : $(objects)
	$(MKDIR2) build
	$(NACL_AR) -rcs $(subst .c,.o, $(nodir $^)) -f $(TARGET).a
		



pnacl : CFLAGS += -O -DPNACL=1 -DEX_PNACL=1
pnacl : CC := $(PNACL_CXX)
pnacl : CFLAGS += -I"$(NACL_SDK_ROOT)/include/newlib"
pnacl : pnaclsource = $(notdir $(subst .c, .o $(wildcard $(LOCAL_SRC_DIR)/src/pnacl/*.c) ) )
pnacl : $(objects) $(pnaclsource)
	$(MKDIR2) build
	$(PNACL_AR) cr $(TARGET).a $^
	$(PNACL_RANLIB) $(TARGET).a
	@du -h $(TARGET).a
	#$(PNACL_TC_PATH)/bin/pnacl-nm $(TARGET).a


clean : 
	$(RM) *.o

