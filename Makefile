## ---------------------------- EMBER ----------------------------- ## 
include Makefile.BuildOptions

######################################################################
# VARIABLES
######################################################################

# Build Options (from Makefile.BuildOptions)
BUILD_OPTIONS+=-DVIRTUAL=$(VIRTUAL)
BUILD_OPTIONS+=-DDEBUG=$(DEBUG)

# Compile
CXXFLAGS = -fPIC -Wall -O3

# Include
EMBER_INCLUDE_FLAGS = -Isrc -Isrc/Ember/Include/Core -Isrc/Ember/Include/Data -Isrc/Ember/Include/Utility

# CPP Project Files
CPP_EMBER = $(wildcard src/Ember/*.cpp)
CPP_CORE = $(wildcard src/Ember/Core/*.cpp)
CPP_DATA = $(wildcard src/Ember/Data/*.cpp)
CPP_UTILITY = $(wildcard src/Ember/Utility/*.cpp)

# HDR Project Files
HDR_SRC = $(wildcard src/*.h)
HDR_CORE = $(wildcard src/Ember/Include/Core/*.h)
HDR_DATA = $(wildcard src/Ember/Include/Data/*.h)
HDR_UTILITY = $(wildcard src/Ember/Include/Utility/*.h)

# PCH Project Files
PCH = src/EmberPCH.h
PCH_GCH = $(PCH).gch

# Composition
HDR = $(HDR_SRC) $(HDR_CORE) $(HDR_DATA) $(HDR_UTILITY)
CPP = $(CPP_EMBER) $(CPP_CORE) $(CPP_DATA) $(CPP_UTILITY)
TMP := $(subst src/,obj/,$(CPP))
OBJ := $(subst .cpp,.o,$(TMP))

# RGB-MATRIX LIB
# https://github.com/hzeller/rpi-rgb-led-matrix
RGB_LIB_DISTRIBUTION=lib/rpi-rgb-led-matrix
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
RGB_LIBRARY_OBJ=obj/Library/rgb-matrix

# CMD Util
MD = mkdir -p

######################################################################
# PRIMARY TARGET
######################################################################

Ember: inf_start clean init inf_build $(PCH_GCH) $(OBJ) $(HDR) $(RGB_LIBRARY) package inf_complete

######################################################################
# TARGETS
######################################################################

install-virtual:
	sudo apt-get install libsfml-dev

clean:
	$(info >>>>> CLEANING <<<<<)
	rm -f $(OBJ) libEmber.a

init:
	${MD} obj
	${MD} obj/Ember
	${MD} obj/Ember/Core
	${MD} obj/Ember/Data
	${MD} obj/Ember/Utility
	${MD} $(RGB_LIBRARY_OBJ)

$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR)

package:
	$(info >>>>> PACKAGING <<<<<)
	ar x $(RGB_LIBRARY) && mv *.o $(RGB_LIBRARY_OBJ)
	ar -cvq libEmber.a $(OBJ) $(RGB_LIBRARY_OBJ)/*.o

######################################################################
# INFO
######################################################################

inf_start:
	$(info  )
	$(info ================= Ember Engine Build Tool =================)
	$(info BUILD VIRTUAL:                                      $(VIRTUAL))
	$(info BUILD DEBUG:                                        $(DEBUG))
	$(info ===========================================================)

inf_build:
	$(info >>>>> BUILDING <<<<<)

inf_complete:
	$(info ================= Ember Build Successful! =================)
	$(info  )

$(PCH_GCH): $(PCH)
	$(CXX) $(PCH)

######################################################################
# PATTERNS
######################################################################

obj/%.o: src/%.cpp
	$(CXX) -c $(CXXFLAGS) $(BUILD_OPTIONS) $< -o $@ $(EMBER_INCLUDE_FLAGS)

######################################################################
.PHONY: init, clean, package, install-virtual, inf_start, inf_start_build, inf_build_complete