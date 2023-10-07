#include <OpenGL/OpenGL.h>

#include "../includes/headers.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../includes/stb_image.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "shader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "glfw.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "processObjFile.hpp"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main(int argc, char **argv) {
	initGLFW();
	GLFWwindow *window = createWindow();
	// SHADER CREATION
	Shader shader(argv[2], argv[3]);

	// VERTICES
	int numVertices;
	std::vector<std::vector<Vertex>> objects = processObjFile(argv[4], numVertices);

	std::vector<float> Triangles;
	std::vector<float> unpreaparedSquares;

	separateTrianglesAndSquares(objects, Triangles, unpreaparedSquares);
	std::vector<float> Squares = convertSquaresToTriangles(unpreaparedSquares);

	// VAO AND VBO
	unsigned int VAO_triangles, VBO_triangles, VAO_squares, VBO_squares;

	// Initialize VAOs and VBOs for triangles and squares
	// Generate VAO and VBO for triangles
	glGenVertexArrays(1, &VAO_triangles);
	glGenBuffers(1, &VBO_triangles);
	glBindVertexArray(VAO_triangles);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_triangles);
	glBufferData(GL_ARRAY_BUFFER, Triangles.size() * sizeof(float), Triangles.data(),
				 GL_STATIC_DRAW);
	// Specify vertex attribute pointers for triangles
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Generate VAO and VBO for squares
	glGenVertexArrays(1, &VAO_squares);
	glGenBuffers(1, &VBO_squares);
	glBindVertexArray(VAO_squares);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_squares);
	glBufferData(GL_ARRAY_BUFFER, Squares.size() * sizeof(float), Squares.data(), GL_STATIC_DRAW);
	// Specify vertex attribute pointers for squares
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(argv[1], &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	shader.use();
	shader.setInt("texture", 0);

	RenderMode renderMode = FILLED;
	// MAIN LOOP FOR RENDERING
	while (!glfwWindowShouldClose(window)) {
		float currentFrame = static_cast<float>(glfwGetTime());
		camera.deltaTime = currentFrame - camera.lastFrame;
		camera.lastFrame = currentFrame;

		processInput(window);
		if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) {
			camera.MovementSpeed -= camera.changeSpeed;
			if (camera.MovementSpeed < 1.0f) {
				camera.MovementSpeed = 1.0f;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
			camera.MovementSpeed += camera.changeSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			camera.ProcessKeyboard(UP, camera.deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			camera.ProcessKeyboard(DOWN, camera.deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			renderMode = WIREFRAME;
		} else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
			renderMode = POINTS;
		} else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
			renderMode = FILLED;
		}
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPolygonMode(GL_FRONT_AND_BACK, (renderMode == WIREFRAME) ? GL_LINE
										 : (renderMode == POINTS)  ? GL_POINT
																   : GL_FILL);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		shader.use();
		glm::mat4 projection = glm::perspective(
			glm::radians(camera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGTH, 0.1f, 1000.0f);
		shader.setMat4("projection", projection);
		glm::mat4 view = camera.GetViewMatrix();
		shader.setMat4("view", view);

		glm::mat4 model = glm::mat4(1.0f);
		shader.setMat4("model", model);
		glBindVertexArray(VAO_triangles);
		glDrawArrays(GL_TRIANGLES, 0, Triangles.size());

		glBindVertexArray(VAO_squares);
		glDrawArrays(GL_TRIANGLES, 0, Squares.size());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO_triangles);
	glDeleteBuffers(1, &VBO_triangles);
	glDeleteVertexArrays(1, &VAO_squares);
	glDeleteBuffers(1, &VBO_squares);

	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, camera.deltaTime);
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