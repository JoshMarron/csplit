TOOLCHAIN_PATH=$(shell cat cmakeflags)

.PHONY: build reconf run

build:
	cd build && make

reconf:
	rm -rf build && mkdir build && cd build && cmake -D$(TOOLCHAIN_PATH) ../

run:
	./build/src/csplit