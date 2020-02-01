hid-gadget-test
===============

There is a possibility to send keypresses in an automated way, using terminal emulator for Android or similar app.
This is done using hid-gadget-test utility.

First, copy this utility to your device.

	adb push hid-gadget-test /data/local/tmp
	adb shell chmod 755 /data/local/tmp/hid-gadget-test

You will need to set world-writable permissions on /dev/hidg0, or run hid-gadget-test from root shell.

	adb shell
	su
	chmod 666 /dev/hidg0 /dev/hidg1

To always have root shell, so you don't need to enter 'su' each time, run command

	adb root

Then, use hid-gadget-test to send keypresses.

	adb shell
	cd /data/local/tmp

	# Send letter 'a'
	echo a | ./hid-gadget-test /dev/hidg0 keyboard

You can also run this command without launching ADB shell, from shell script or .bat file.

	adb shell 'echo a | /data/local/tmp/hid-gadget-test /dev/hidg0 keyboard'

Advanced examples.

	# Send letter 'B'
	echo left-shift b | ./hid-gadget-test /dev/hidg0 keyboard

	# Send string 'abcdeZ'
	for C in a b c d e 'left-shift z' ; do echo "$C" ; sleep 0.1 ; done | ./hid-gadget-test /dev/hidg0 keyboard

	# You may combine several modifier keys
	echo left-ctrl left-shift enter | ./hid-gadget-test /dev/hidg0 keyboard

	# Try to guess what this command sends
	echo left-ctrl left-alt del | ./hid-gadget-test /dev/hidg0 keyboard

	# Bruteforce 4-digit PIN-code, that's a particularly popular script
	# that people keep asking me for. It executes for 42 hours.
	for a in 0 1 2 3 4 5 6 7 8 9; do
	for b in 0 1 2 3 4 5 6 7 8 9; do
	for c in 0 1 2 3 4 5 6 7 8 9; do
	for d in 0 1 2 3 4 5 6 7 8 9; do
	echo $a $b $c $d
	for C in $a $b $c $d enter ; do echo "$C" ; sleep 0.2 ; done | ./hid-gadget-test /dev/hidg0 keyboard
	sleep 15
	done
	done
	done
	done

	# Press right mouse button
	echo --b2 | ./hid-gadget-test /dev/hidg1 mouse

	# Hold left mouse button, drag 100 pixels to the right and 50 pixels up, then release
	echo --hold --b1 | ./hid-gadget-test /dev/hidg1 mouse
	echo --hold --b1 100 0 | ./hid-gadget-test /dev/hidg1 mouse
	echo --hold --b1 0 -50 | ./hid-gadget-test /dev/hidg1 mouse
	echo --b1 | ./hid-gadget-test /dev/hidg1 mouse

You can check the modification time of file `/sys/devices/virtual/hidg/hidg0/dev`
to know when the USB cable has been plugged into PC, however this does not always work,
so it's better to simply check if hid-gadget-test returned an error.

Here's a sample shell script that will send a predefined key sequence when USB cable is plugged into PC:

	#!/system/bin/sh
	while true; do
		until echo volume-up | ./hid-gadget-test /dev/hidg0 keyboard >/dev/null 2>&1; do
			sleep 2
		done
		echo "USB cable plugged"
		sleep 1
		for C in 'left-meta r' c m d enter s t a r t space i e x p l o r e space x x x period c o m enter \
			; do echo "$C" ; sleep 0.3 ; done | ./hid-gadget-test /dev/hidg0 keyboard
		echo "Done sending commands"
		while echo volume-up | ./hid-gadget-test /dev/hidg0 keyboard >/dev/null 2>&1; do
			sleep 2
		done
		echo "USB cable unplugged"
	done

Here is [the list of keys that hid-gadget-test utility supports](https://github.com/nift4/android-keyboard-gadget/tree/master/hid-gadget-test/jni/hid-gadget-test.c#L33)
