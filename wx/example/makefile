example: example.cpp
	g++ -c -w example.cpp `wx-config --cflags` -O2
	g++ example.o `wx-config --libs` -o example

clean: 
	rm example.o example
