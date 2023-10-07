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

enum RenderMode { WIREFRAME, POINTS, FILLED };

struct Vertex {
	float x, y, z, texX, texY;
};

void loadFromObjFile(const std::string &filePath, std::vector<std::vector<int>> &faces,
					 std::vector<Vertex> &vertices) {
	std::ifstream objFile(filePath);
	if (!objFile.is_open()) {
		std::cerr << "Error opening the file: " << filePath << std::endl;
		return;
	}
	std::string line;
	while (std::getline(objFile, line)) {
		std::string prefix;
		std::istringstream stream(line);
		std::vector<int> faceIndices;
		Vertex vertex;
		char slash;
		int index;

		stream >> prefix;
		if (prefix == "v") {
			stream >> vertex.x >> vertex.y >> vertex.z;
			vertex.texX = vertex.x;
			vertex.texY = vertex.y;
			vertices.push_back(vertex);
		} else if (prefix == "f") {
			while (stream >> index) {
				faceIndices.push_back(index);
				if (stream.peek() == '/') {
					stream.ignore();
					if (stream.peek() != ' ' && stream >> index) {
						
					}
				}
			}
			if (faceIndices.size() >= 3) {
				faces.push_back(faceIndices);
			} else {
				std::cerr << "Invalid face with " << faceIndices.size()
						  << " indices encountered. Ignoring.\n";
			}
		}
	}
	objFile.close();
}


void normalizeTextureCoordinates(std::vector<Vertex> &vertices) {
    for (auto &vertex : vertices) {
        // Calculate spherical coordinates
        float theta = atan2(vertex.z, vertex.x);
        float phi = acos(vertex.y / sqrt(vertex.x * vertex.x + vertex.y * vertex.y + vertex.z * vertex.z));

        // Normalize theta and phi to the range [0, 1] for texture mapping
        vertex.texX = (theta + M_PI) / (2.0f * M_PI);
        vertex.texY = phi / M_PI;
    }
}

std::vector<std::vector<Vertex>> processObjFile(const std::string &filePath, int &triangleCount) {
	std::vector<std::vector<int>> faces;
	std::vector<Vertex> vertices;

	loadFromObjFile(filePath, faces, vertices);

	normalizeTextureCoordinates(vertices);

	std::vector<std::vector<Vertex>> triangles;
	triangleCount = 0;
	for (const auto &face : faces) {
		if (face.size() >= 3) {
			std::vector<Vertex> triangle;
			for (int index : face) {
				triangle.push_back(vertices[index - 1]);
			}
			triangles.push_back(triangle);
			triangleCount++;
		} else {
			std::cerr << "Invalid face with less than 3 indices encountered. Ignoring.\n";
		}
	}

	std::ofstream outputFile("result.obj");
	if (outputFile.is_open()) {
		for (const auto &triangle : triangles) {
			for (const auto &vertex : triangle) {
				outputFile << vertex.x << " " << vertex.y << " " << vertex.z << " " << vertex.texX
						   << " " << vertex.texY << std::endl;
			}
			outputFile << "\n";
		}
		outputFile.close();
	} else {
		std::cerr << "Error opening result.obj file for writing.\n";
	}

	return triangles;
}

void separateTrianglesAndSquares(const std::vector<std::vector<Vertex>> &objects,
								 std::vector<float> &Triangles, std::vector<float> &Squares) {
	for (const auto &shape : objects) {
		if (shape.size() == 3) {
			for (const auto &vertex : shape) {
				Triangles.push_back(vertex.x);
				Triangles.push_back(vertex.y);
				Triangles.push_back(vertex.z);
				Triangles.push_back(vertex.texX);
				Triangles.push_back(vertex.texY);
			}
		} else if (shape.size() == 4) {
			for (const auto &vertex : shape) {
				Squares.push_back(vertex.x);
				Squares.push_back(vertex.y);
				Squares.push_back(vertex.z);
				Squares.push_back(vertex.texX);
				Squares.push_back(vertex.texY);
			}
		} else {
			std::cerr << "Invalid shape detected! Shape must have 3 or 4 vertices." << std::endl;
		}
	}
}

std::vector<float> convertSquaresToTriangles(const std::vector<float>& Squares) {
    std::vector<float> triangles;

    // Iterate through Squares, converting each square into two triangles
    for (size_t i = 0; i < Squares.size(); i += 20) {
        // Extract vertices of the square
        float x1 = Squares[i];
        float y1 = Squares[i + 1];
        float z1 = Squares[i + 2];
        float texX1 = Squares[i + 3];
        float texY1 = Squares[i + 4];

        float x2 = Squares[i + 5];
        float y2 = Squares[i + 6];
        float z2 = Squares[i + 7];
        float texX2 = Squares[i + 8];
        float texY2 = Squares[i + 9];

        float x3 = Squares[i + 10];
        float y3 = Squares[i + 11];
        float z3 = Squares[i + 12];
        float texX3 = Squares[i + 13];
        float texY3 = Squares[i + 14];

        float x4 = Squares[i + 15];
        float y4 = Squares[i + 16];
        float z4 = Squares[i + 17];
        float texX4 = Squares[i + 18];
        float texY4 = Squares[i + 19];

        // Convert square to triangles
        // First triangle: (x1, y1, z1), (x2, y2, z2), (x3, y3, z3)
        triangles.insert(triangles.end(), {x1, y1, z1, texX1, texY1,
                                           x2, y2, z2, texX2, texY2,
                                           x3, y3, z3, texX3, texY3});
        
        // Second triangle: (x1, y1, z1), (x3, y3, z3), (x4, y4, z4)
        triangles.insert(triangles.end(), {x1, y1, z1, texX1, texY1,
                                           x3, y3, z3, texX3, texY3,
                                           x4, y4, z4, texX4, texY4});
    }

    return triangles;
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

	// VERTICES
	int numVertices;
	std::vector<std::vector<Vertex>> objects = processObjFile(argv[4], numVertices);

	std::vector<float> Triangles;
	std::vector<float> unpreaparedSquares;

	separateTrianglesAndSquares(objects, Triangles, unpreaparedSquares);
	std::vector<float> Squares = convertSquaresToTriangles(unpreaparedSquares);


	// VAO AND VBO
	unsigned int VAO_triangles, VBO_triangles, VAO_squares, VBO_squares;

	// Initialize VAOs and VBOs for triangles and squares
	// Generate VAO and VBO for triangles
	glGenVertexArrays(1, &VAO_triangles);
	glGenBuffers(1, &VBO_triangles);
	glBindVertexArray(VAO_triangles);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_triangles);
	glBufferData(GL_ARRAY_BUFFER, Triangles.size() * sizeof(float), Triangles.data(),
				 GL_STATIC_DRAW);
	// Specify vertex attribute pointers for triangles
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Generate VAO and VBO for squares
	glGenVertexArrays(1, &VAO_squares);
	glGenBuffers(1, &VBO_squares);
	glBindVertexArray(VAO_squares);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_squares);
	glBufferData(GL_ARRAY_BUFFER, Squares.size() * sizeof(float), Squares.data(), GL_STATIC_DRAW);
	// Specify vertex attribute pointers for squares
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

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

	RenderMode renderMode = FILLED;
	// MAIN LOOP FOR RENDERING
	while (!glfwWindowShouldClose(window)) {
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS) {
			camera.MovementSpeed -= camera.changeSpeed;
			if (camera.MovementSpeed < 1.0f) {
				camera.MovementSpeed = 1.0f;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS) {
			camera.MovementSpeed += camera.changeSpeed;
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			camera.ProcessKeyboard(UP, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			camera.ProcessKeyboard(DOWN, deltaTime);
		}
		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			renderMode = WIREFRAME;
		} else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
			renderMode = POINTS;
		} else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
			renderMode = FILLED;
		}
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPolygonMode(GL_FRONT_AND_BACK, (renderMode == WIREFRAME) ? GL_LINE
										 : (renderMode == POINTS)  ? GL_POINT
																   : GL_FILL);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		shader.use();
		glm::mat4 projection = glm::perspective(
			glm::radians(camera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGTH, 0.1f, 1000.0f);
		shader.setMat4("projection", projection);
		glm::mat4 view = camera.GetViewMatrix();
		shader.setMat4("view", view);

		glm::mat4 model = glm::mat4(1.0f);
		shader.setMat4("model", model);
		glBindVertexArray(VAO_triangles);
		glDrawArrays(GL_TRIANGLES, 0, Triangles.size());

		glBindVertexArray(VAO_squares);
		glDrawArrays(GL_TRIANGLES, 0, Squares.size());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO_triangles);
	glDeleteBuffers(1, &VBO_triangles);
	glDeleteVertexArrays(1, &VAO_squares);
	glDeleteBuffers(1, &VBO_squares);

	glfwTerminate();

	return 0;
}

// int main(int argc, char **argv) {
// 	glfwInit();
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
// 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
// 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// 	// apple specific
// 	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

// 	GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGTH, "windowtitle", NULL,
// NULL); 	if (window == NULL) { 		std::cout << "Failed to create the window" << std::endl;
// 		glfwTerminate();
// 		return -1;
// 	}
// 	glfwMakeContextCurrent(window);
// 	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
// 	glfwSetCursorPosCallback(window, mouse_callback);
// 	glfwSetScrollCallback(window, scroll_callback);

// 	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

// 	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
// 		std::cout << "Failed to initialize GLAD" << std::endl;
// 		glfwTerminate();
// 		return -1;
// 	}

// 	glEnable(GL_DEPTH_TEST);

// 	// SHADER CREATION

// 	Shader shader(argv[2], argv[3]);

// 	// VETICES

// 	int numVertices;
// 	std::vector<std::vector<Vertex>> objects = processObjFile(argv[4], numVertices);

// 	std::vector<float> Triangles;
// 	std::vector<float> Squares;
// 	separateTrianglesAndSquares(objects, Triangles, Squares);

// 	float vertices[] = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,	-0.5f, -0.5f, 1.0f, 0.0f,
// 						0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,	0.5f,  -0.5f, 1.0f, 1.0f,
// 						-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

// 						-0.5f, -0.5f, 0.5f,	 0.0f, 0.0f, 0.5f,	-0.5f, 0.5f,  1.0f, 0.0f,
// 						0.5f,  0.5f,  0.5f,	 1.0f, 1.0f, 0.5f,	0.5f,  0.5f,  1.0f, 1.0f,
// 						-0.5f, 0.5f,  0.5f,	 0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

// 						-0.5f, 0.5f,  0.5f,	 1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
// 						-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
// 						-0.5f, -0.5f, 0.5f,	 0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

// 						0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, 0.5f,	0.5f,  -0.5f, 1.0f, 1.0f,
// 						0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,	-0.5f, -0.5f, 0.0f, 1.0f,
// 						0.5f,  -0.5f, 0.5f,	 0.0f, 0.0f, 0.5f,	0.5f,  0.5f,  1.0f, 0.0f,

// 						-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,	-0.5f, -0.5f, 1.0f, 1.0f,
// 						0.5f,  -0.5f, 0.5f,	 1.0f, 0.0f, 0.5f,	-0.5f, 0.5f,  1.0f, 0.0f,
// 						-0.5f, -0.5f, 0.5f,	 0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

// 						-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,	0.5f,  -0.5f, 1.0f, 1.0f,
// 						0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, 0.5f,	0.5f,  0.5f,  1.0f, 0.0f,
// 						-0.5f, 0.5f,  0.5f,	 0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

// 	glm::vec3 cubePositions[] = {glm::vec3(0.0f, 0.0f, 0.0f),	 glm::vec3(2.0f, 5.0f, -15.0f),
// 								 glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f,
// -12.3f), 								 glm::vec3(2.4f, -0.4f, -3.5f),	 glm::vec3(-1.7f, 3.0f,
// -7.5f), glm::vec3(1.3f,
// -2.0f, -2.5f),	 glm::vec3(1.5f, 2.0f, -2.5f), 								 glm::vec3(1.5f,
// 0.2f, -1.5f), glm::vec3(-1.3f, 1.0f, -1.5f)};

// 	// VBO, VAO AND EBO

// 	unsigned int VBO, VAO;
// 	glGenVertexArrays(1, &VAO);
// 	glGenBuffers(1, &VBO);

// 	glBindVertexArray(VAO);

// 	glBindBuffer(GL_ARRAY_BUFFER, VBO);
// 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
// 	glEnableVertexAttribArray(0);

// 	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 *
// sizeof(float))); 	glEnableVertexAttribArray(1);

// 	// LOAD AND CREATE TEXTURE

// 	unsigned int texture;
// 	glGenTextures(1, &texture);
// 	glBindTexture(GL_TEXTURE_2D, texture);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// 	int width, height, nrChannels;
// 	stbi_set_flip_vertically_on_load(true);
// 	unsigned char *data = stbi_load(argv[1], &width, &height, &nrChannels, 0);
// 	if (data) {
// 		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
// data); 		glGenerateMipmap(GL_TEXTURE_2D); 	} else { 		std::cout << "Failed to load
// texture"
// << std::endl;
// 	}
// 	stbi_image_free(data);

// 	shader.use();
// 	shader.setInt("texture", 0);

// 	// MAIN LOOP FOR RENDERING

// 	while (!glfwWindowShouldClose(window)) {
// 		float currentFrame = static_cast<float>(glfwGetTime());
// 		deltaTime = currentFrame - lastFrame;
// 		lastFrame = currentFrame;

// 		processInput(window);
// 		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
// 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// 		glActiveTexture(GL_TEXTURE0);
// 		glBindTexture(GL_TEXTURE_2D, texture);

// 		shader.use();

// 		glm::mat4 projection = glm::perspective(
// 			glm::radians(camera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGTH, 0.1f,
// 100.0f); 		shader.setMat4("projection", projection);

// 		glm::mat4 view = camera.GetViewMatrix();
// 		shader.setMat4("view", view);

// 		glBindVertexArray(VAO);
// 		for (unsigned int i = 0; i < 10; i++) {
// 			glm::mat4 model = glm::mat4(1.0f);
// 			model = glm::translate(model, cubePositions[i]);
// 			float angle = 20.0f * i;
// 			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
// 			shader.setMat4("model", model);

// 			glDrawArrays(GL_TRIANGLES, 0, 36);
// 		}

// 		glfwSwapBuffers(window);
// 		glfwPollEvents();
// 	}
// 	glDeleteVertexArrays(1, &VAO);
// 	glDeleteBuffers(1, &VBO);

// 	glfwTerminate();
// 	return 0;
// }

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