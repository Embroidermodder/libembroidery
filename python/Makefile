CC=gcc
COPY=cp
CFLAGS=-fPIC -I ..

all: libembroidery.so

libembroidery.o: ../embroidery.c
	$(CC) $(CFLAGS) -c $< -o $@

libembroidery.so: libembroidery.o
	$(CC) $< -shared -o $@

test: all
	python3 embroidery.py

dist:
	python3 -m build
	python3 -m pip install dist/*.whl

	rm -fr build dist embroidery/__pycache__ embroidery/embroidery.egg-info

clean:
	rm -f libembroidery.o libembroidery.so
