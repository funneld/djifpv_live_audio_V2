all: jni/*
	ndk-build
	
install: all
	install -d ipk/airunit/data/opt/etc/preload.d/
	install -d ipk/glasses/data/opt/etc/preload.d/
	install libs/armeabi-v7a/liblive_audio_v2_au.so ipk/airunit/data/opt/etc/preload.d/
	install libs/armeabi-v7a/libtinyalsa.so ipk/glasses/data/opt/etc/preload.d/
	install libs/armeabi-v7a/tinyplay_udp ipk/glasses/data/opt/bin/

ipk: all
	$(MAKE) -C ipk clean
	$(MAKE) install	
	chmod +x ipk/glasses/data/opt/bin/tinyplay_udp
	$(MAKE) -C ipk
	mv ipk/airunit/*.ipk ./
	mv ipk/glasses/*.ipk ./

clean:
	$(MAKE) -C ipk clean
	rm -f *.ipk
	rm -rf libs
	rm -rf obj
	rm ipk/airunit/data/opt/etc/preload.d/liblive_audio_v2_au.so
	rm ipk/glasses/data/opt/etc/preload.d/libtinyalsa.so
	rm ipk/glasses/data/opt/bin/tinyplay_udp