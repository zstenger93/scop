#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "headers.hpp"

class Object {
   public:
   std::string name;
   bool hasSlash = false;
	std::vector<glm::vec3> normals;
};

void createVaoVbo(GLuint &VAO_triangles, GLuint &VAO_squares, GLuint &VBO_triangles,
				  GLuint &VBO_squares, GLuint &normalVBO, std::vector<float> &Squares,
				  std::vector<float> &Triangles, std::vector<glm::vec3> &glmNormals);

#endif