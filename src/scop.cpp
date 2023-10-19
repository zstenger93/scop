#include <OpenGL/OpenGL.h>

#include "includes/camera.hpp"
#include "includes/glfw.hpp"
#include "includes/headers.hpp"
#include "includes/object.hpp"
#include "includes/processObjFile.hpp"
#include "includes/render.hpp"
#include "includes/shader.hpp"
#include "includes/stb_image.h"
#include "includes/texture.hpp"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main(int argc, char **argv) {
	Object object;
	
	initGLFW();
	processObjFile(argv[3], object);
	saveTextures(object, argv);

	GLFWwindow *window = createWindow(object);
	Shader shader(argv[1], argv[2]);

	passMtlInfoToFragmentShader(shader, object);
	separateTrianglesAndSquares(object);
	convertSquaresToTriangles(object);
	createVaoVbo(object);
	createTexture(object);
	renderingLoop(window, shader, camera, object);
	glDeleteVertexArrays(1, &object.VAO_triangles);
	glDeleteBuffers(1, &object.VBO_triangles);
	glDeleteVertexArrays(1, &object.VAO_squares);
	glDeleteBuffers(1, &object.VBO_squares);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int heigth) {
	glViewport(0, 0, width, heigth);
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (camera.firstMouse) {
		camera.lastX = xpos;
		camera.lastY = ypos;
		camera.firstMouse = false;
	}
	float xoffset = xpos - camera.lastX;
	float yoffset = camera.lastY - ypos;

	camera.lastX = xpos;
	camera.lastY = ypos;
	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
