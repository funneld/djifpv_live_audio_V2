#!/system/bin/sh

if grep -q "WM150" /system/etc/dji.json
then
	sleep 5
	echo "Starting live audio DUML command..."
	dji_mb_ctrl -S test -R local -g 1 -t 1 -s 2 -c E1 -a 0 -q i 01
else
	echo "AU NOT COMPATIBLE. EXIT."
fi
