#include "includes/object.hpp"

void Object::createTriangles(std::vector<std::vector<Vertex>>& triangles) {
	triangleCount = 0;
	for (const auto& face : faces) {
		std::vector<Vertex> triangle;
		for (int index : face) {
			triangle.push_back(vertices[index - 1]);
		}
		triangleCount++;
		triangles.push_back(triangle);
	}
}

void Object::renderShape() {
	glBindTexture(GL_TEXTURE_2D, texture);

	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_TRUE);
	glEnable(GL_BLEND);
	for (const auto& shape : triangles) {
		if (shape.size() == 3)
			glBegin(GL_TRIANGLES);
		else if (shape.size() == 4)
			glBegin(GL_QUADS);
		for (const auto& vertex : shape) {
			glTexCoord2f(vertex.z, vertex.y);
			glVertex3f(vertex.x / zoom, vertex.y / zoom, vertex.z / zoom);
		}
		glEnd();
	}
}

void Object::centering() {
	minX = triangles[0][0].x;
	minY = triangles[0][0].y;
	minZ = triangles[0][0].z;
	maxX = triangles[0][0].x;
	maxY = triangles[0][0].y;
	maxZ = triangles[0][0].z;

	for (const auto& triangle : triangles) {
		for (const auto& vertex : triangle) {
			if (vertex.x < minX) minX = vertex.x;
			if (vertex.x > maxX) maxX = vertex.x;
			if (vertex.y < minY) minY = vertex.y;
			if (vertex.y > maxY) maxY = vertex.y;
			if (vertex.z < minZ) minZ = vertex.z;
			if (vertex.z > maxZ) maxZ = vertex.z;
		}
	}
	centerX = (minX + maxX) / 2.0f;
	centerY = (minY + maxY) / 2.0f;
	centerZ = (minZ + maxZ) / 2.0f;
	for (auto& triangle : triangles) {
		for (auto& vertex : triangle) {
			vertex.texX = (vertex.x - minX) / (maxX - minX);
			vertex.texY = (vertex.y - minY) / (maxY - minY);
		}
	}
}

void Object::setPerspectiveProjection(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	fov = 50.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
	glLoadMatrixf(glm::value_ptr(projectionMatrix));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.0f, 0.0f, -5.0f);
}

void Object::setPolygonMode(Object& object, MouseHandler& mouseHandler) {
	GLFWwindow* window = object.getWindow();

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		wireframeMode = true;
	} else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		wireframeMode = false;
		pointMode = true;
	} else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		wireframeMode = false;
		pointMode = false;
	}

	glfwSetScrollCallback(window, MouseHandler::scrollCallback);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	} else {
		if (wireframeMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		} else if (pointMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		}
	}
}