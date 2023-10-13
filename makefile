LIB_DIR = libs
LIB_EIGEN = eigen-3.4.0
LIB_GTEST = googletest-1.14.0

all: check_libs build_cmake

check_libs:
	echo "Checking libraries"
	if [ ! -d $(LIB_DIR) ]; then \
		mkdir $(LIB_DIR); \
	fi
	cd $(LIB_DIR); \
	if [ ! -d $(LIB_EIGEN) ]; then \
		wget "https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.zip"; \
		unzip eigen-3.4.0.zip > /dev/null; \
		rm eigen-3.4.0.zip; \
	fi; \
	if [ ! -d $(LIB_GTEST) ]; then \
		wget "https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip"; \
		unzip v1.14.0.zip > /dev/null; \
		rm v1.14.0.zip; \
	fi

compile:
	g++ -g -fsanitize=address -std=c++17 src/main.cpp -o run_main

build_cmake:
	mkdir build; \
	cd build; \
	cmake ..; \
	make

clean:
	rm -rf ./build