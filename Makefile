all:

ipk: all
	$(MAKE) -C ipk clean
	$(MAKE) -C ipk
	mv ipk/airunit/*.ipk ./
	mv ipk/glasses/*.ipk ./

clean:
	$(MAKE) -C ipk clean
	rm -f *.ipk
    