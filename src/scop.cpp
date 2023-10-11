#include <OpenGL/OpenGL.h>

#include "includes/glfw.hpp"
#include "includes/headers.hpp"
#include "includes/object.hpp"
#include "includes/processObjFile.hpp"
#include "includes/render.hpp"
#include "includes/shader.hpp"
#include "includes/stb_image.hpp"
#include "includes/texture.hpp"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main(int argc, char **argv) {
	Mtl mtl;
	Faces face;
	Object w;
	std::vector<Uv> uv;
	std::vector<Normal> normal;
	RenderMode renderMode = FILLED;
	std::vector<glm::vec3> glmNormals;
	std::vector<float> Triangles, unpreaparedSquares, Squares;

	initGLFW();
	std::vector<std::vector<Vertex>> objects =
		processObjFile(argv[4], mtl, face, glmNormals, w, normal, uv);
	GLFWwindow *window = createWindow(w);
	Shader shader(argv[2], argv[3]);

	passMtlInfoToFragmentShader(shader, mtl);

	separateTrianglesAndSquares(objects, Triangles, unpreaparedSquares);
	Squares = convertSquaresToTriangles(unpreaparedSquares);

	GLuint VAO_triangles, VBO_triangles, VAO_squares, VBO_squares, normalVBO;
	createVaoVbo(VAO_triangles, VAO_squares, VBO_triangles, VBO_squares, normalVBO, Squares,
				 Triangles, glmNormals);

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