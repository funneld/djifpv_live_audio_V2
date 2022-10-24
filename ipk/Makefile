NAME_AU = $(shell cat ./airunit/control/control | grep Package | cut -d" " -f2)
ARCH_AU = $(shell cat ./airunit/control/control | grep Architecture | cut -d" " -f2)
VERSION_AU = $(shell cat ./airunit/control/control | grep Version | cut -d" " -f2)
IPK_NAME_AU = "${NAME_AU}_${VERSION_AU}_${ARCH_AU}.ipk"

NAME_GLS = $(shell cat ./glasses/control/control | grep Package | cut -d" " -f2)
ARCH_GLS = $(shell cat ./glasses/control/control | grep Architecture | cut -d" " -f2)
VERSION_GLS = $(shell cat ./glasses/control/control | grep Version | cut -d" " -f2)
IPK_NAME_GLS = "${NAME_GLS}_${VERSION_GLS}_${ARCH_GLS}.ipk"

all:
	mkdir -p airunit/tmp
	echo "2.0" > airunit/tmp/debian-binary
	cp -r airunit/data airunit/tmp/
	cp -r airunit/control airunit/tmp/
	chmod +x airunit/tmp/data/opt/bin/live_audio_v2_airside.sh
	chmod +x airunit/tmp/control/postinst
	chmod +x airunit/tmp/control/prerm
	cd airunit/tmp/control && tar --owner=0 --group=0 -czvf ../control.tar.gz .
	cd airunit/tmp/data && tar --owner=0 --group=0 -czvf ../data.tar.gz .
	cd airunit/tmp/ && tar --owner=0 --group=0 -czvf "../${IPK_NAME_AU}" ./control.tar.gz ./data.tar.gz ./debian-binary

	mkdir -p glasses/tmp
	echo "2.0" > glasses/tmp/debian-binary
	cp -r glasses/data glasses/tmp/
	cp -r glasses/control glasses/tmp/
	chmod +x glasses/tmp/data/opt/bin/live_audio_v2_glasses.sh
	chmod +x glasses/tmp/control/postinst
	chmod +x glasses/tmp/control/prerm
	cd glasses/tmp/control && tar --owner=0 --group=0 -czvf ../control.tar.gz .
	cd glasses/tmp/data && tar --owner=0 --group=0 -czvf ../data.tar.gz .
	cd glasses/tmp/ && tar --owner=0 --group=0 -czvf "../${IPK_NAME_GLS}" ./control.tar.gz ./data.tar.gz ./debian-binary
	
clean:
	rm -rf airunit/tmp
	rm -rf glasses/tmp
