## ---------------------------- EMBER ----------------------------- ## 

######################################################################
# VARIABLES
######################################################################

# Compile
CXXFLAGS = -Wall -O3 -g

# CPP Project Files
CPP_CORE = $(wildcard src/Core/*.cpp)

# HDR Project Files
HDR_BASE = $(wildcard src/*.h)
HDR_CORE = $(wildcard src/Core/*.h)

# Composition
CPP = $(CPP_CORE)
HDR = $(HDR_BASE) $(HDR_CORE)
TMP := $(subst src/,obj/,$(CPP))
OBJ := $(subst .cpp,.o,$(TMP))

# CMD Util
MD = mkdir -p

######################################################################
# TARGETS
######################################################################

# PRIMARY BUILD TARGET
Ember: clean init $(OBJ) $(HDR)
	$(CXX) $(CXXFLAGS) $(OBJ) -o Ember

######################################################################

init:
	${MD} obj
	${MD} obj/Core

clean:
	rm -f $(OBJ) Ember

######################################################################
# PATTERNS
######################################################################

obj/%.o: src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

######################################################################
.PHONY: init, clean