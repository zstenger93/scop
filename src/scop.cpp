#include "includes/headers.hpp"
#include "includes/object.hpp"

int main(int argc, char** argv) {
	Object object;

	object.loadFromObjFile(argv[1]);

	std::cout << object.getName() << std::endl << std::endl;
	object.printVertices();
	object.printFaces();
	object.printMaterialProperties();

	const std::vector<Vertex>& vertices = object.getVertices();
	const std::vector<std::vector<int>>& faces = object.getFaces();

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(1600, 1200, object.getName().c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Set up OpenGL context
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window)) {
		// Clear the buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw the triangles
		glBegin(GL_TRIANGLES);
		for (const auto& face : faces) {
			for (int i = 0; i < 3; ++i) {
				const auto& vertex = vertices[face[i]];
				glVertex3f(vertex.x, vertex.y, vertex.z);
			}
		}
		glEnd();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
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
	std::cout << "illum: " << illum << std::endl;
}