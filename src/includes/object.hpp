#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "headers.hpp"

class Object {
   public:
	Mtl mtl;
	std::string name;
	bool hasSlash = false;
	RenderMode renderMode = FILLED;
	std::vector<glm::vec3> normals;	 // vn aka normals for light calculations
	std::vector<Uv> uv;				 // vt aka uv coordinates

	std::vector<Vertex> vertices; // triangle ad square coordinates
	std::vector<std::vector<int>> faces;	 // contains each from the obj file
	std::vector<std::vector<int>> uv_index;	 // indexes for uv coordinates from each face
};

void createVaoVbo(GLuint &VAO_triangles, GLuint &VAO_squares, GLuint &VBO_triangles,
				  GLuint &VBO_squares, GLuint &normalVBO, std::vector<float> &Squares,
				  std::vector<float> &Triangles, std::vector<glm::vec3> &glmNormals);

#endif