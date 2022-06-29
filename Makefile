TARGET = oblivion

CC = gcc
CFLAGS = -std=c18 -pipe
RELEASE_CFLAGS = -O2 -march=native -flto -DNDEBUG
DEBUG_CFLAGS = -O0 -g -DDEBUG -fsanitize=address,leak,undefined

INCLUDES =
LFLAGS =
LIBS =

SRC_DIR = ./src
OBJ_DIR = ./obj
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CFLAGS += $(RELEASE_CFLAGS)
CFLAGS += -Wall -Wextra -pedantic -pedantic-errors -Wformat=2 -Wshadow	\
	  -Wstrict-prototypes -Wstrict-overflow=2 -Wredundant-decls	\
	  -Wnested-externs -Wfloat-equal -Wpointer-arith -Wvla -Wundef	\
	  -Wcast-qual -Winit-self -Wwrite-strings -Wlogical-op

CLANGD_FILE = compile_flags.txt
CLANGD_CFLAGS = $(CFLAGS) -Wno-unused-function -Wno-empty-translation-unit

default: $(TARGET)

debug: CFLAGS := $(filter-out $(RELEASE_CFLAGS), $(CFLAGS))
debug: CFLAGS += $(DEBUG_CFLAGS)
debug: $(TARGET)

$(TARGET): $(CLANGD_FILE)
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir $@

$(CLANGD_FILE):
	@echo "$(CLANGD_CFLAGS)" | xargs -n 1 > $@

.PHONY: clean
clean:
	$(RM) -r $(OBJ_DIR)
	$(RM) $(TARGET) $(CLANGD_FILE) *~ gmon.out .clangd
