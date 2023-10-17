##
## Variables
##
CC = g++
SRC_DIR = src
BUILD_DIR = build
WARNINGS =-Wall -Wextra -Wshadow -Wconversion
ALLEGRO_TAGS := -lallegro -lallegro_font -lallegro_primitives -lallegro_image -lallegro_ttf
LIBS_TAGS := $(ALLEGRO_TAGS) -pthread
C_FLAGS = -O2 $(WARNINGS) $(LIBS_TAGS) 

##
## OS Variables
##
ifeq '$(findstring ;,$(PATH))' ';'
  OS := PlainWindows
else
  OS := $(shell uname 2>/dev/null || echo Unknown)
  OS := $(patsubst CYGWIN%,Cygwin,$(OS))
  OS := $(patsubst MSYS%,MSYS,$(OS))
  OS := $(patsubst MINGW%,MINGW,$(OS))
endif

##
## Commands and Files
##
ifeq ($(OS), PlainWindows)
  TARGET = executable.exe
  RM_COMMAND = del /q /f
  CLEAN_PATH = *.o
  SOURCE_FILES = src\main.cpp src\physics\physics.hpp #Por o diretorio de todos os arquivos .cpp
  O_FILES = $(subst src\,build\,$(SOURCE_FILES:.cpp=.o))
else
  TARGET = executable.out
  RM_COMMAND = rm -f
  MAKE_DIR = mkdir -p
  SOURCE_FILES = $(shell find $(SRC_DIR) -type f -name \*.cpp)
  O_FILES = $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCE_FILES:.cpp=.o))
endif

##
## Targets
##
$(TARGET): $(O_FILES)
	@$(MAKE_DIR) $(dir $@)
	@echo compiling executable...
	@$(CC) $^ -o $(TARGET) $(C_FLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(MAKE_DIR) $(dir $@)
	@echo compiling $@
	@$(CC) $(C_FLAGS) -c -o $@ $<

$(BUILD_DIR)\\%.o: $(SRC_DIR)\%.cpp
	@$(MAKE_DIR) $(dir $@)
	@echo compiling $@
	@$(CC) $(C_FLAGS) -c -o $@ $<

##
## Commands
##
build: $(TARGET)

run:
	./$(TARGET)

clean:
	@echo deleting... $(O_FILES)
	@$(RM_COMMAND) $(O_FILES) $(TARGET)

test:
	@echo $(OS)
	@echo $(SOURCE_FILES)
	@echo $(O_FILES)
	@echo $(TARGET)

.PHONY: clean build run