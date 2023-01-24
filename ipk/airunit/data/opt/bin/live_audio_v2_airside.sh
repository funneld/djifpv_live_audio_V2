#!/system/bin/sh

if grep -q "WM150" /system/etc/dji.json; then
	if [ -d "/storage/sdcard0" ]; then
		echo "SD card found. Live audio will start only while recording."
	else
		echo "No SD card found. Start tinycap."
		LD_PRELOAD="/opt/etc/preload.d/liblive_audio_v2_au.so" tinycap /dev/null -r 48000 -b 16
	fi
else
	echo "Airunit not compatible. Exit."
fi
