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
EMBER_INCLUDE_FLAGS = -Isrc/Ember/Include -Isrc

# CPP Project Files
CPP_EMBER = $(wildcard src/Ember/*.cpp)
CPP_CORE = $(wildcard src/Ember/Core/*.cpp)

# PCH Project Files
PCH = src/EmberPCH.h
PCH_GCH = $(PCH).gch

# Composition
HDR = $(wildcard src/Ember/Include/*.h) src/*.h
CPP = $(CPP_EMBER) $(CPP_CORE)
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
# TARGETS
######################################################################

# PRIMARY BUILD TARGET
Ember: clean init $(PCH_GCH) $(OBJ) $(HDR) $(RGB_LIBRARY)
	ar x $(RGB_LIBRARY) && mv *.o $(RGB_LIBRARY_OBJ)
	ar -cvq libEmber.a $(OBJ) $(RGB_LIBRARY_OBJ)/*.o


######################################################################

$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIBDIR)

install-virtual:
	sudo apt-get install libsfml-dev

init:
	${MD} obj
	${MD} obj/Ember
	${MD} obj/Ember/Core
	${MD} $(RGB_LIBRARY_OBJ)

$(PCH_GCH): $(PCH)
	$(CXX) $(PCH)

clean:
	rm -f $(OBJ) libEmber.a

######################################################################
# PATTERNS
######################################################################

obj/%.o: src/%.cpp
	$(CXX) -c $(CXXFLAGS) $(BUILD_OPTIONS) $< -o $@ $(EMBER_INCLUDE_FLAGS)

######################################################################
.PHONY: init, clean, install-virtual