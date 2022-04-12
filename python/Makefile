all:
	swig -Wall -python embroidery.i
	python3 setup.py build
	python3 setup.py install --user
	python3 test.py

clean:
	rm -fr build dist libembroidery.egg-info __pycache__
	rm -fr libembroidery.py embroidery_wrap.c
