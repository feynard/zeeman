#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <OpenGL/gl3.h>
#define __gl_h_

#include <GLUT/glut.h>

// Constants
const double pi = 3.14159265358979323846;

#include "vec.hpp"
#include "mat.hpp"

GLuint ShaderInit(const char* vertex_shader, const char* fragment_shader);

#define BUFFER_OFFSET(offset) ((GLvoid*) (offset))

#endif
