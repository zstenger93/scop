#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "headers.hpp"

struct Vertex {
	float x, y, z;
};

struct Color {
	float r, g, b;
};

class Object {
   private:
	std::string name;
	std::vector<Vertex> vertices;
	std::vector<std::vector<int>> faces;

	float Ns, Ni, d, illum;
	Color Ka;  // Ambient color
	Color Kd;  // Diffuse color
	Color Ks;  // Specular color

   public:
	void loadFromObjFile(const std::string& filePath);

	const std::vector<Vertex>& getVertices() const { return vertices; }
	const std::vector<std::vector<int>>& getFaces() const { return faces; }
	const std::string& getName() const { return name; }

	void printVertices() const {
		std::cout << "Vertices:\n";
		for (const auto& vertex : vertices) {
			std::cout << "(" << vertex.x << ", " << vertex.y << ", " << vertex.z << ")\n";
		}
	}

	void printFaces() const {
		std::cout << "Faces:\n";
		for (const auto& face : faces) {
			for (const auto& index : face) {
				std::cout << index << " ";
			}
			std::cout << std::endl;
		}
	}

	void printMaterialProperties() const {
		std::cout << "Material Properties:" << std::endl;
		std::cout << "Ns: " << Ns << std::endl;
		std::cout << "Ni: " << Ni << std::endl;
		std::cout << "d: " << d << std::endl;
		std::cout << "illum: " << illum << std::endl;
		std::cout << "Ka: (" << Ka.r << ", " << Ka.g << ", " << Ka.b << ")" << std::endl;
		std::cout << "Kd: (" << Kd.r << ", " << Kd.g << ", " << Kd.b << ")" << std::endl;
		std::cout << "Ks: (" << Ks.r << ", " << Ks.g << ", " << Ks.b << ")" << std::endl;
	}
};

#endif