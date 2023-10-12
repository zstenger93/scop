#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "headers.hpp"

class Object {
   public:
	Mtl mtl;
	std::string name;
	unsigned int texture;
	bool hasSlash = false;
	RenderMode renderMode = FILLED;
	std::vector<glm::vec3> normals;	 // vn aka normals for light calculations
	std::vector<Uv> uv;				 // vt aka uv coordinates

	std::vector<Vertex> vertices;				 // triangle ad square coordinates
	std::vector<std::vector<int>> faces;		 // contains each from the obj file
	std::vector<std::vector<int>> uv_index;		 // indexes for uv coordinates from each face
	std::vector<std::vector<Vertex>> triangles;	 // contains all shapes for now
	std::vector<float> Triangles, unpreaparedSquares, Squares;	// converting squares to triangles

	GLuint VAO_triangles, VBO_triangles, VAO_squares, VBO_squares,
		normalVBO;	// vertex arrays and buffers
};

void createVaoVbo(Object &object);

#endif