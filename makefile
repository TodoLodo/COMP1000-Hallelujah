# Compiler and flags
CC = gcc
COMMON_CFLAGS = -Wall -Werror -ansi -pedantic
CFLAGS = $(COMMON_CFLAGS)
LDFLAGS = 

# Conditional compilation for PULL
ifeq ($(PULL), 1)
	CFLAGS += -DPULL
endif

# Directories
SRCDIR = src
INCDIR = include
LIBDIR = lib
BINDIR = bin
OBJDIR = build
TESTDIR = tests

# File extensions and patterns
SRC = $(wildcard $(SRCDIR)/*.c)
LIB_SRC = $(wildcard $(LIBDIR)/*.c)
TEST_SRC = $(wildcard $(TESTDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
LIB_OBJ = $(LIB_SRC:$(LIBDIR)/%.c=$(OBJDIR)/%.o)
TEST_OBJ = $(TEST_SRC:$(TESTDIR)/%.c=$(OBJDIR)/%.o)

# Dependency files
DEP = $(OBJ:.o=.d) $(LIB_OBJ:.o=.d) $(TEST_OBJ:.o=.d)

# Executable name
EXE = $(BINDIR)/box

# Build target
all: $(EXE)

# Link the final binary
$(EXE): $(OBJ) $(LIB_OBJ) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIB_OBJ) $(LDFLAGS)

# Compile source files into the obj directory
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBDIR) -MMD -MF $(@:.o=.d) -c $< -o $@

# Compile library files into the obj directory
$(OBJDIR)/%.o: $(LIBDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBDIR) -MMD -MF $(@:.o=.d) -c $< -o $@

# Compile test files into the obj directory
$(OBJDIR)/%.o: $(TESTDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(LIBDIR) -MMD -MF $(@:.o=.d) -c $< -o $@

# Ensure directories exist
$(BINDIR) $(OBJDIR):
	mkdir -p $@

# Test targets (general rule)
tests: $(TEST_SRC:$(TESTDIR)/%.c=$(BINDIR)/test_%)

$(BINDIR)/test_%: $(OBJDIR)/test_%.o $(LIB_OBJ) $(OBJDIR)/%.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@$@

# Clean target
clean:
	rm -rf $(OBJDIR) $(BINDIR) $(DEP)

# Include dependency files
-include $(DEP)

# Phony targets
.PHONY: all clean test