#!/bin/bash

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

#
BASE ?= $(call my-dir)
SHELL ?= /bin/bash
DESTDIR=/
MAKE := make
CMAKE := cmake
MKDIR ?=  mkdir -p
TAR := tar
CP ?= cp
RM ?= rm -rf
INSTALL ?= install


CFLAGS ?= 


#echo `git describe` | sed -e 's/[^0-9]*//g' | cut -c1-1 

MAJOR_VERSION :=` git describe | sed -e 's/[^0-9]*//g' | cut -c1-1 `
MINOR_VERSION := ` git describe | sed -e 's/[^0-9].[^0-9]*//g' | cut -c1-1 `
REVISION_VERSION := ` git describe | sed -e 's/[^0-9].[^0-9].[^0-9]*//g' | cut -c1-2`


PACKAGE_INCLUDE ?= src include 


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

# check if git exist in directory.
#ifdef $(find .git
CFLAGS += -DMAJOR_VERSION=$(MAJOR_VERSION)
CFLAGS += -DMINOR_VERSION=$(MINOR_VERSION)
CFLAGS += -DREVISION_VERSION=$(REVISION_VERSION)




.PHONY : createpackage
createpackage:
	@echo "version: " $(MAJOR_VERSION).$(MINOR_VERSION).$(REVISION_VERSION)
	find include/ src/ -name "*.c" -or -name "*.h" | tar -zcvf $(current_dir)-$(MAJOR_VERSION).$(MINOR_VERSION).$(REVISION_VERSION).tar.gz -T -
	@du -h $(current_dir)-$(MAJOR_VERSION).$(MINOR_VERSION).$(REVISION_VERSION).tar.gz



