ARCHS = arm64
TARGET = iphone:clang:latest:14.0
include $(THEOS)/makefiles/common.mk

TWEAK_NAME = FilePickerFix
FilePickerFix_FILES = Sources/FilePickerFix.xm Sources/Logger/Logger.m
FilePickerFix_FRAMEWORKS = UIKit

include $(THEOS_MAKE_PATH)/tweak.mk
