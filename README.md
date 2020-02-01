Convert your Android device into USB keyboard/mouse, control your PC from your Android device remotely, including BIOS/bootloader.

#### Apps & tools using android-keyboard-gadget:
* [USB Keyboard](https://github.com/nift4/android-keyboard-gadget/tree/app?files=1) [(F-Droid/Download)](https://apt.izzysoft.de/fdroid/index/apk/remote.hid.keyboard.client)
* [hid-gadget-test](https://github.com/nift4/android-keyboard-gadget/tree/jni?files=1)
* [Authorizer](https://github.com/tejado/Authorizer)
* [KP2A USB Keyboard plugin](https://play.google.com/store/apps/details?id=th.in.whs.k2ausbkbd) [(F-Droid)](https://apt.izzysoft.de/fdroid/index/apk/th.in.whs.k2ausbkbd)

Installation
============

Moto G5 (cedric)
----------------

Coming soon...

Other devices
-------------

- You will have to compile the kernel yourself after appling the patch. Ask your ROM developer or XDA device community.

SELinux
=======

You may need to disable SELinux for /dev/hidg0 and /dev/hidg1 to use this correctly.

Compiling USB Keyboard app
==========================

To compile USB Keyboard app, install Android SDK and NDK from site http://developer.android.com/ , and launch commands

	git clone https://github.com/pelya/commandergenius.git
	cd commandergenius
	git submodule update --init --recursive
	rm -f project/jni/application/src
	ln -s hid-pc-keyboard project/jni/application/src
	./changeAppSettings.sh -a
	android update project -p project

How it works
============

The custom kernel you have compiled adds two new devices, /dev/hidg0 for keyboard, and /dev/hidg1 for mouse.

You can open these two files, using open() system call,
and write raw keyboard/mouse events there, using write() system call,
which will be sent through USB cable to your PC.

Keyboard event is an array of 8 byte length, first byte is a bitmask of currently pressed modifier keys:

	typedef enum {
		LCTRL = 0x1,
		LSHIFT = 0x2,
		LALT = 0x4,
		LSUPER = 0x8, // Windows key
		RCTRL = 0x10,
		RSHIFT = 0x20,
		RALT = 0x40,
		RSUPER = 0x80, // Windows key
	} ModifierKeys_t;

Remaining 7 bytes is a list of all other keys currently pressed, one byte for one key, or 0 if no key is pressed.
Consequently, the maximum amount of keys that may be pressed at the same time is 7, excluding modifier keys.

Professional or 'gamer' USB keyboards report several keyboard HID descriptors, which creates several keyboard devices in host PC,
to overcome that 7-key limit.

The scancode table for each key is available [in hid-gadget-test utility](https://github.com/nift4/android-keyboard-gadget/tree/jni/jni/hid-gadget-test.c#L33).
Extended keys, such as Play/Pause, are not supported, because they require modifying USB descriptor in kernel patch.

Mouse event is an array of 4 bytes, first byte is a bitmask of currently pressed mouse buttons:

	typedef enum {
		BUTTON_LEFT = 0x1,
		BUTTON_RIGHT = 0x2,
		BUTTON_MIDDLE = 0x4,
	} MouseButtons_t;

Remaining 3 bytes are X movement offset, Y movement offset, and mouse wheel offset, represented as signed integers.
Horizontal wheel is not supported yet.

See functions outputSendKeys() and outputSendMouse() inside file [input.cpp](https://github.com/nift4/android-keyboard-gadget/tree/master/app/input.cpp)
for reference implementation.
