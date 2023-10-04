#include "includes/headers.hpp"
#include "includes/mouse.hpp"
#include "includes/object.hpp"

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
	object.setPerspectiveProjection(1600, 1200);
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

	object.loadTexture("textures/ok.jpg");
	glfwSetWindowUserPointer(window, &mouseHandler);
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		MouseHandler* handler = static_cast<MouseHandler*>(glfwGetWindowUserPointer(window));
		handler->mouseCallback(window, xpos, ypos);
	});
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	object.centering();
	glm::vec3 objectCenter(centerX, centerY, centerZ);
	object.renderingLoop(object, objectCenter, mouseHandler);
	glfwTerminate();
}

void Object::centering() {
	minX = triangles[0][0].x;
	minY = triangles[0][0].y;
	minZ = triangles[0][0].z;
	maxX = triangles[0][0].x;
	maxY = triangles[0][0].y;
	maxZ = triangles[0][0].z;

	for (const auto& triangle : triangles) {
		for (const auto& vertex : triangle) {
			if (vertex.x < minX) minX = vertex.x;
			if (vertex.x > maxX) maxX = vertex.x;
			if (vertex.y < minY) minY = vertex.y;
			if (vertex.y > maxY) maxY = vertex.y;
			if (vertex.z < minZ) minZ = vertex.z;
			if (vertex.z > maxZ) maxZ = vertex.z;
		}
	}
	centerX = (minX + maxX) / 2.0f;
	centerY = (minY + maxY) / 2.0f;
	centerZ = (minZ + maxZ) / 2.0f;
}

void Object::renderingLoop(Object& object, glm::vec3& objectCenter, MouseHandler& mouseHandler) {
	GLFWwindow* window = object.getWindow();

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glTranslatef(objectCenter.x, objectCenter.y, objectCenter.z);
		object.rotation(mouseHandler);
		glTranslatef(-objectCenter.x, -objectCenter.y, -objectCenter.z);
		object.renderShape();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Object::rotation(MouseHandler& mouseHandler) {
	glm::quat rotationX =
		glm::angleAxis(glm::radians(mouseHandler.rotationAngleX), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat rotationY =
		glm::angleAxis(glm::radians(mouseHandler.rotationAngleY), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::quat combinedRotation = rotationY * rotationX;
	glm::mat4 rotationMatrix = glm::mat4_cast(combinedRotation);
	glMultMatrixf(glm::value_ptr(rotationMatrix));
}

void Object::setPerspectiveProjection(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	float fov = 50.0f;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	glm::mat4 projectionMatrix =
		glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
	glLoadMatrixf(glm::value_ptr(projectionMatrix));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.0f, 0.0f, -5.0f);
}
