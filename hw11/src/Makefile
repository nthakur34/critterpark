###################################################
# Advanced auto-magical makefile 
# Ben Mitchell
# 2015-10-13
#
# This makefile makes clever use of wildcards and pattern searching
# to auto-magically detect what files should be compiled as what.
#
# Assuming you use the expected naming conventions, it will figure
# out what should be tests and what should be "normal" executables,
# and compile everything appropriately.
#
# Test source files must end in "Test.c" 
# e.g. "unitTest.c" or "myFunctionTest.c"
#
# Binaries will be placed in ../bin with names that match the source
# file they were compiled from; e.g. hw6.c will generate ../bin/hw6,
# and unitTest.c will generate ../bin/unitTest
#
# You can change the stuff up top if you want; things like
# debug mode and file paths and default target are easy to switch.
# The rest of the file may be a bit confusing if you're not very
# familiar with make, so be more careful changing any of that
# stuff unless you know what you're doing.
#
###################################################

###############################
# enable/disable debugging flags for compiler (-g -O0, etc.)
# Set to 1 for debugging flags on,
# Set to 0 for debugging flags off
###############################
DEBUG_MODE = 0

# set a default target
default: test

###############################
# paths
###############################
# where to look for .c files
SRC_DIRS = .
# where to look for .h files
INC_DIRS = ../include
# where to put .o files
OBJ_DIR = ./obj
# where to put executables
BIN_DIR = ../bin

###############################
# universal flags
###############################
# C compiler
CC = gcc 
# C++ compiler
CPP = g++

# search path for #include directives
IFLAGS = $(patsubst %, -I%, $(INC_DIRS) $(SRC_DIRS) ) 

# standard compile flags (for C and C++)

ifeq ($(DEBUG_MODE),1) # for debugging
CFLAGS = -std=c99 -Wall -Wextra -pedantic $(IFLAGS) -O0 -g -fprofile-arcs -ftest-coverage  
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic $(IFLAGS) -O0 -g -fprofile-arcs -ftest-coverage  
else # normal compiler flags
CFLAGS = -std=c99 -Wall -Wextra -pedantic $(IFLAGS)
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic $(IFLAGS)
endif

# libraries to link against
LIBS = -lm


###################################################
###################################################
# NOTE: you probably shouldn't need to modify anything
# below this point, unless you really know what you're
# doing
###################################################
###################################################

###############################
# files
###############################
# figure out what source files we are using for what
INCLUDES := $(wildcard $(patsubst %, %/*.h*, $(INC_DIRS))) 
C_SOURCES := $(wildcard $(patsubst %, %/*.c, $(SRC_DIRS))) 
ifneq ($(strip $(C_SOURCES)),)
# don't try this if there aren't any C files, as it will hang waiting for input...
C_MAINS := $(shell grep -l "int main" $(C_SOURCES))
C_TESTS := $(filter %Test.c,$(C_MAINS)) 
C_NON_MAINS := $(shell grep -L "int main" $(C_SOURCES))
endif

CPP_SOURCES := $(wildcard $(patsubst %, %/*.cpp, $(SRC_DIRS))) 
ifneq ($(strip $(CPP_SOURCES)),)
# don't try this if there aren't any C++ files, as it will hang waiting for input...
CPP_MAINS := $(shell grep -l "int main" $(CPP_SOURCES))
CPP_TESTS := $(filter %Test.cpp,$(CPP_MAINS)) 
CPP_NON_MAINS := $(shell grep -L "int main" $(CPP_SOURCES))
endif

# figure out what executables we're going to want to build
C_EXECUTABLES := $(patsubst %.c, $(BIN_DIR)/%, $(C_MAINS))
C_TEST_EXECUTABLES := $(patsubst %.c, $(BIN_DIR)/%, $(C_TESTS))
CPP_EXECUTABLES := $(patsubst %.cpp, $(BIN_DIR)/%, $(CPP_MAINS))
CPP_TEST_EXECUTABLES := $(patsubst %.cpp, $(BIN_DIR)/%, $(CPP_TESTS))

# figure out what object files we'll need to build them
C_OBJECTS := $(patsubst $(SRC_DIRS)/%.c, $(OBJ_DIR)/%.o, $(C_SOURCES))
C_MAIN_OBJECTS := $(patsubst $(SRC_DIRS)/%.c, $(OBJ_DIR)/%.o, $(C_MAINS))
C_NON_MAIN_OBJECTS := $(patsubst $(SRC_DIRS)/%.c, $(OBJ_DIR)/%.o, $(C_NON_MAINS))
CPP_OBJECTS := $(patsubst $(SRC_DIRS)/%.cpp, $(OBJ_DIR)/%.o, $(CPP_SOURCES))
CPP_MAIN_OBJECTS := $(patsubst $(SRC_DIRS)/%.cpp, $(OBJ_DIR)/%.o, $(CPP_MAINS))
CPP_NON_MAIN_OBJECTS := $(patsubst $(SRC_DIRS)/%.cpp, $(OBJ_DIR)/%.o, $(CPP_NON_MAINS))

# also keep track of auto-generated dependency files
C_DEPFILES := $(patsubst $(SRC_DIRS)/%.c, $(OBJ_DIR)/%.cdep, $(C_SOURCES))
CPP_DEPFILES := $(patsubst $(SRC_DIRS)/%.cpp, $(OBJ_DIR)/%.cppdep, $(CPP_SOURCES))

###############################
# custom targets 
###############################

# all binaries
all: $(C_EXECUTABLES) $(CPP_EXECUTABLES)

# build and run tests
test: $(C_TEST_EXECUTABLES) $(CPP_TEST_EXECUTABLES)
	@echo ""
	@echo "Running tests..."
	@for i in $^; do echo "Running test for $$i: "; $$i; done

# to use gcov, we build and run the tests,
# then run gcov on the source files we want
# to check coverage of (be sure to make clean
# first)
gcov: test
	@echo ""
	@echo "Running gcov..."
	@for i in $(C_TESTS) $(CPP_TESTS); do gcov -o $(OBJ_DIR) $$i; done

###############################
# generic compile rules
###############################

# generic compile rule for building (linking) executables

# NOTE: this is a bit complicated, but it's trying to auto-detect
# whether to link in C mode or C++ mode...
$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(C_NON_MAIN_OBJECTS) $(CPP_NON_MAIN_OBJECTS) 
	@if [ ! -d $(BIN_DIR) ]; then mkdir $(BIN_DIR); fi
	$(if $(filter $@,$(C_EXECUTABLES)),\
		@echo Linking $@ as C...;\
		$(CC) $(CFLAGS) -o $@ $< $(C_NON_MAIN_OBJECTS) $(LIBS),\
		@echo Linking $@ as C++...;\
		$(CPP) $(CXXFLAGS) -o $@ $< $(CPP_NON_MAIN_OBJECTS) $(LIBS))

## C
#$(BIN_DIR)/%: $(C_NON_MAIN_OBJECTS) $(OBJ_DIR)/%.o
#	@if [ ! -d $(BIN_DIR) ]; then mkdir $(BIN_DIR); fi
#	@echo Linking $@ as C...
#	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

## C++
#$(BIN_DIR)/%: $(CPP_NON_MAIN_OBJECTS) $(OBJ_DIR)/%.o
#	@if [ ! -d $(BIN_DIR) ]; then mkdir $(BIN_DIR); fi
#	@echo Linking $@ as C++...
#	@$(CPP) $(CXXFLAGS) -o $@ $^ $(LIBS)


# generic compile rules for building (compiling) objects

# C
$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)/%.cdep
	@if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi
	@echo Compiling $< as C...
	@$(CC) $(CFLAGS) -c -o $@ $< 

# C++
$(OBJ_DIR)/%.o: %.cpp $(OBJ_DIR)/%.cppdep
	@if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi
	@echo Compiling $< as C++...
	@$(CPP) $(CXXFLAGS) -c -o $@ $< 


# rule for auto-generating dependency-tracking files
$(OBJ_DIR)/%.cdep: %.c
	@if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi
	@echo Updating dependencies for $<...
	@$(CC) -MM -MT $(OBJ_DIR)/$*.o $(CFLAGS) $< | \
		sed 's!\($(OBJ_DIR)/$*\)\.o[ :]*!\1.o $@ : !g' > $@

$(OBJ_DIR)/%.cppdep: %.cpp
	@if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi
	@echo Updating dependencies for $<...
	@$(CPP) -MM -MT $(OBJ_DIR)/$*.o $(CXXFLAGS) $< | \
		sed 's!\($(OBJ_DIR)/$*\)\.o[ :]*!\1.o $@ : !g' > $@

# include files containing (auto-generated) target-specific rules based on #includes
-include $(C_DEPFILES)
-include $(CPP_DEPFILES)

###############################
# "utility" rules
###############################
# this line says these targets aren't expected to generate files named after the target
.PHONY: clean checkVars test gcov all default

# target to check the contenst of our variables
checkVars:
	@echo C sources - \"$(C_SOURCES)\"; echo 
	@echo C mains - $(C_MAINS); echo 
	@echo C non-mains - $(C_NON_MAINS); echo 
	@echo C main_objects - $(C_MAIN_OBJECTS); echo 
	@echo C non-main_objects - $(C_NON_MAIN_OBJECTS); echo 
	@echo C executables - $(C_EXECUTABLES); echo 
	@echo C tests - $(C_TESTS); echo 
	@echo C test-executables - $(C_TEST_EXECUTABLES); echo 
	@echo C++ sources - $(CPP_SOURCES); echo 
	@echo C++ mains - $(CPP_MAINS); echo 
	@echo C++ non-mains - $(CPP_NON_MAINS); echo 
	@echo C++ main_objects - $(CPP_MAIN_OBJECTS); echo 
	@echo C++ non-main_objects - $(CPP_NON_MAIN_OBJECTS); echo 
	@echo C++ executables - $(CPP_EXECUTABLES); echo 
	@echo C++ tests - $(CPP_TESTS); echo 
	@echo C++ test-executables - $(CPP_TEST_EXECUTABLES); echo 

# clean up generated files
clean:
	@echo removing generated files...
	@rm -f $(C_OBJECTS) $(C_DEPFILES) $(CPP_OBJECTS) $(CPP_DEPFILES) $(OBJ_DIR)/*.gcda $(OBJ_DIR)/*.gcno *.gcda *.gcno *.gcov 
