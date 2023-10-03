#include "includes/headers.hpp"
#include "includes/object.hpp"

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
}

void Object::runGLFW(Object& object) {
	GLFWwindow* window = object.getWindow();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
		for (const auto& face : faces) {
			for (int i = 0; i < 3; ++i) {
				const auto& vertex = vertices[face[i]];
				glVertex3f(vertex.x, vertex.y, vertex.z);
			}
		}
		glEnd();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}