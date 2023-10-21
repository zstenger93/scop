#include <OpenGL/OpenGL.h>

#include "includes/camera.hpp"
#include "includes/glfw.hpp"
#include "includes/headers.hpp"
#include "includes/imgui/imgui.h"
#include "includes/object.hpp"
#include "includes/processObjFile.hpp"
#include "includes/render.hpp"
#include "includes/shader.hpp"
#include "includes/stb_image.h"
#include "includes/texture.hpp"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main(int argc, char **argv) {
	inputValidaThor(argc, argv);

	Object object;

	initGLFW();
	processObjFile(argv[3], object);
	saveTextures(object, argv);

	GLFWwindow *window = createWindow(object);
	Shader shader(argv[1], argv[2]);

	ImGui::CreateContext();
	// ImGuiIO &io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init("#version 330");


	passMtlInfoToFragmentShader(shader, object);
	separateTrianglesAndSquares(object);
	convertSquaresToTriangles(object);
	createVaoVbo(object);
	renderingLoop(window, shader, camera, object);

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glDeleteVertexArrays(1, &object.VAO_triangles);
	glDeleteBuffers(1, &object.VBO_triangles);
	glDeleteVertexArrays(1, &object.VAO_squares);
	glDeleteBuffers(1, &object.VBO_squares);
	glfwTerminate();
	return 0;
}

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

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (camera.firstMouse) {
		camera.lastX = xpos;
		camera.lastY = ypos;
		camera.firstMouse = false;
	}
	float xoffset = xpos - camera.lastX;
	float yoffset = camera.lastY - ypos;

	camera.lastX = xpos;
	camera.lastY = ypos;
	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
