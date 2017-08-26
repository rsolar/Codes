.PHONY: clean

all: scoped_ptr shared_ptr unique_ptr

run: scoped_ptr shared_ptr unique_ptr
	./scoped_ptr
	./shared_ptr
	./unique_ptr

scoped_ptr: scoped_ptr.cpp scoped_ptr.h
	g++ -std=c++11 -o scoped_ptr scoped_ptr.cpp

shared_ptr: shared_ptr.cpp shared_ptr.h
	g++ -std=c++11 -o shared_ptr shared_ptr.cpp

unique_ptr: unique_ptr.cpp unique_ptr.h
	g++ -std=c++11 -o unique_ptr unique_ptr.cpp

clean:
	rm -rf *.o scoped_ptr shared_ptr unique_ptr weak_ptr
