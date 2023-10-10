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

	// get rid of these later
	GLuint NsLoc = glGetUniformLocation(shader.ID, "Ns");
	GLuint KaLoc = glGetUniformLocation(shader.ID, "Ka");
	GLuint KdLoc = glGetUniformLocation(shader.ID, "Kd");
	GLuint KsLoc = glGetUniformLocation(shader.ID, "Ks");
	GLuint NiLoc = glGetUniformLocation(shader.ID, "Ni");
	GLuint dLoc = glGetUniformLocation(shader.ID, "d");
	GLuint illumLoc = glGetUniformLocation(shader.ID, "illum");

	glUseProgram(shader.ID);
	glUniform1f(NsLoc, mtl.Ns);
	glUniform3f(KaLoc, mtl.ka.r, mtl.ka.g, mtl.ka.b);
	glUniform3f(KdLoc, mtl.kd.r, mtl.kd.g, mtl.kd.b);
	glUniform3f(KsLoc, mtl.ks.r, mtl.ks.g, mtl.ks.b);
	glUniform1f(NiLoc, mtl.Ni);
	glUniform1f(dLoc, mtl.d);
	glUniform1i(illumLoc, mtl.illum);

	separateTrianglesAndSquares(objects, Triangles, unpreaparedSquares);
	Squares = convertSquaresToTriangles(unpreaparedSquares);

	unsigned int VAO_triangles, VBO_triangles, VAO_squares, VBO_squares;
	createVaoVbo(VAO_triangles, VAO_squares, VBO_triangles, VBO_squares, Squares, Triangles);
	if (normal.size() > 0) {
		GLuint normalVBO;
		glGenBuffers(1, &normalVBO);
		glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
		glBufferData(GL_ARRAY_BUFFER, glmNormals.size() * sizeof(glm::vec3), glmNormals.data(),
					 GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	}

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