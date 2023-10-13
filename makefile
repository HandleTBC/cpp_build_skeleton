PHONY_TARGETS := debug release configure_debug configure_release build_debug build_release
.PHONY: $(PHONY_TARGETS)

LIB_DIR = libs
LIB_EIGEN = eigen-3.4.0
LIB_GTEST = googletest-1.14.0

vanilla: check_libs debug 

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

debug: configure_debug build_debug

release: configure_release build_release

configure_debug:
	@mkdir -p build/debug
	@cd build/debug && \
	cmake -DCMAKE_BUILD_TYPE=Debug ../..

configure_release:
	@mkdir -p build/release
	@cd build/release && \
	cmake -DCMAKE_BUILD_TYPE=Release ../..

build_debug:
	@cd build/debug && \
	make -s $(filter-out $(PHONY_TARGETS),$(MAKECMDGOALS))

build_release:
	@cd build/release && \
	make -s $(filter-out $(PHONY_TARGETS),$(MAKECMDGOALS))



clean:
	rm -rf ./build

# Catch-all rule to prevent make from erroring out when given
# targets it doesn't recognize
%:
	@: