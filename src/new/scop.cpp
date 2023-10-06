#include <OpenGL/OpenGL.h>

#include "../includes/headers.hpp"
#define STB_IMAGE_IMPLEMENTATION

#include "../includes/stb_image.hpp"
#define STB_IMAGE_IMPLEMENTATION

#include "shader.hpp"
#define STB_IMAGE_IMPLEMENTATION

#include "camera.hpp"
#define STB_IMAGE_IMPLEMENTATION

void framebuffer_size_callback(GLFWwindow *window, int width, int heigth);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGTH / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

struct Vertex {
	float x, y, z, u, v;
};

struct Triangle {
	int v1, v2, v3;
};

void calculateAndNormalizeUV(std::vector<Vertex> &vertices) {
	// Calculate UV coordinates based on vertex positions
	for (size_t i = 0; i < vertices.size(); ++i) {
		Vertex &vertex = vertices[i];
		// Normalize vertex positions to generate UV coordinates
		vertex.u = std::fmod(vertex.x, 1.0f);
		vertex.v = std::fmod(vertex.y, 1.0f);

		if (vertex.u < 0) {
			vertex.u += 1.0f;
		}
		if (vertex.v < 0) {
			vertex.v += 1.0f;
		}

		// Normalize UV coordinates closer to 0 or 1
		if (vertex.u > 0.5f) {
			vertex.u = 1.0f;
		} else {
			vertex.u = 0.0f;
		}
		if (vertex.v > 0.5f) {
			vertex.v = 1.0f;
		} else {
			vertex.v = 0.0f;
		}
	}
}

float *loadFromObjFile(const std::string &filename, int &numVertices) {
	std::ifstream file(filename);
	std::string line;
	std::vector<Vertex> vertices;
	std::vector<Triangle> triangles;

	while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertex.u = 0.0f;
            vertex.v = 0.0f;
            vertices.push_back(vertex);
        } else if (prefix == "f") {
            std::vector<int> faceIndices;
            int index;
            while (iss >> index) {
                // OBJ indices start from 1
                faceIndices.push_back(index - 1);
            }

            // Create triangles based on the number of vertices in the face
            for (size_t i = 2; i < faceIndices.size(); ++i) {
                Triangle triangle;
                triangle.v1 = faceIndices[0];
                triangle.v2 = faceIndices[i - 1];
                triangle.v3 = faceIndices[i];
                triangles.push_back(triangle);
            }
        }
    }

	calculateAndNormalizeUV(vertices);

	// Combine triangles into a float array
	numVertices = triangles.size() * 3;			 // Each triangle has 3 vertices
	float *result = new float[numVertices * 5];	 // Each vertex has 5 values (x, y, z, u, v)

	for (int i = 0; i < numVertices; ++i) {
    Triangle triangle = triangles[i / 4];
    Vertex vertex;

    if (i % 3 == 0) {
        vertex = vertices[triangle.v1];
    } else if (i % 3 == 1) {
        vertex = vertices[triangle.v2];
    } else {
        vertex = vertices[triangle.v3];
    }

    // Normalize UV coordinates to [0, 1]
    float u = vertex.u;
    float v = vertex.v;
    

    // Vertex
    result[i * 5] = vertex.x;
    result[i * 5 + 1] = vertex.y;
    result[i * 5 + 2] = vertex.z;
    result[i * 5 + 3] = u;
    result[i * 5 + 4] = v;
}
	std::string outputFilename = "result.obj";
	std::ofstream outputFile(outputFilename);
	if (outputFile.is_open()) {
		for (int i = 0; i < numVertices; ++i) {
			outputFile << result[i * 5] << " " << result[i * 5 + 1] << " " << result[i * 5 + 2]
					   << " " << result[i * 5 + 3] << " " << result[i * 5 + 4] << std::endl;
		}
		outputFile.close();
		std::cout << "Data written to " << outputFilename << std::endl;
	} else {
		std::cerr << "Error: Unable to open file " << outputFilename << std::endl;
	}

	return result;
}

int main(int argc, char **argv) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// apple specific
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGTH, "windowtitle", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create the window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	// SHADER CREATION

	Shader shader(argv[2], argv[3]);

	// VETICES

	// int numVertices;
	// float *vertices = loadFromObjFile(argv[4], numVertices);

	float vertices[] = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,	-0.5f, -0.5f, 1.0f, 0.0f,
						0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,	0.5f,  -0.5f, 1.0f, 1.0f,
						-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

						-0.5f, -0.5f, 0.5f,	 0.0f, 0.0f, 0.5f,	-0.5f, 0.5f,  1.0f, 0.0f,
						0.5f,  0.5f,  0.5f,	 1.0f, 1.0f, 0.5f,	0.5f,  0.5f,  1.0f, 1.0f,
						-0.5f, 0.5f,  0.5f,	 0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

						-0.5f, 0.5f,  0.5f,	 1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
						-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
						-0.5f, -0.5f, 0.5f,	 0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

						0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, 0.5f,	0.5f,  -0.5f, 1.0f, 1.0f,
						0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,	-0.5f, -0.5f, 0.0f, 1.0f,
						0.5f,  -0.5f, 0.5f,	 0.0f, 0.0f, 0.5f,	0.5f,  0.5f,  1.0f, 0.0f,

						-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,	-0.5f, -0.5f, 1.0f, 1.0f,
						0.5f,  -0.5f, 0.5f,	 1.0f, 0.0f, 0.5f,	-0.5f, 0.5f,  1.0f, 0.0f,
						-0.5f, -0.5f, 0.5f,	 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

						-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,	0.5f,  -0.5f, 1.0f, 1.0f,
						0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, 0.5f,	0.5f,  0.5f,  1.0f, 0.0f,
						-0.5f, 0.5f,  0.5f,	 0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

	glm::vec3 cubePositions[] = {glm::vec3(0.0f, 0.0f, 0.0f),	 glm::vec3(2.0f, 5.0f, -15.0f),
								 glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
								 glm::vec3(2.4f, -0.4f, -3.5f),	 glm::vec3(-1.7f, 3.0f, -7.5f),
								 glm::vec3(1.3f, -2.0f, -2.5f),	 glm::vec3(1.5f, 2.0f, -2.5f),
								 glm::vec3(1.5f, 0.2f, -1.5f),	 glm::vec3(-1.3f, 1.0f, -1.5f)};

	// VBO, VAO AND EBO

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// LOAD AND CREATE TEXTURE

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(argv[1], &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	shader.use();
	shader.setInt("texture", 0);

	// MAIN LOOP FOR RENDERING

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		shader.use();

		glm::mat4 projection = glm::perspective(
			glm::radians(camera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGTH, 0.1f, 100.0f);
		shader.setMat4("projection", projection);

		glm::mat4 view = camera.GetViewMatrix();
		shader.setMat4("view", view);

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int heigth) {
	glViewport(0, 0, width, heigth);
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}