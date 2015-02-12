#!/bin/bash

VALID_TOOLCHAINS := pnacl newlib glibc

NACL_SDK_ROOT ?= $(abspath $(CURDIR)/../../)

include $(NACL_SDK_ROOT)/tools/common.mk

TARGET = part2
LIBS = ppapi_cpp ppapi

CFLAGS = -Wall
vpath =./../../
SOURCES = $<

#	Build rules generated by macros from common.mk

$(foreach src, $(SOURCES), $(eval $(call COMPILE_RULE, $(src), $(CFLAGS))))

# The PNaCl workfow uses both an unstripped and finalized/stripped binary.
# On NaCl, onty produce a stripped binary for Release configs (not Debug)
ifneq (,$(or $(findstring pnacl,$(TOOLCHAIN)), $(findstring Release, $(CONFIG))))
$(eval $(call LINK_RULE, $(TARGET)_unsripped,$(SOURCES),$(LIBS),$(DEPS)))
$(eval $(call STRIP_RULE,$(TARGET),$(TARGET)_unstripped))
else
$(eval $(call LINK_RULE, $(TARGET), $(SOURCES), $(LIBS), $(DEPS)))
endif

$(eval $(call NMF_RULE,$(TARGET),))
