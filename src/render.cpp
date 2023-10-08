#include "includes/render.hpp"

#include "includes/camera.hpp"
#include "includes/keyPress.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "includes/texture.hpp"
#define STB_IMAGE_IMPLEMENTATION


float rotateSpeed = 1.0f;
float rotationX = 0.0f;
float rotationY = 0.0f;
float rotationZ = 0.0f;

glm::vec3 calculateCenter(const std::vector<float>& triangles) {
    glm::vec3 sum(0.0f);
    size_t totalVertices = triangles.size() / 5; // Each vertex has 5 attributes (x, y, z, u, v)

    for (size_t i = 0; i < triangles.size(); i += 5) {
        sum.x += triangles[i];     // x-coordinate
        sum.y += triangles[i + 1]; // y-coordinate
        sum.z += triangles[i + 2]; // z-coordinate
    }

    return sum / static_cast<float>(totalVertices);
}

void renderingLoop(GLFWwindow *window, Shader &shader, Camera &camera, RenderMode &renderMode,
				   unsigned int &texture, unsigned int &VAO_triangles, unsigned int &VAO_squares,
				   std::vector<float> &Triangles, std::vector<float> &Squares, std::vector<float> &objects) {
	while (!glfwWindowShouldClose(window)) {
		camera.fps(camera);
		processInput(window, camera);
		keyPressHandler(window, renderMode, camera);

		glm::vec3 objectCenter = calculateCenter(objects);


		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
			rotationX += rotateSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
			rotationX -= rotateSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
			rotationY += rotateSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
			rotationY -= rotateSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
			rotationZ += rotateSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
			rotationZ -= rotateSpeed;
		}

		glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, objectCenter); // Translate to the center of the object
        model = glm::rotate(model, glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(rotationZ), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, -objectCenter); // Translate back to the original position

		shader.settings(renderMode, texture);
		shader.use();



		shader.setMat4("model", model);
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