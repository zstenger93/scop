#include <OpenGL/OpenGL.h>

#include "includes/headers.hpp"
#include "includes/stb_image.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "includes/shader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "includes/glfw.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "includes/processObjFile.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "includes/texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "includes/object.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "includes/render.hpp"
#define STB_IMAGE_IMPLEMENTATION

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main(int argc, char **argv) {
	RenderMode renderMode = FILLED;
	std::vector<float> Triangles, unpreaparedSquares, Squares;

	initGLFW();
	GLFWwindow *window = createWindow();
	Shader shader(argv[2], argv[3]);
	std::vector<std::vector<Vertex>> objects = processObjFile(argv[4]);

	separateTrianglesAndSquares(objects, Triangles, unpreaparedSquares);
	Squares = convertSquaresToTriangles(unpreaparedSquares);

	unsigned int VAO_triangles, VBO_triangles, VAO_squares, VBO_squares;
	createVaoVbo(VAO_triangles, VAO_squares, VBO_triangles, VBO_squares, Squares, Triangles);

	unsigned int texture;
	createTexture(texture, argv[1]);

	renderingLoop(window, shader, camera, renderMode, texture, VAO_triangles, VAO_squares,
				  Triangles, Squares);

	glDeleteVertexArrays(1, &VAO_triangles);
	glDeleteBuffers(1, &VBO_triangles);
	glDeleteVertexArrays(1, &VAO_squares);
	glDeleteBuffers(1, &VBO_squares);
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