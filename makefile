CFLAGS = -std=c99 -Wall -pedantic
CXX = gcc

all:
	mkdir build
	@(cd lib && make)
	@(cd test/test_main && make)
	@(cd build && cp -r ../lib ./ && cp -r ../rsc ./ && cp ../test/test_main/letsplay ./)


clean:
	@(cd lib && make clean)
	@(cd test/test_main && make clean)
	rm -rf build