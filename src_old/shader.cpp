#include "includes/object.hpp"

void Object::shader() {
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

	shaderProgram = compileShaderProgram(vertexShaderSource, fragmentShaderSource);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << "OpenGL Error: " << error << std::endl;
	}
}

GLuint Object::compileShaderProgram(const char* vertexShaderSource,
									const char* fragmentShaderSource) {
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	checkShaderCompileStatus(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	checkShaderCompileStatus(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindAttribLocation(shaderProgram, 0, "inPosition");
	glBindAttribLocation(shaderProgram, 1, "inTexCoord");

	glLinkProgram(shaderProgram);
	checkProgramLinkStatus(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

void Object::checkShaderCompileStatus(GLuint shader) {
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "Shader compilation error: " << infoLog << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Object::checkProgramLinkStatus(GLuint program) {
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cerr << "Shader program linking error: " << infoLog << std::endl;
		exit(EXIT_FAILURE);
	}
}
