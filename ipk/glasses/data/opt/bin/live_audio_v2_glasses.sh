#!/system/bin/sh

sleep 5
LD_PRELOAD="/opt/etc/preload.d/libtinyalsa.so" /opt/bin/tinyplay_udp > /dev/null 2>&1
