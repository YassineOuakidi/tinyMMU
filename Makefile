# Makefile for Paging Simulation Project

# Compiler and flags
CC       := gcc
CFLAGS   :=  -Iinc -g

# Directories
SRCDIR   := src
INCDIR   := inc
TESTDIR  := test
BINDIR   := bin

# Target executable
TARGET   := test_paging

# Source files
SRC_FILES := \
	$(SRCDIR)/bitmap.c \
	$(SRCDIR)/bitmap_pmm.c \
	$(SRCDIR)/frame_allocator.c \
	$(SRCDIR)/map.c \
	$(SRCDIR)/translate.c \
	$(SRCDIR)/unmap.c \
	$(TESTDIR)/main.c

# Object files (one .o per source)
OBJ_FILES := $(patsubst %.c,%.o,$(SRC_FILES))

# Default rule
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c sources in $(SRCDIR)
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile .c sources in $(TESTDIR)
$(TESTDIR)/%.o: $(TESTDIR)/%.c
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean up build artifacts
clean:
	rm -f $(OBJ_FILES) $(TARGET)

.PHONY: all clean
