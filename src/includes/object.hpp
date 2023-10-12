#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "camera.hpp"
#include "headers.hpp"

class Object {
   public:
	Mtl mtl;  // material file content
	std::string windowName;
	unsigned int texture;			 // texture used for the object
	bool hasSlash = false;			 // flag for type of the object file
	RenderMode renderMode = FILLED;	 // default, hotkey available
	std::vector<glm::vec3> normals;	 // vn aka normals for light calculations
	std::vector<Uv> uv;				 // vt aka uv coordinates

	std::vector<Vertex> vertices;				 // triangle ad square coordinates
	std::vector<std::vector<int>> faces;		 // contains each from the obj file
	std::vector<std::vector<int>> uv_index;		 // indexes for uv coordinates from each face
	std::vector<std::vector<Vertex>> triangles;	 // contains all shapes for now
	std::vector<float> Triangles, unpreaparedSquares, Squares;	// converting squares to triangles

	GLuint VAO_triangles, VBO_triangles, VAO_squares, VBO_squares,
		normalVBO;	// vertex arrays and buffers maybe for elements arrays later

	glm::vec3 lightSourcePos;
	float ambientLightIntensity = 1.0f, diffuseLightIntensity = 1.0f, specularLightIntensity = 1.0f;
	glm::vec3 ambientColor, diffuseColor, specularColor;
};

void createVaoVbo(Object &object);

void colorCalculation(Object &object, Camera &camera);

#endif