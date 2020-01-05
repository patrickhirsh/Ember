## ---------------------------- EMBER ----------------------------- ## 

######################################################################
# VARIABLES
######################################################################

# Compile
CXXFLAGS = -Wall -O3

# CPP Project Files
CPP_BASE = $(wildcard src/*.cpp)
CPP_EMBER = $(wildcard src/Ember/*.cpp)
CPP_CORE = $(wildcard src/Ember/Core/*.cpp)

# HDR Project Files
HDR_BASE = $(wildcard src/*.h)
HDR_EMBER = $(wildcard src/Ember*.h)
HDR_CORE = $(wildcard src/Ember/Core/*.h)

# Composition
CPP = $(CPP_BASE) $(CPP_EMBER) $(CPP_CORE)
HDR = $(HDR_BASE) $(HDR_EMBER) $(HDR_CORE)
TMP := $(subst src/,obj/,$(CPP))
OBJ := $(subst .cpp,.o,$(TMP))

# CMD Util
MD = mkdir -p

######################################################################
# TARGETS
######################################################################

# PRIMARY BUILD TARGET
Ember: clean init $(OBJ) $(HDR)
	ar -cvq libEmber.a $(OBJ)

######################################################################

init:
	${MD} obj
	${MD} obj/Ember
	${MD} obj/Ember/Core

clean:
	rm -f $(OBJ) libEmber.a

######################################################################
# PATTERNS
######################################################################

obj/%.o: src/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

######################################################################
.PHONY: init, clean