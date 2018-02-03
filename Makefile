# Main Flags

CC = g++
GCC_FLAGS = -Wall -pedantic -std=c++11 -O3
OBJECTS = main.o shader_init.o vec.o mat.o

# OS check

OS := $(shell uname)

ifeq ($(OS), Darwin)
	OPENGL = -framework OpenGL
	GLUT_FRAMEWORK = -framework GLUT
	GCC_FLAGS += -Wno-deprecated-declarations
else ifeq ($(OS), Linux)
	OPENGL_FLAG = -lGL
	GLUT_FRAMEWORK = -lglut
endif

# Targets

program: $(OBJECTS)
	$(CC) $(GCC_FLAGS) $(OBJECTS) -o program $(OPENGL) $(GLUT_FRAMEWORK)

main.o: main.cpp graphics.hpp physics.hpp
	$(CC) $(GCC_FLAGS) -c main.cpp

vec.o: graphics.hpp vec.hpp vec.cpp
	$(CC) $(GCC_FLAGS) -c vec.cpp

mat.o: vec.hpp mat.hpp mat.cpp
	$(CC) $(GCC_FLAGS) -c mat.cpp

shader_init.o: shader_init.cpp graphics.hpp
	$(CC) $(GCC_FLAGS) -c shader_init.cpp

clean:
	@ rm -f program -r program.dSYM *.o
