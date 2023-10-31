#include "includes/headers.hpp"
#include "includes/object.hpp"
#include "includes/processObjFile.hpp"

void inputValidaThor(int argc, char **argv) {
	if (argc < 4) {
		std::cout << "Not enough arguments." << std::endl;
		std::cout << "The program needs at least the following:" << std::endl;
		std::cout << "A vertex and fragment source, an object file and a texture." << std::endl;
		exit(1);
	}
	std::string fileName = argv[3];
	if (fileName.length() >= 4 && fileName.substr(fileName.length() - 4) != ".obj") {
		std::cout << "Invalid object file, it doesn't have .obj extension." << std::endl;
		exit(1);
	}
	std::ifstream file(fileName.substr(3));
	if (file.is_open()) {
		if (file.peek() == std::ifstream::traits_type::eof()) {
			std::cout << "The object file is empty." << std::endl;
			file.close();
			exit(1);
		}
		file.close();
	} else {
		std::cout << "Unable to open the object file." << std::endl;
		exit(1);
	}
}

void cleanUp(Object &object) {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glDeleteVertexArrays(1, &object.VAO_triangles);
	glDeleteBuffers(1, &object.VBO_triangles);
	glDeleteVertexArrays(1, &object.VAO_squares);
	glDeleteBuffers(1, &object.VBO_squares);
	glfwTerminate();
}