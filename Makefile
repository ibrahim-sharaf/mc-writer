#
# Makefile to build mc-writer
# Author: Ibarhim Sharaf
#

# Tools
COMPILER 		= g++
AR 		 		= ar rcs

# To include path.
INC_PATH		= -Iinc

# Compiler flags.
CFLAGS 			= -Wall ${INC_PATH}

# executable.
EXE 			= mc-writer.exe

# Source Paths
SRC_PATH        = src
SRCLIB_PATH     = src/srclib

# Object Paths
OBJ_PATH 		= obj
S_LIB_OBJ_PATH 	= static/obj

# Binary and Static lib paths
S_LIB_PATH 		= static/lib
BIN_PATH 		= bin

STATIC = static

# Needed path for output
PATHS_TO_CREATE = $(S_LIB_OBJ_PATH) $(S_LIB_PATH) $(OBJ_PATH) $(BIN_PATH)

# Name of source files
SRCLIB  =  $(wildcard $(SRCLIB_PATH)/*.cpp)
SRC     =  $(wildcard $(SRC_PATH)/*.cpp)

# Naming object files
OBJ     =  $(subst $(SRC_PATH)/, $(OBJ_PATH)/, $(SRC:.cpp=.o))
OBJLIB  =  $(subst $(SRCLIB_PATH)/, $(S_LIB_OBJ_PATH)/, $(SRCLIB:.cpp=.o))

# Naming static link libraries
LIB     =  $(subst $(SRCLIB_PATH)/, $(S_LIB_PATH)/lib, $(SRCLIB:.cpp=.a))
TOLINK  =  $(subst $(SRCLIB_PATH)/, -l, $(SRCLIB:.cpp=))

# build executable by default
all: $(BIN_PATH)/$(EXE)

# Build excutable from object files
$(BIN_PATH)/$(EXE): ${OBJ} ${LIB} ${OBJLIB} | $(BIN_PATH)
	$(COMPILER) ${OBJ} -L./$(S_LIB_PATH) ${TOLINK} -o $@ 

# Build object form source
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp | $(OBJ_PATH)
	$(COMPILER) $(CFLAGS) -c $<  -o $@

# Build static link libraries
$(S_LIB_PATH)/lib%.a : $(S_LIB_OBJ_PATH)/%.o | $(S_LIB_PATH)
	$(AR) $@ $<
$(S_LIB_OBJ_PATH)/%.o : $(SRCLIB_PATH)/%.cpp | $(S_LIB_OBJ_PATH)
	$(COMPILER) $(CFLAGS) -c $< -o $@

# Create needed paths for outputs. 
$(PATHS_TO_CREATE):
	@if not exist "$@" mkdir "$@"

# Adjust path names for the del command
S_LIB_OBJ_PATH2 	= $(subst /,\, $(S_LIB_OBJ_PATH))
S_LIB_PATH2 		= $(subst /,\, $(S_LIB_PATH))

# clear the ouputs
clean: 

	if exist $(S_LIB_OBJ_PATH2)\* del /q $(S_LIB_OBJ_PATH2)\*
	if exist $(S_LIB_OBJ_PATH2) rd $(S_LIB_OBJ_PATH2)

	if exist $(S_LIB_PATH2)\* del /q $(S_LIB_PATH2)\*
	if exist $(S_LIB_PATH2) rd $(S_LIB_PATH2)
	
	if exist $(OBJ_PATH)\* del /q $(OBJ_PATH)\*
	if exist $(OBJ_PATH) rd $(OBJ_PATH)

	if exist $(BIN_PATH)\* del /q $(BIN_PATH)\*
	if exist $(BIN_PATH) rd $(BIN_PATH)

	if exist $(STATIC) rd $(STATIC)