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
	int triangleCount;

	// created triangles from points
	std::vector<std::vector<Vertex>> triangles;

	// GLFW
	GLFWwindow* window;

	// mtllib attributes
	float Ns, Ni, d, illum;	 // Specular Exponent, Optical Density, Dissolve, Illumination Model
	Color Ka;				 // Ambient color
	Color Kd;				 // Diffuse color
	Color Ks;				 // Specular color

   public:
	// input reading
	void loadMtllibFile(const std::string& filePath);
	void loadFromObjFile(const std::string& filePath);

	// create triangles
	void createTriangles(std::vector<std::vector<Vertex>>& triangles);

	void setPerspectiveProjection(int width, int height);

	// getters
	const std::string& getName() const { return name; }
	const std::vector<Vertex>& getVertices() const { return vertices; }
	const std::vector<std::vector<int>>& getFaces() const { return faces; }
	std::vector<std::vector<Vertex>>& getTriangles() { return triangles; }

	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	// GLFW
	GLFWwindow* getWindow() { return window; }
	void setWindow() { window = glfwCreateWindow(1600, 1200, name.c_str(), NULL, NULL); }
	void initGLFW(Object& object);
	void runGLFW(Object& object);

	// testing stuff with printing
	void printFaces() const;
	void printVertices() const;
	void printTriangles() const;
	void printMaterialProperties() const;
	void debugPrint(Object& object) const;
};

class MouseHandler {
   public:
	float rotationAngleX = 0.0f;
	float rotationAngleY = 0.0f;
	double lastXPos = 0.0;
	double lastYPos = 0.0;

	static void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
		MouseHandler* handler = static_cast<MouseHandler*>(glfwGetWindowUserPointer(window));

		if (handler->lastXPos == 0.0 && handler->lastYPos == 0.0) {
			handler->lastXPos = xpos;
			handler->lastYPos = ypos;
		}

		double deltaX = xpos - handler->lastXPos;
		double deltaY = ypos - handler->lastYPos;
		float sensitivity = 0.01f;

		handler->rotationAngleX += deltaX * sensitivity;
		handler->rotationAngleY += deltaY * sensitivity;

		if (handler->rotationAngleX > 360.0f) {
			handler->rotationAngleX -= 360.0f;
		} else if (handler->rotationAngleX < -360.0f) {
			handler->rotationAngleX += 360.0f;
		}

		if (handler->rotationAngleY > 360.0f) {
			handler->rotationAngleY -= 360.0f;
		} else if (handler->rotationAngleY < -360.0f) {
			handler->rotationAngleY += 360.0f;
		}

		handler->lastXPos = xpos;
		handler->lastYPos = ypos;
	}
};

#endif