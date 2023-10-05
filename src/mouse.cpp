#include "includes/mouse.hpp"

#include "includes/object.hpp"

void MouseHandler::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	MouseHandler* handler = static_cast<MouseHandler*>(glfwGetWindowUserPointer(window));
	_xpos = xpos, _ypos = ypos;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		updatePosition(handler);
		calculateRotationSpeed(handler);
		preventFlip(handler);
		updateHandler(handler);
	} else
		stopRotation(handler);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		double deltaX = _xpos - handler->lastXPos;
		double deltaY = _ypos - handler->lastYPos;

		float translationSpeed = 0.01f;
		translateX = -0.0f;
		translateY = -deltaY * translationSpeed;
		translateZ = +deltaX * translationSpeed;
	} else {
		translateX = 0.0f;
		translateY = 0.0f;
		translateZ = 0.0f;
	}
	handler->lastXPos = _xpos;
	handler->lastYPos = _ypos;
}

void MouseHandler::updatePosition(MouseHandler* handler) {
	sensitivity = 0.005f;
	if (handler->lastXPos != 0.0 && handler->lastYPos != 0.0 &&
		(handler->lastXPos != _xpos || handler->lastYPos != _ypos)) {
		handler->mouseMoved = true;
	} else {
		handler->mouseMoved = false;
		sensitivity = 0.0f;
	}
	deltaX = _xpos - handler->lastXPos;
	deltaY = _ypos - handler->lastYPos;
}

void MouseHandler::preventFlip(MouseHandler* handler) {
	if (handler->rotationAngleX > 360.0f)
		handler->rotationAngleX -= 360.0f;
	else if (handler->rotationAngleX < -360.0f)
		handler->rotationAngleX += 360.0f;

	if (handler->rotationAngleY > 360.0f)
		handler->rotationAngleY -= 360.0f;
	else if (handler->rotationAngleY < -360.0f)
		handler->rotationAngleY += 360.0f;
}

void MouseHandler::calculateRotationSpeed(MouseHandler* handler) {
	handler->rotationAngleX += deltaX * sensitivity;
	handler->rotationAngleY += deltaY * sensitivity;
}

void MouseHandler::updateHandler(MouseHandler* handler) {
	handler->lastXPos = _xpos;
	handler->lastYPos = _ypos;
}

void MouseHandler::stopRotation(MouseHandler* handler) {
	handler->rotationAngleX = 0.0f;
	handler->rotationAngleY = 0.0f;
	handler->mouseMoved = false;
}

void MouseHandler::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	std::cout << "Scroll Offset y: " << yoffset << std::endl;
	MouseHandler* handler = static_cast<MouseHandler*>(glfwGetWindowUserPointer(window));

	Object* objInstance = handler->object;
	if (objInstance->zoom - yoffset > 2 && objInstance->zoom - yoffset < 300)
		objInstance->zoom -= static_cast<float>(yoffset) * objInstance->zoomSpeed;
}

void Object::rotation(MouseHandler& mouseHandler) {
	glm::quat rotationX =
		glm::angleAxis(glm::radians(mouseHandler.rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat rotationY =
		glm::angleAxis(glm::radians(mouseHandler.rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat combinedRotation = rotationY * rotationX;
	glm::mat4 rotationMatrix = glm::mat4_cast(combinedRotation);

	translationMatrix = glm::translate(
		glm::mat4(1.0f),
		glm::vec3(mouseHandler.translateX, mouseHandler.translateY, mouseHandler.translateZ));
	rotationMatrix = translationMatrix * rotationMatrix;

	glMultMatrixf(glm::value_ptr(rotationMatrix));
}
