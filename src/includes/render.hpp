#ifndef RENDER_HPP
#define RENDER_HPP

#include "camera.hpp"
#include "headers.hpp"
#include "shader.hpp"
#include "object.hpp"

void renderingLoop(GLFWwindow *window, Shader &shader, Camera &camera, Object &object);

#endif