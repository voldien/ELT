
LOCAL_PATH := $(call my-dir)


INCLUDE_PATH := ./../../../include/
SOURCE_PATH  := ./../../../src/

#	c files
FILE_LIST := $(wildcard $(LOCAL_PATH)/../../../src/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../src/system/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../src/input/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../src/math/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../src/graphic/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../src/system/android/*.c)
FILE_LIST -= $(LOCAL_PATH)/../../../src/system/elt_cl.c

include $(CLEAR_VARS)



CODE_PATH := ./../../../src/

LOCAL_MODULE := libEngineEx


LOCAL_C_INCLUDE := $(LOCAL_PATH)$(INCLUDE_PATH)  #elt_alloc.h


#LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES := $(FILE_LIST)

#pre compiler flag
LOCAL_CFLAGS := -w -O3 -DANDROID=1 -D__ANDROID__=1 -DINTERNAL_ENGINE=1 -Wall -I"./../../../include" -I"./../../../External/OpenCL/Include" -D_DEBUG=1 -DEX_ANDROID=1  -DDONT_SUPPORT_OPENCL=1 -DGL_ES_VERSION_2_0=1

 #    #-I"$(INTELOCLSDKROOT)/include" -L"/opt/intel/opencl-1.2-4.5.0.8/lib64" 

LOCAL_CFLAGS += -Wno-error=format-security

LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2 -lEGL -llog -ldl
LOCAL_STATIC_LIBRARIES := android_native_app_glue

# -lGLESv1_CM 


#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)
$(call import-module,android/native_app_glue)

#$(call import-module,android/native_app_glue)
