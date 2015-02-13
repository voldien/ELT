#!/bin/bash
LOCAL_PATH := $(call my-dir)

FILE_LIST := $(wildcard $(LOCAL_PATH)/../../../Source/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Source/System/*.c)

include $(CLEAR_VARS)

LOCAL_MODULE := EngineEx

CODE_PATH := ./../../../Source/

LOCAL_C_INCLUDE := $(LOCAL_PATH)$(CODE_PATH)#elt_alloc.h


LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES-= main.c

#pre compiler flag
LOCAL_CFLAGS := -DANDROID=1 -D__ANDROID__=1 -Wall -I"./../../../External/OpenCL/Include" -I"$(INTELOCLSDKROOT)/include"
LOCAL_CPPFLAGS := -fexceptions

LOCAL_LDLIBS := -lGLESv2 -lEGL -llog -landroid  -lOpenCL

include $(BUILD_SHARED_LIBRARY)
