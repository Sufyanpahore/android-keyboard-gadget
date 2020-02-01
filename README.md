# USB Keyboard
An graphical app to control PCs / other devices via Keyboard and Mouse emulation.

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
