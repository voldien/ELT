#!/bin/bash
LOCAL_PATH := $(call my-dir)


#	c files
FILE_LIST := $(wildcard $(LOCAL_PATH)/../../../Source/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Source/System/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Source/Input/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Source/math/*.c)


include $(CLEAR_VARS)

LOCAL_MODULE := EngineEx

CODE_PATH := ./../../../Source/

LOCAL_C_INCLUDE := $(LOCAL_PATH)$(CODE_PATH)#elt_alloc.h


LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES-= main.c

#pre compiler flag
LOCAL_CFLAGS := -w -DANDROID=1 -D__ANDROID__=1 -Wall -I"./../../../External/OpenCL/Include" -I"$(INTELOCLSDKROOT)/include" -L"/opt/intel/opencl-1.2-4.5.0.8/lib64"

LOCAL_CFLAGS += -Wno-error=format-security

LOCAL_CPPFLAGS := -fexceptions

LOCAL_LDLIBS := -lGLESv2 -lEGL -llog -landroid #-lOpenCL#-lPVROCL #-lOpenCL

include $(BUILD_SHARED_LIBRARY)
