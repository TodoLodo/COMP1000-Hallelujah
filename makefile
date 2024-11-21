# Compiler and flags
CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic
LDFLAGS =

# Conditional compilation for BORDERLESS
ifeq ($(BORDERLESS), 1)
    CFLAGS += -DBORDERLESS
endif

# Directories
SRCDIR = src
INCDIR = include
LIBDIR = lib
BINDIR = bin
OBJDIR = obj
TESTDIR = test

# External libraries and your object files
LIB_SRC = $(wildcard $(LIBDIR)/*.c)
LIB_OBJ = $(LIB_SRC:$(LIBDIR)/%.c=$(OBJDIR)/%.o)

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Test files
TEST_SRC = $(wildcard $(TESTDIR)/*.c)
TEST_OBJ = $(TEST_SRC:$(TESTDIR)/%.c=$(OBJDIR)/%.o)

# Executable name
EXE = $(BINDIR)/escape

# Build target
all: $(EXE)

# Link the final binary
$(EXE): $(OBJ) $(LIB_OBJ) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIB_OBJ)

# Compile your source files into the obj directory
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBDIR) -c $< -o $@

# Compile external library files into the obj directory
$(OBJDIR)/%.o: $(LIBDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBDIR) -c $< -o $@

# Compile test files into the obj directory
$(OBJDIR)/%.o: $(TESTDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBDIR) -c $< -o $@

# Ensure bin and obj directories exist
$(BINDIR) $(OBJDIR):
	mkdir -p $@

# Clean target to remove generated files
clean:
	rm -f $(OBJDIR)/*.o $(EXE) $(BINDIR)/test_*

# Test targets
test: test_utils test_grid

test_utils: $(OBJDIR)/test_utils.o $(LIB_OBJ) $(OBJDIR)/utils.o
	$(CC) $(CFLAGS) -o $(BINDIR)/test_utils $(OBJDIR)/test_utils.o $(LIB_OBJ) $(OBJDIR)/utils.o
	$(BINDIR)/test_utils

test_grid: $(OBJDIR)/test_grid.o $(LIB_OBJ) $(OBJDIR)/grid.o
	$(CC) $(CFLAGS) -o $(BINDIR)/test_grid $(OBJDIR)/test_grid.o $(LIB_OBJ) $(OBJDIR)/grid.o
	$(BINDIR)/test_grid

# Phony targets
.PHONY: all clean test test_utils test_grid
