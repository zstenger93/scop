#include "includes/headers.hpp"
#include "includes/mouse.hpp"
#include "includes/object.hpp"
#include "includes/shader.hpp"

void Object::initGLFW(Object& object) {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	object.setWindow();
	GLFWwindow* window = object.getWindow();
	if (!window) return glfwTerminate();
	glfwMakeContextCurrent(window);
	object.setPerspectiveProjection(3200, 1800);
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(-1);
	}
}

void Object::runGLFW(Object& object) {
	GLFWwindow* window = object.getWindow();
	MouseHandler mouseHandler;

	mouseHandler.object = &object;
	object.loadTexture("textures/ok.jpg");
	glfwSetWindowUserPointer(window, &mouseHandler);
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		MouseHandler* handler = static_cast<MouseHandler*>(glfwGetWindowUserPointer(window));
		handler->mouseCallback(window, xpos, ypos);
	});
	glfwSetScrollCallback(window, MouseHandler::scrollCallback);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	object.centering();
	glm::vec3 objectCenter(centerX, centerY, centerZ);
	object.renderingLoop(object, objectCenter, mouseHandler);
	glfwTerminate();
}

void Object::centering() {
	minX = triangles[0][0].x;
	minY = triangles[0][0].y;
	minZ = triangles[0][0].z;
	maxX = triangles[0][0].x;
	maxY = triangles[0][0].y;
	maxZ = triangles[0][0].z;

	for (const auto& triangle : triangles) {
		for (const auto& vertex : triangle) {
			if (vertex.x < minX) minX = vertex.x;
			if (vertex.x > maxX) maxX = vertex.x;
			if (vertex.y < minY) minY = vertex.y;
			if (vertex.y > maxY) maxY = vertex.y;
			if (vertex.z < minZ) minZ = vertex.z;
			if (vertex.z > maxZ) maxZ = vertex.z;
		}
	}
	centerX = (minX + maxX) / 2.0f;
	centerY = (minY + maxY) / 2.0f;
	centerZ = (minZ + maxZ) / 2.0f;
	for (auto& triangle : triangles) {
		for (auto& vertex : triangle) {
			vertex.texX = (vertex.x - minX) / (maxX - minX);
			vertex.texY = (vertex.y - minY) / (maxY - minY);
		}
	}
}

void Object::renderingLoop(Object& object, glm::vec3& objectCenter, MouseHandler& mouseHandler) {
	GLFWwindow* window = object.getWindow();

	const char* vertexShaderSource = R"glsl(
	attribute vec3 inPosition;
	attribute vec2 inTexCoord;
	varying vec2 fragTexCoord;
	uniform mat4 modelViewProjection;
	void main() {
		gl_Position = modelViewProjection * vec4(inPosition, 1.0);
		fragTexCoord = inTexCoord;
	}
	)glsl";

	const char* fragmentShaderSource = R"glsl(
	varying vec2 fragTexCoord;
	uniform sampler2D textureSampler;
	void main() {
		vec4 texColor = texture2D(textureSampler, fragTexCoord);
		gl_FragColor = texColor;
	}
	)glsl";

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(),
				 GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texX));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, texture);

	GLuint shaderProgram = compileShaderProgram(vertexShaderSource, fragmentShaderSource);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << "OpenGL Error: " << error << std::endl;
	}
	while (!glfwWindowShouldClose(window)) {
		glfwSetScrollCallback(window, MouseHandler::scrollCallback);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		projectionMatrix = glm::perspective(glm::radians(zoom), aspectRatio, nearPlane, farPlane);
		// glUseProgram(shaderProgram);
		glTranslatef(objectCenter.x, objectCenter.y, objectCenter.z);
		object.rotation(mouseHandler);
		glTranslatef(-objectCenter.x, -objectCenter.y, -objectCenter.z);
		object.renderShape();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Object::setPerspectiveProjection(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	fov = 50.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
	glLoadMatrixf(glm::value_ptr(projectionMatrix));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.0f, 0.0f, -5.0f);
}
