# compilador a ser utilizado (podem ser outros como cl, clang, borland c++, etc...)
CXX=g++
# utilizar c++11 como padrão
CPPFLAGS=--std=c++11
# exportar a tabela de símbolos para o debug
CPPFLAGS+=-g
# mostrar todos os warnings
CPPFLAGS+=-Wall
CPPFLAGS+=-MMD -MP
LDFLAGS=
LDLIBS=
# mode do arquivo executável (pode variar de SO)
EXEC_FILE=
# pasta onde serão armazenados os arquivos .o e .d gerados
OBJ_FOLDER_LOC=obj
# pasta onde será armazenado o executável
BIN_FOLDER_LOC=bin
# pasta onde estão os arquivos .hpp (útil caso utilizamos módulos deste programa em outros programas)
INC_FOLDER_LOC=include
# pasta onde se encontram os scripts auxiliares (ex: criar pastas necessárias)
SCRIPT_FOLDER_LOC=etc
# pasta com os arquivos de teste em Java/Jasmin para serem compilados
JTS_FOLDER_LOC=tests/criss
SRC_FILE_LIST=$(wildcard *.cpp)
OBJ_FILE_LIST=$(SRC_FILE_LIST:%.cpp=$(OBJ_FOLDER_LOC)/%.o)
DEP_FILE_LIST=$(OBJ_FILE_LIST:.o=.d)
PREMAKE_SCRIPT_CMD=

ifeq ($(OS),Windows_NT)
	EXEC_FILE=jvm.exe
	PREMAKE_SCRIPT_CMD="$(SCRIPT_FOLDER_LOC)/premake.bat"
	CLEAR_SCRIPT_CMD=rmdir /s /q $(OBJ_FOLDER_LOC) $(BIN_FOLDER_LOC)
else
	EXEC_FILE=jvm
	LINUX_PREMAKE_SH=$(SCRIPT_FOLDER_LOC)/premake.sh
	PREMAKE_SCRIPT_CMD=chmod +x $(LINUX_PREMAKE_SH) && ./$(LINUX_PREMAKE_SH)
	LINUX_CLEAR_SH=$(SCRIPT_FOLDER_LOC)/clear.sh
	CLEAR_SCRIPT_CMD=rm -rf $(OBJ_FOLDER_LOC) $(BIN_FOLDER_LOC)
endif

.PHONY: all

all: pre_build $(BIN_FOLDER_LOC)/$(EXEC_FILE)

pre_build:
	$(PREMAKE_SCRIPT_CMD)

$(BIN_FOLDER_LOC)/$(EXEC_FILE): $(OBJ_FILE_LIST)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_FOLDER_LOC)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) -o $@ -c $<

-include $(DEP_FILE_LIST)

class:
	javac -source 7 -target 7 $(JTS_FOLDER_LOC)/*.java
	java -jar etc/jasmin-2.4/jasmin.jar -d $(JTS_FOLDER_LOC) $(JTS_FOLDER_LOC)/*.j

docs:
	doxygen JVMDocs

clear:
	$(CLEAR_SCRIPT_CMD)