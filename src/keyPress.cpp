#include "includes/keyPress.hpp"

void keyPressHandler_Camera_wasdSpaceX(GLFWwindow *window, Camera &camera) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, camera.deltaTime);
}

void keyPressHandler_Camera_Speed(GLFWwindow *window, Camera &camera) {
	if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
		camera.MovementSpeed -= camera.changeSpeed;
		if (camera.MovementSpeed < 1.0f) camera.MovementSpeed = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) camera.MovementSpeed += camera.changeSpeed;
}

void keyPressHandler_PolygonModes(GLFWwindow *window, RenderMode &renderMode, Camera &camera) {
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		renderMode = WIREFRAME;
	} else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		renderMode = POINTS;
	} else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		renderMode = FILLED;
}

void keyPressHandler_Color_OR_Texture(GLFWwindow *window, Camera &camera, int &version) {
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) version = 0;
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) version = 1;
}

float rotationX = 0.0f;
float rotationY = 0.0f;
float rotationZ = 0.0f;
float rotateSpeed = 1.0f;

glm::mat4 keyPressHandler_ObjectCenterRotation(GLFWwindow *window, std::vector<float> &Triangles,
											   std::vector<float> &Squares, glm::mat4 &model) {
	model = glm::mat4(1.0f);
	std::vector<float> allTriangles;
	allTriangles.insert(allTriangles.end(), Triangles.begin(), Triangles.end());
	allTriangles.insert(allTriangles.end(), Squares.begin(), Squares.end());

	glm::vec3 objectCenter = calculateCenter(allTriangles);

	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) rotationX += rotateSpeed;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) rotationX -= rotateSpeed;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) rotationY += rotateSpeed;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) rotationY -= rotateSpeed;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) rotationZ += rotateSpeed;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) rotationZ -= rotateSpeed;
	if (rotateSpeed > 1.0f)
		if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) rotateSpeed -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) rotateSpeed += 1.0f;

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
