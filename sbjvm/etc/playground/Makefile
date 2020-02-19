# compiled to be used (can be others like cl, clang, borland C++, ...)
CXX=g++
# compiling using C++11 
CFLAGS= --std=c++11
# add symbol table for debbuging (do not use this in production)
CFLAGS+= -g
# you can call it whatever you want
PROG_NAME=issues
# this will depend on the OS becuse this is the produced executable name
EXE_NAME=$(PROG_NAME)
# directory containing object and dependency files
OBJ_DIR=obj
# this points to the main program root
MAIN_PROJ_ROOT=../..
# points to the main program include folder containing hpp
MAIN_PROG_INC=$(MAIN_PROJ_ROOT)/include
# this helps us reuse the objects files (they must be compiled first)
MAIN_PROG_OBJ=$(MAIN_PROJ_ROOT)/obj
# folder contaning the sources files for INI parser
INI_PROJ_PATH=$(MAIN_PROJ_ROOT)/etc/vendor/inih
# this will build the list of all object files from the main program
MAIN_OBJ_LIST=$(addprefix $(MAIN_PROG_OBJ)/, JavaClass.o Security.o ClassPrinter.o)
# tell gcc that our static libs (.a files) are in the obj folder
CLIBS=-L./$(OBJ_DIR)

ifeq ($(OS),Windows_NT)
	EXE_NAME=$(PROG_NAME).exe
	CLEAR_SCRIPT_CMD=rmdir /s /q $(OBJ_DIR) && del $(EXE_NAME)
else
	CLEAR_SCRIPT_CMD=rm -rf $(OBJ_DIR) && rm $(EXE_NAME)
endif

all: premake $(OBJ_DIR)/libinih.a $(EXE_NAME)

$(EXE_NAME): $(OBJ_DIR)/main.o
	$(CXX) -o $(EXE_NAME) $(OBJ_DIR)/main.o $(MAIN_OBJ_LIST) \
		$(CLIBS) -static -linih

$(OBJ_DIR)/main.o: main.cpp
	$(CXX) -c main.cpp $(CFLAGS) -o $(OBJ_DIR)/main.o

### SUBMODULE: inih

$(OBJ_DIR)/ini.o: $(INI_PROJ_PATH)/ini.c $(INI_PROJ_PATH)/ini.h
	$(CXX) $(CFLAGS) -c $(INI_PROJ_PATH)/ini.c -o $(OBJ_DIR)/ini.o

$(OBJ_DIR)/INIReader.o: $(INI_PROJ_PATH)/cpp/INIReader.cpp $(INI_PROJ_PATH)/cpp/INIReader.h
	$(CXX) $(CFLAGS) -c $(INI_PROJ_PATH)/cpp/INIReader.cpp -o $(OBJ_DIR)/INIReader.o

$(OBJ_DIR)/inih.a: $(OBJ_DIR)/ini.o $(OBJ_DIR)/INIReader.o
	ar rvs $(OBJ_DIR)/libinih.a $(OBJ_DIR)/ini.o $(OBJ_DIR)/INIReader.o

premake:
ifeq ($(OS),Windows_NT)
	"make_scripts/premake.bat"
else
	chmod +x make_scripts/premake.sh
	./premake.sh
endif

class:
	javac -source 7 -target 7 java_test/*.java

clear:
	$(CLEAR_SCRIPT_CMD)