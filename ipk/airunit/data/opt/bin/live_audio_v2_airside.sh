#!/system/bin/sh

if grep -q "WM150" /system/etc/dji.json; then
	if [ -d "/storage/sdcard0" ]; then
		echo "SD card found. Live audio will start only while recording."
	else
		echo "No SD card found. Start tinycap."
		sleep 3
		LD_PRELOAD="/opt/etc/preload.d/liblive_audio_v2_au.so" tinycap /dev/null -r 48000 -b 16 > /dev/null 2>&1
	fi
else
	echo "Airunit not compatible. Exit."
fi
