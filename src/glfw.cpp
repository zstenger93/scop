#include "includes/headers.hpp"
#include "includes/object.hpp"
#include "includes/mouse.hpp"

void Object::initGLFW(Object& object) {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}
	object.setWindow();
	GLFWwindow* window = object.getWindow();
	if (!window) {
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
	object.setPerspectiveProjection(1600, 1200);
}

void Object::runGLFW(Object& object) {
	GLFWwindow* window = object.getWindow();

	MouseHandler mouseHandler;
    glfwSetWindowUserPointer(window, &mouseHandler);
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
        MouseHandler* handler = static_cast<MouseHandler*>(glfwGetWindowUserPointer(window));
        handler->mouseCallback(window, xpos, ypos);
    });
    
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glRotatef(mouseHandler.rotationAngleX, 1.0f, 0.0f, 0.0f);
        glRotatef(mouseHandler.rotationAngleY, 0.0f, 1.0f, 0.0f);
		object.renderShape();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}

void Object::setPerspectiveProjection(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	float fov = 90.0f;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	glm::mat4 projectionMatrix =
		glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);

	glLoadMatrixf(glm::value_ptr(projectionMatrix));

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.0f, 0.0f, -5.0f);
}
