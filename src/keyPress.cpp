#include "includes/keyPress.hpp"

void keyPressHandler(GLFWwindow *window, RenderMode &renderMode, Camera &camera) {
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) {
		camera.MovementSpeed -= camera.changeSpeed;
		if (camera.MovementSpeed < 1.0f) camera.MovementSpeed = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) camera.MovementSpeed += camera.changeSpeed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) camera.ProcessKeyboard(UP, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		renderMode = WIREFRAME;
	} else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		renderMode = POINTS;
	} else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		renderMode = FILLED;
}