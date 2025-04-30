export ARCHS = arm64 arm64e
export TARGET = iphone:clang:latest:17.0.1

include $(THEOS)/makefiles/common.mk

TWEAK_NAME = FilePickerFix
FilePickerFix_FILES = \
    Sources/FilePickerFix.xm \
    Sources/Logger/Logger.m

FilePickerFix_CFLAGS += -I$(THEOS_PROJECT_DIR)/Sources
FilePickerFix_FRAMEWORKS = Foundation UIKit
FilePickerFix_PRIVATE_FRAMEWORKS = CoreServices

include $(THEOS)/makefiles/tweak.mk

after-install::
	install.exec "killall -9 SpringBoard"
