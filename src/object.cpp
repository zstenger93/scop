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