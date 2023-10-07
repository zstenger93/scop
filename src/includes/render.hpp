#ifndef RENDER_HPP
#define RENDER_HPP

#include "headers.hpp"
#include "camera.hpp"
#include "shader.hpp"

void renderingLoop(GLFWwindow *window, Shader &shader, Camera &camera, RenderMode &renderMode,
				   unsigned int &texture, unsigned int &VAO_triangles, unsigned int &VAO_squares,
				   std::vector<float> &Triangles, std::vector<float> &Squares);
void processInput(GLFWwindow *window, Camera &camera);

#endif