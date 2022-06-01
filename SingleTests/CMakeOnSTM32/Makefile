.PHONY: all build cmake clean format

BUILD_DIR := build
BUILD_TYPE ?= Debug
TOOL_DIR := .env/gcc-arm-none-eabi-10.3-2021.10/bin
MAKE_DIR := .

all: build

${BUILD_DIR}/Makefile:
	cmake \
		-B${BUILD_DIR} \
		-DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
		-DCMAKE_TOOLCHAIN_FILE=gcc-arm-none-eabi.cmake \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DTOOL_DIR=${TOOL_DIR}

cmake: ${BUILD_DIR}/Makefile

get_toolchain:
	./download.sh 

build: cmake
	$(MAKE) -C ${BUILD_DIR} --no-print-directory

SRCS := $(shell find . -name '*.[ch]' -or -name '*.[ch]pp')
format: $(addsuffix .format,${SRCS})

%.format: %
	clang-format -i $<

clean:
	rm -rf $(BUILD_DIR) .env
