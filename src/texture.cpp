#define STB_IMAGE_IMPLEMENTATION

#include "includes/object.hpp"

void Object::loadTexture(std::string imagePath) {
	int w, h, channels;
	std::string path = "../" + imagePath;
	unsigned char* data = stbi_load(path.c_str(), &w, &h, &channels, 0);

	if (data) {
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &texSize);
		if (w > texSize || h > texSize) {
			std::cerr << "Texture to big" << std::endl;
			exit(127);
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		stbi_image_free(data);
	} else {
		std::cerr << "Error Loading the image" << std::endl;
		exit(127);
	}
}