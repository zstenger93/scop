#ifndef SHADER_H
#define SHADER_H

/*
	This class takes the vertexSourceCode and fragmentSourceCode
	creates the vertex and fragment shader, and combining the 2,
	creates the shader program.
	Outside of that:
		setting for the window:
			Perspective
			View
			Model
			Settings
*/

#include "camera.hpp"
#include "headers.hpp"

class Shader {
   public:
	unsigned int ID;

	Shader(const char *vertexPath, const char *fragmentPath);
	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec2(const std::string &name, const glm::vec2 &value) const;
	void setVec2(const std::string &name, float x, float y) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setVec3(const std::string &name, float x, float y, float z) const;
	void setVec4(const std::string &name, const glm::vec4 &value) const;
	void setVec4(const std::string &name, float x, float y, float z, float w) const;
	void setMat2(const std::string &name, const glm::mat2 &mat) const;
	void setMat3(const std::string &name, const glm::mat3 &mat) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
	void setPerspective(Camera &camera, Shader &shader);
	void setView(Camera &camera, Shader &shader);
	void setModel(Camera &camera, Shader &shader, glm::mat4 &model);
	void settings(RenderMode &renderMode, unsigned int &texture);
	void setTexture_OR_setColor(Shader &shader, int &version, glm::vec3 &color);

   private:
	void checkCompileErrors(unsigned int shader, std::string type);
};

void passMtlInfoToFragmentShader(Shader &shader, Mtl &mtl);

#endif