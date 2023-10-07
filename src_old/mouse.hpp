#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "headers.hpp"

class Object;

class MouseHandler {
   public:
	Object* object;

	float rotationAngleX = 0.0f;
	float rotationAngleY = 0.0f;
	float sensitivity = 0.0f;
	bool mouseMoved = false;
	double lastXPos = 0.0;
	double lastYPos = 0.0;
	double deltaY;
	double deltaX;
	double _xpos;
	double _ypos;

	float translateX;
	float translateY;
	float translateZ;

	void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	void updatePosition(MouseHandler* handler);
	void calculateRotationSpeed(MouseHandler* handler);
	void preventFlip(MouseHandler* handler);
	void updateHandler(MouseHandler* handler);
	void stopRotation(MouseHandler* handler);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif