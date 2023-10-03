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
	// obj file attributes
	std::string name;
	std::vector<Vertex> vertices;
	std::vector<std::vector<int>> faces;


	// mtllib attributes
	float Ns, Ni, d, illum;	 // Specular Exponent, Optical Density, Dissolve, Illumination Model
	Color Ka;				 // Ambient color
	Color Kd;				 // Diffuse color
	Color Ks;				 // Specular color

   public:
	// input reading
	void loadMtllibFile(const std::string& filePath);
	void loadFromObjFile(const std::string& filePath);

	// getters
	const std::string& getName() const { return name; }
	const std::vector<Vertex>& getVertices() const { return vertices; }
	const std::vector<std::vector<int>>& getFaces() const { return faces; }

	// testing stuff with printing
	void printFaces() const;
	void printVertices() const;
	void printMaterialProperties() const;
};

#endif