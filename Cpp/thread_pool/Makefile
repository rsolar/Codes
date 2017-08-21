.PHONY: clean

run: main
	./main

main: main.cpp thread_pool.h
	g++ -std=c++11 -O3 -o main main.cpp

clean:
	rm -rf *.o main