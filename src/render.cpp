#include "includes/render.hpp"
#include "includes/camera.hpp"
#include "includes/keyPress.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "includes/texture.hpp"
#define STB_IMAGE_IMPLEMENTATION

void renderingLoop(GLFWwindow *window, Shader &shader, Camera &camera, RenderMode &renderMode,
				   unsigned int &texture, unsigned int &VAO_triangles, unsigned int &VAO_squares,
				   std::vector<float> &Triangles, std::vector<float> &Squares) {
	while (!glfwWindowShouldClose(window)) {
		camera.fps(camera);
		processInput(window, camera);
		keyPressHandler(window, renderMode, camera);
		shader.settings(renderMode, texture);
		shader.use();
		shader.setPerspective(camera, shader);
		shader.setView(camera, shader);
		shader.setModel(camera, shader);
		draw(VAO_triangles, VAO_squares, Triangles, Squares);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void processInput(GLFWwindow *window, Camera &camera) {
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