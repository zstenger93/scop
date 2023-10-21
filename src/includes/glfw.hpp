#ifndef GLFW_HPP
#define GLFW_HPP

#include "camera.hpp"
#include "headers.hpp"
#include "object.hpp"

/*
    setting up GLFW and creating the first window, other
    than that mouse handling functions.
*/

void initGLFW();
GLFWwindow *createWindow(Object &object);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow *window, int width, int heigth);

#endif