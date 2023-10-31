#include "../includes/shader.hpp"

#include <OpenGL/OpenGL.h>

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	} catch (std::ifstream::failure &e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
	}
	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();
	unsigned int vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
void Shader::use() { glUseProgram(ID); }

void Shader::setBool(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) const {
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const {
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setPerspective(Camera &camera, Shader &shader) {
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix =
		glm::perspective(glm::radians(camera.Zoom),
						 static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT),
						 camera.nearPlane, camera.farPlane);
	glm::mat4 viewMatrix = camera.getViewMatrix();
	glm::mat4 modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;
	shader.setMat4("modelViewProjectionMatrix", modelViewProjectionMatrix);
	shader.setMat4("projection", projectionMatrix);
}

void Shader::setView(Camera &camera, Shader &shader) {
	glm::mat4 view = camera.getViewMatrix();
	shader.setMat4("view", view);
}

void Shader::setModel(Camera &camera, Shader &shader, glm::mat4 &model) {
	shader.setMat4("model", model);
}

void Shader::settings(Object &object) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, (object.renderMode == WIREFRAME) ? GL_LINE
									 : (object.renderMode == POINTS)  ? GL_POINT
																	  : GL_FILL);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, object.texture);
}

void Shader::setTexture_OR_setColor(Shader &shader, int &version, glm::vec3 &color, int &light) {
	shader.setInt("useTexture", version);
	shader.setInt("useLight", light);
	shader.setInt("texture", 0);
	shader.setVec3("objectColor", color);
}

void passMtlInfoToFragmentShader(Shader &shader, Object &object) {
	GLuint NsLoc = glGetUniformLocation(shader.ID, "Ns");
	GLuint KaLoc = glGetUniformLocation(shader.ID, "Ka");
	GLuint KdLoc = glGetUniformLocation(shader.ID, "Kd");
	GLuint KsLoc = glGetUniformLocation(shader.ID, "Ks");
	GLuint NiLoc = glGetUniformLocation(shader.ID, "Ni");
	GLuint dLoc = glGetUniformLocation(shader.ID, "d");
	GLuint illumLoc = glGetUniformLocation(shader.ID, "illum");
	GLuint lightPosLoc = glGetUniformLocation(shader.ID, "LightPos");

	glUseProgram(shader.ID);
	glUniform1f(NsLoc, object.mtl.Ns);
	glUniform3f(KaLoc, object.mtl.ka.r, object.mtl.ka.g, object.mtl.ka.b);
	glUniform3f(KdLoc, object.mtl.kd.r, object.mtl.kd.g, object.mtl.kd.b);
	glUniform3f(KsLoc, object.mtl.ks.r, object.mtl.ks.g, object.mtl.ks.b);
	glUniform1f(NiLoc, object.mtl.Ni);
	glUniform1f(dLoc, object.mtl.d);
	glUniform1i(illumLoc, object.mtl.illum);
	glUniform3f(lightPosLoc, object.lightSourcePos.x, object.lightSourcePos.y,
				object.lightSourcePos.z);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
					  << infoLog << "\n -- --------------------------------------------------- -- "
					  << std::endl;
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
					  << infoLog << "\n -- --------------------------------------------------- -- "
					  << std::endl;
		}
	}
}
