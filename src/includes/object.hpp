#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "headers.hpp"
#include "mouse.hpp"
#include "shader.hpp"

struct Vertex {
	float x, y, z, texX, texY;
};

struct Color {
	float r, g, b;
};

class Object {
   private:
	// OBJ FILE ATTRIBUTES
	std::string name;
	std::vector<Vertex> vertices;
	std::vector<std::vector<int>> faces;

	// CAMERA
	float aspectRatio;
	float fov;
	float nearPlane;
	float farPlane;
	glm::mat4 projectionMatrix;

	int triangleCount;
	// CREATED TRIANGLES BY COMBINING FACES AND VERTICES
	std::vector<std::vector<Vertex>> triangles;
	// GLFW
	GLFWwindow* window;
	// MTLLIB ATTRIBUTES
	float Ns, Ni, d, illum;	 // Specular Exponent, Optical Density, Dissolve, Illumination Model
	Color Ka;				 // Ambient color
	Color Kd;				 // Diffuse color
	Color Ks;				 // Specular color

	GLint texSize;
	GLuint texture;

	// OBJECT MIN-MAX COORDINATES
	float minX;
	float minY;
	float minZ;
	float maxX;
	float maxY;
	float maxZ;
	// OBJECT CENTER
	float centerX;
	float centerY;
	float centerZ;

	bool wireframeMode = false;
	bool pointMode = false;

   public:
	glm::mat4 translationMatrix;
	float zoom = 1.0f;
	float zoomSpeed = 2.0f;
	// INPUT READING
	void loadMtllibFile(const std::string& filePath);
	void loadFromObjFile(const std::string& filePath);
	// TEXTURE
	void loadTexture(std::string imagePath);
	// CREATE TRIANGLES
	void createTriangles(std::vector<std::vector<Vertex>>& triangles);
	void centering();
	// RENDERING
	void renderingLoop(Object& object, glm::vec3& objectCenter, MouseHandler& mouseHandler);
	void setPolygonMode(Object& object, MouseHandler& mouseHandler);
	void rotation(MouseHandler& mouseHandler);
	void renderShape();
	// GETERS
	const std::string& getName() const { return name; }
	const std::vector<Vertex>& getVertices() const { return vertices; }
	const std::vector<std::vector<int>>& getFaces() const { return faces; }
	std::vector<std::vector<Vertex>>& getTriangles() { return triangles; }
	// GLFW
	GLFWwindow* getWindow() { return window; }
	void setWindow() { window = glfwCreateWindow(3200, 1800, name.c_str(), NULL, NULL); }
	void initGLFW(Object& object);
	void runGLFW(Object& object);
	void setPerspectiveProjection(int width, int height);
	// TESTING STUFF WITH PRINTING
	void printFaces() const;
	void printVertices() const;
	void printTriangles() const;
	void printMaterialProperties() const;
	void debugPrint(Object& object) const;

	GLuint compileShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
	void checkShaderCompileStatus(GLuint shader);
	void checkProgramLinkStatus(GLuint program);
};

#endif