export ARCHS = arm64e arm64
export TARGET = iphone:clang:17.0:11.0
include $(THEOS)/makefiles/common.mk

TWEAK_NAME = FilePickerFix
FilePickerFix_FILES = Tweak.xm
FilePickerFix_CFLAGS = -fobjc-arc

include $(THEOS_MAKE_PATH)/tweak.mk