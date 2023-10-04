#ifndef SHADER_HPP
#define SHADER_HPP

#include "headers.hpp"

class Shader {
   public:
	// GLuint shaderProgram;

	GLuint compileShader(GLenum shaderType, const char* shaderSource);
	GLuint createShaderProgram();
};

#endif