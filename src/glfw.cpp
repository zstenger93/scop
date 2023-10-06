#include "includes/headers.hpp"
#include "includes/mouse.hpp"
#include "includes/object.hpp"
#include "includes/shader.hpp"
#include "includes/errorLog.hpp"

void Object::initGLFW(Object& object) {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	object.setWindow();
	GLFWwindow* window = object.getWindow();
	if (!window) return glfwTerminate();
	glfwMakeContextCurrent(window);
	object.setPerspectiveProjection(3200, 1800);
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(-1);
	}
}

void Object::runGLFW(Object& object) {
	GLFWwindow* window = object.getWindow();
	MouseHandler mouseHandler;

	mouseHandler.object = &object;
	object.loadTexture("textures/ok.jpg");
	glfwSetWindowUserPointer(window, &mouseHandler);
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		MouseHandler* handler = static_cast<MouseHandler*>(glfwGetWindowUserPointer(window));
		handler->mouseCallback(window, xpos, ypos);
	});
	glfwSetScrollCallback(window, MouseHandler::scrollCallback);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	object.centering();
	glm::vec3 objectCenter(centerX, centerY, centerZ);
	object.renderingLoop(object, objectCenter, mouseHandler);
	glfwTerminate();
}

void Object::renderingLoop(Object& object, glm::vec3& objectCenter, MouseHandler& mouseHandler) {
	GLFWwindow* window = object.getWindow();

	object.shader();

	while (!glfwWindowShouldClose(window)) {
		object.setPolygonMode(object, mouseHandler);

		projectionMatrix = glm::perspective(glm::radians(zoom), aspectRatio, nearPlane, farPlane);
		glUseProgram(shaderProgram);
		glTranslatef(objectCenter.x, objectCenter.y, objectCenter.z);
		object.rotation(mouseHandler);
		glTranslatef(-objectCenter.x, -objectCenter.y, -objectCenter.z);
		object.renderShape();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
