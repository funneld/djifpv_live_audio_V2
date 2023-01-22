LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -fPIC -std=c99
LOCAL_LDFLAGS += -fPIC 
LOCAL_LDLIBS := -llog

LOCAL_MODULE    := live_audio_v2_au 
LOCAL_SRC_FILES := live_audio_v2_au.c

include $(BUILD_SHARED_LIBRARY)
