#!/bin/bash

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))
DESTDIR=/
MAKE := make
CMAKE := cmake
TAR := tar


MAJOR_VERSION := 0
MINOR_VERSION := 6
REVISION_VERSION := 8


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




.PHONY : createpackage
createpackage:
	tar -zcvf $(current_dir)-$(MAJOR_VERSION).$(MINOR_VERSION).$(REVISION_VERSION).tar.gz src include 



