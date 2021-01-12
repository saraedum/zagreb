BOARD_TAG    = uno
ARDUINO_PORT = /dev/ttyACM0
ARDUINO_LIBS = Adafruit_NeoPixel AceCommon AceRoutine
USER_LIB_PATH = .
EXTRA_FLAGS = -std=gnu++11
CPPFLAGS = -isystem AceCommon/src -isystem AceRoutine/src

include Arduino-Makefile/Arduino.mk
