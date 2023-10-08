#include "includes/keyPress.hpp"

void keyPressHandler_Camera(GLFWwindow *window, RenderMode &renderMode, Camera &camera) {
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

float rotationX = 0.0f;
float rotationY = 0.0f;
float rotationZ = 0.0f;

glm::mat4 keyPressHandler_ObjectCenterRotation(GLFWwindow *window, std::vector<float> &Triangles,
											   std::vector<float> &Squares, glm::mat4 &model) {
	float rotateSpeed = 1.0f;
	model = glm::mat4(1.0f);
	std::vector<float> allTriangles;
	allTriangles.insert(allTriangles.end(), Triangles.begin(), Triangles.end());
	allTriangles.insert(allTriangles.end(), Squares.begin(), Squares.end());

	glm::vec3 objectCenter = calculateCenter(allTriangles);

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) rotationX += rotateSpeed;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) rotationX -= rotateSpeed;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) rotationY += rotateSpeed;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) rotationY -= rotateSpeed;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) rotationZ += rotateSpeed;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) rotationZ -= rotateSpeed;

	model = glm::translate(model, objectCenter);
	model = glm::rotate(model, glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotationZ), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, -objectCenter);
	return model;
}

glm::vec3 calculateCenter(const std::vector<float> &triangles) {
	glm::vec3 sum(0.0f);
	size_t totalVertices = triangles.size() / 5;

	for (size_t i = 0; i < triangles.size(); i += 5) {
		sum.x += triangles[i];
		sum.y += triangles[i + 1];
		sum.z += triangles[i + 2];
	}
	return sum / static_cast<float>(totalVertices);
}
