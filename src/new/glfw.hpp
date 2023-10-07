#ifndef GLFW_HPP
#define GLFW_HPP

#include "../includes/headers.hpp"
#include "camera.hpp"



void initGLFW();
GLFWwindow *createWindow();

void framebuffer_size_callback(GLFWwindow *window, int width, int heigth);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

#endif