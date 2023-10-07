#ifndef ERRORLOG_HPP
#define ERRORLOG_HPP

#include "headers.hpp"

/*
	You can wrap this beauty around functions which ones aren't
	returning anything (otherwise you won't have access to the
	returned value) and it will clear the OpenGL error until
	that point, if any. Then catch, immediatly print the error
	and exit the program.
*/

#define ASSERT(x)       \
	if (!(x)) {         \
		raise(SIGTRAP); \
	}

#define GLCall(x)   \
	GLClearError(); \
	x;              \
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError() {
	while (glGetError())
		;
}

static bool GLLogCall(const char *function, const char *file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ": " << line
				  << std::endl;
		return false;
	}
	return true;
}

#endif