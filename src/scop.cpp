#include "includes/headers.hpp"
#include "includes/object.hpp"


int main(int argc, char **argv) {

	Object object;

	object.loadFromObjFile(argv[1]);

	const std::vector<Vertex>& vertices = object.getVertices();
    const std::vector<std::vector<int>>& faces = object.getFaces();

	object.printVertices();
	object.printFaces();

    // if (!glfwInit()) {
    //     std::cerr << "Failed to initialize GLFW\n";
    //     return -1;
    // }
    // // Create a windowed mode window and its OpenGL context
    // GLFWwindow* window = glfwCreateWindow(800, 600, "My Window", NULL, NULL);
    // if (!window) {
    //     std::cerr << "Failed to create GLFW window\n";
    //     glfwTerminate();
    //     return -1;
    // }
    // // Make the window's context current
    // glfwMakeContextCurrent(window);
    // while (!glfwWindowShouldClose(window)) {
    //     // Render graphics here

    //     // Swap front and back buffers
    //     // glfwSwapBuffers(window);

    //     // Poll for and process events
    //     glfwPollEvents();
    // }
    // glfwDestroyWindow(window);
    // glfwTerminate();
    // return 0;
}

