#include "includes/object.hpp"

void Object::createTriangles(std::vector<std::vector<Vertex>>& triangles) {
	triangleCount = 0;
	for (const auto& face : faces) {
		std::vector<Vertex> triangle;
		for (int index : face) {
			triangle.push_back(vertices[index - 1]);
			triangleCount++;
		}
		triangles.push_back(triangle);
	}
}

void Object::renderShape() {
	for (const auto& shape : triangles) {
		if (shape.size() == 3)
			glBegin(GL_TRIANGLES);
		else if (shape.size() == 4)
			glBegin(GL_QUADS);
		for (const auto& vertex : shape) glVertex3f(vertex.x, vertex.y, vertex.z);
		glEnd();
	}
}
