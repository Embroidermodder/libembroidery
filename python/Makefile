CC=gcc
COPY=cp
CFLAGS=-fPIC -I ..

all: libembroidery.so

libembroidery.o: ../embroidery.c
	$(COPY) ../embroidery.h embroidery/embroidery.h
	$(CC) $(CFLAGS) -c ../embroidery.c -o $@

libembroidery.so: libembroidery.o
	$(CC) libembroidery.o -shared -o $@

clean:
	rm -f libembroidery.o libembroidery.so
