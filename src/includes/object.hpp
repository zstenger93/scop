#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "headers.hpp"

void createVaoVbo(GLuint &VAO_triangles, GLuint &VAO_squares, GLuint &VBO_triangles,
				  GLuint &VBO_squares, GLuint &normalVBO, std::vector<float> &Squares,
				  std::vector<float> &Triangles, std::vector<glm::vec3> &glmNormals);

#endif