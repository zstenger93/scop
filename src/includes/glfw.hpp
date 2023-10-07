#ifndef GLFW_HPP
#define GLFW_HPP

#include "camera.hpp"
#include "headers.hpp"

/*
    setting up GLFW and creating the first window, other
    than that mouse handling functions.
*/

void initGLFW();
GLFWwindow *createWindow();

void framebuffer_size_callback(GLFWwindow *window, int width, int heigth);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

#endif