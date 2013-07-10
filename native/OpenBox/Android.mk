LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := Box2D-local
LOCAL_SRC_FILES := $(LOCAL_PATH)/../Box2D/libs/$(TARGET_ARCH_ABI)/libbox2D.so
# LOCAL_SRC_FILES := libbox2D.so
include $(PREBUILT_SHARED_LIBRARY)
include $(CLEAR_VARS)
LOCAL_MODULE    := openbox
LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. $(LOCAL_PATH)
NDK_OUT :=../../
LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,, \
	$(wildcard $(LOCAL_PATH)/*.cpp) \
    $(wildcard $(LOCAL_PATH)/Collision/Shapes/*.cpp))
LOCAL_LDLIBS := -lm -llog -ldl -lGLESv1_CM
LOCAL_SHARED_LIBRARIES := Box2D-local
include $(BUILD_SHARED_LIBRARY)
