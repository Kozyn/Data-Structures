# Compiler
CC = gcc

# Directories
SRCDIR = src
OUTDIR = out
BINDIR = bin
HEADERDIR = header

# Executable name
EXEC = $(BINDIR)/main

# Source files
SOURCES = $(wildcard $(SRCDIR)/*.c)

# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OUTDIR)/%.o, $(SOURCES))

# Compiler flags
CFLAGS = -I$(HEADERDIR) -Wall -Wextra -Werror

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJECTS) -o $@

# Compile the source files into object files
$(OUTDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -rf $(OUTDIR) $(BINDIR)

#run executable
run: $(EXEC)
	./$(EXEC)

# Phony targets
.PHONY: all clean run