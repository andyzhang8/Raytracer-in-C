# Makefile for Raytracer Project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -lm

# Executable name
EXEC = raytracer

# Source files
SRCS = src/main.c src/render.c src/raytracer.c src/lighting.c src/camera.c \
       src/material.c src/object.c src/scene.c src/texture.c src/vector.c \
       src/postprocessing.c src/utils.c

# Header files
HDRS = src/render.h src/raytracer.h src/lighting.h src/camera.h \
       src/material.h src/object.h src/scene.h src/texture.h \
       src/vector.h src/postprocessing.h src/utils.h

# Object files
OBJS = $(SRCS:.c=.o)

# Build target
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Rule for compiling source files to object files
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)

# Run the raytracer
run: $(EXEC)
	./$(EXEC)
