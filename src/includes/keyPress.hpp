#ifndef KEYPRESS_HPP
#define KEYPRESS_HPP

#include "camera.hpp"
#include "headers.hpp"

void keyPressHandler_Camera(GLFWwindow *window, RenderMode &renderMode, Camera &camera);
glm::mat4 keyPressHandler_ObjectCenterRotation(GLFWwindow *window, std::vector<float> &Triangles,
											   std::vector<float> &Squares, glm::mat4 &model);
glm::vec3 calculateCenter(const std::vector<float> &triangles);

#endif