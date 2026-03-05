.PHONY: all cacheSim cache_tests test clean

all: cacheSim cache_tests

cacheSim: src/cacheSim.cpp
	g++ -std=c++17 -Wall -Wextra -pedantic src/cacheSim.cpp -o cacheSim

cache_tests: tests/tests.cpp
	g++ -std=c++17 -Wall -Wextra -pedantic tests/tests.cpp -o cache_tests

test: cache_tests
	./cache_tests

clean:
	rm -f cacheSim cache_tests cacheSim.exe cache_tests.exe
