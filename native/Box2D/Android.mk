LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := box2D
LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. $(LOCAL_PATH)/include
# LOCAL_CFLAGS := -O3 -ffast-math
LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
        $(wildcard $(LOCAL_PATH)/*.cpp) \
        $(wildcard $(LOCAL_PATH)/Collision/*.cpp) \
        $(wildcard $(LOCAL_PATH)/Collision/Shapes/*.cpp) \
        $(wildcard $(LOCAL_PATH)/Rope/*.cpp) \
        $(wildcard $(LOCAL_PATH)/Dynamics/*.cpp) \
        $(wildcard $(LOCAL_PATH)/Dynamics/Contacts/*.cpp) \
        $(wildcard $(LOCAL_PATH)/Dynamics/Joints/*.cpp) \
	$(wildcard $(LOCAL_PATH)/Common/*.cpp))
LOCAL_LDLIBS := -lm -llog -ldl
include $(BUILD_SHARED_LIBRARY)
