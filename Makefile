all: jni/*
	ndk-build
	
install: all
	install -d ipk/airunit/data/opt/etc/preload.d/
	install libs/armeabi-v7a/lib*.so ipk/airunit/data/opt/etc/preload.d/

ipk: all
	$(MAKE) -C ipk clean
	$(MAKE) install	
	$(MAKE) -C ipk
	mv ipk/airunit/*.ipk ./
	mv ipk/glasses/*.ipk ./

clean:
	$(MAKE) -C ipk clean
	rm -f *.ipk
	rm -rf libs
	rm -rf obj
	rm ipk/airunit/data/opt/etc/preload.d/liblive_audio_v2_au.so