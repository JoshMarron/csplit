TOOLCHAIN_PATH=$(shell cat cmakeflags)

.PHONY: build reconf run

build:
	cd build && make -j8 --no-print-directory

conan:
	rm -rf build && mkdir build && cd build && conan install .. && cmake ../

reconf:
	rm -rf build && mkdir build && cd build && cmake -D$(TOOLCHAIN_PATH) ../

run:
	./build/src/csplit

test:
	cd build && make && make test
test-verb:
	cd build && make && ./tests/core/csplitcore.t.tsk