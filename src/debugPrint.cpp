#include "includes/headers.hpp"
#include "includes/object.hpp"

void Object::debugPrint(Object &object) const {
	std::cout << object.getName() << std::endl << std::endl;
	object.printVertices();
	object.printFaces();
	object.printMaterialProperties();
	object.printTriangles();
}

void Object::printVertices() const {
	std::cout << "Vertices:\n";
	for (const auto& vertex : vertices) {
		std::cout << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
	}
	std::cout << std::endl;
}

void Object::printFaces() const {
	std::cout << "Faces:\n";
	for (const auto& face : faces) {
		for (const auto& index : face) {
			std::cout << index << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Object::printMaterialProperties() const {
	std::cout << "Material Properties:" << std::endl;
	std::cout << "Ns: " << Ns << std::endl;
	std::cout << "Ka: " << Ka.r << " " << Ka.g << " " << Ka.b << std::endl;
	std::cout << "Kd: " << Kd.r << " " << Kd.g << " " << Kd.b << std::endl;
	std::cout << "Ks: " << Ks.r << " " << Ks.g << " " << Ks.b << std::endl;
	std::cout << "Ni: " << Ni << std::endl;
	std::cout << "d: " << d << std::endl;
	std::cout << "illum: " << illum << std::endl << std::endl;
}

void Object::printTriangles() const {
	for (const auto& triangle : triangles) {
		for (const auto& vertex : triangle) {
			std::cout << "(" << vertex.x << ", " << vertex.y << ", " << vertex.z << ") ";
		}
		std::cout << std::endl;
	}
}