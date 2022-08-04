OLED_ENABLE            = yes   	# Enables the use of OLED displays
ENCODER_ENABLE         = yes  	# Enables the use of one or more encoders
RGBLIGHT_ENABLE        = yes  	# Enable keyboard RGB underglow
BOOTMAGIC_ENABLE       = no   	# Virtual DIP switch configuration
EXTRAKEY_ENABLE        = yes 	# Audio control and System control
CONSOLE_ENABLE         = no		# Console for debug
COMMAND_ENABLE         = no    # Commands for debug and configuration
NKRO_ENABLE            = no    # USB Nkey Rollover
BACKLIGHT_ENABLE       = no    # Enable keyboard backlight functionality on B7 by default
MIDI_ENABLE            = no    # MIDI support
UNICODE_ENABLE         = yes   # Unicode
BLUETOOTH_ENABLE       = no    # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE           = no    # Audio output on port C6
FAUXCLICKY_ENABLE      = no    # Use buzzer to emulate clicky switches
HD44780_ENABLE         = no    # Enable support for HD44780 based LCDs

BOOTLOADER             = atmel-dfu
SECONDARY              = 0
ifeq ($(SECONDARY), 1)
	POINTING_DEVICE_ENABLE  = no
	CFLAGS                 += "-D SECONDARY_SPLIT"
else
	MOUSEKEY_ENABLE         = yes
	POINTING_DEVICE_ENABLE  = yes
	POINTING_DEVICE_DRIVER  = pimoroni_trackball
	CFLAGS                 += "-D PRIMARY_SPLIT"
endif
