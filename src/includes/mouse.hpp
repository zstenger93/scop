#include "headers.hpp"

class MouseHandler {
   public:
	float rotationAngleX = 0.0f;
	float rotationAngleY = 0.0f;
	double lastXPos = 0.0;
	double lastYPos = 0.0;
	bool mouseMoved = false;

	static void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
		MouseHandler* handler = static_cast<MouseHandler*>(glfwGetWindowUserPointer(window));
		float sensitivity = 0.005f;

		if (handler->lastXPos != 0.0 && handler->lastYPos != 0.0 &&
			(handler->lastXPos != xpos || handler->lastYPos != ypos)) {
			handler->mouseMoved = true;
		} else {
			handler->mouseMoved = false;
			sensitivity = 0.0f;
		}
		if (!handler->mouseMoved) {
			handler->lastXPos = xpos;
			handler->lastYPos = ypos;
			handler->mouseMoved = true;
		}

		double deltaX = xpos - handler->lastXPos;
		double deltaY = ypos - handler->lastYPos;

		handler->rotationAngleX += deltaX * sensitivity;
		handler->rotationAngleY += deltaY * sensitivity;

		if (handler->rotationAngleX > 360.0f) {
			handler->rotationAngleX += 360.0f;
		} else if (handler->rotationAngleX < -360.0f) {
			handler->rotationAngleX -= 360.0f;
		}

		if (handler->rotationAngleY > 360.0f) {
			handler->rotationAngleY += 360.0f;
		} else if (handler->rotationAngleY < -360.0f) {
			handler->rotationAngleY -= 360.0f;
		}

		handler->lastXPos = xpos;
		handler->lastYPos = ypos;
	}

	static void mouseStopCallback(GLFWwindow* window, int button, int action, int mods) {
		MouseHandler* handler = static_cast<MouseHandler*>(glfwGetWindowUserPointer(window));

		if (action == GLFW_PRESS) {
			if (!handler->mouseMoved) {
				// Mouse stopped moving, handle it here
				handler->rotationAngleX = 0.0f;
				handler->rotationAngleY = 0.0f;
			}
		}
	}
};