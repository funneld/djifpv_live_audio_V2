#!/system/bin/sh

mkfifo /tmp/audiopipe
ffmpeg -y -probesize 32 -fflags nobuffer -flags low_delay -f u16le -ar 48000 -ac 2 -i udp://localhost:45151 -f u16le /tmp/audiopipe | tinyplay /tmp/audiopipe -i raw -d 0 -r 48000 -b 16 -c 2
