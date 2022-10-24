#!/system/bin/sh

if grep -q "WM150" /system/etc/dji.json
then
	sleep 5
	mkfifo /tmp/audiopipe
	tinycap /tmp/audiopipe -r 48000 -b 16 | ffmpeg -y -probesize 32 -fflags nobuffer -flags low_delay -f u16le -ar 48000 -ac 2 -i /tmp/audiopipe -f u16le udp://192.168.41.2:45151
else
    echo "AU NOT COMPATIBLE. EXIT"
fi
