#ifndef HEADERS_HPP
#define HEADERS_HPP

/*
	Header file collection for standard libraries and
	for installed extra libraries like GLFW, GLAD, GLM
*/

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

#define WINDOW_WIDTH 3200
#define WINDOW_HEIGTH 1800


enum RenderMode { WIREFRAME, POINTS, FILLED };

struct Vertex {
	float x, y, z, texX, texY, normalX, normalY, normalZ;
};

struct Faces {
	int vertex, uv, normal;
};

struct Uv {
	float u, v, w;
};

struct Normal {
	float normalX, normalY, normalZ;
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

struct Light {
    Ka ambientIntensity;
    Kd diffuseIntensity;
    Ks specularIntensity;
    Normal lightDirection;
};

struct Mtl {
	Ka ka;
	Kd kd;
	Ks ks;
	float Ns, Ni, d;
	int illum;
};

// struct Object {
// 	std::string name;
// };

#endif