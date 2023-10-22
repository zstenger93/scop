#ifndef HEADERS_HPP
#define HEADERS_HPP

/*
	Header file collection for standard libraries and
	for installed extra libraries like GLFW, GLAD, GLM
*/
#define GL_SILENCE_DEPRECATION
#include </Users/zstenger/.brew/Cellar/glfw/3.3.8/include/GLFW/glfw3.h>

#include <OpenGL/OpenGL.h>

#include </Users/zstenger/.brew/Cellar/glm/0.9.9.8/include/glm/glm.hpp>
#include </Users/zstenger/.brew/Cellar/glm/0.9.9.8/include/glm/gtc/matrix_transform.hpp>
#include </Users/zstenger/.brew/Cellar/glm/0.9.9.8/include/glm/gtc/type_ptr.hpp>
#include <cmath>
#include <csignal>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../includes/glad/glad.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#define WINDOW_WIDTH 3200
#define WINDOW_HEIGHT 1800

enum RenderMode { WIREFRAME, POINTS, FILLED };

struct Vertex {
	float x, y, z, texX, texY, normalX, normalY, normalZ;
};

struct Uv {
	float u, v, w;
};

struct Ka {
	float r, g, b;
};

struct Kd {
	float r, g, b;
};

struct Ks {
	float r, g, b;
};

struct Mtl {
	Ka ka;
	Kd kd;
	Ks ks;
	float Ns, Ni, d;
	int illum;
};

#endif