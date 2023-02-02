LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_CFLAGS += -fPIC -std=c99 -O3
LOCAL_LDFLAGS += -fPIC 
LOCAL_LDLIBS := -llog
LOCAL_MODULE    := live_audio_v2_au 
LOCAL_SRC_FILES := live_audio_v2_au.c
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_CFLAGS += -fPIC -std=c99 -O3
LOCAL_LDFLAGS += -fPIC
LOCAL_SRC_FILES:= tinyalsa/mixer.c tinyalsa/pcm.c
LOCAL_MODULE := libtinyalsa
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_CFLAGS += -fPIC -std=c99 -O3
LOCAL_LDFLAGS += -fPIC
LOCAL_SRC_FILES:= tinyplay_udp.c
LOCAL_MODULE := tinyplay_udp
LOCAL_SHARED_LIBRARIES:= libtinyalsa
include $(BUILD_EXECUTABLE)