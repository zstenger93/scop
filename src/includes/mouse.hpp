#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "headers.hpp"

class MouseHandler {
   public:
	float rotationAngleX = 0.0f;
	float rotationAngleY = 0.0f;
	double lastXPos = 0.0;
	double lastYPos = 0.0;
	bool mouseMoved = false;

	void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	void preventFlip(MouseHandler* handler);
	void setSensitivity(MouseHandler* handler, double& deltaX, double& deltaY, float sensitivity);
};

#endif