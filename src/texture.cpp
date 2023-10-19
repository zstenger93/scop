#include "includes/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "includes/stb_image.h"

void createTexture(Object &object) {
	glGenTextures(1, &object.texture);
	glBindTexture(GL_TEXTURE_2D, object.texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(object.textures[0], &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	stbi_image_free(data);
}

void draw(Object &object) {
	glBindVertexArray(object.VAO_triangles);
	glDrawArrays(GL_TRIANGLES, 0, object.Triangles.size());
	glBindVertexArray(object.VAO_squares);
	glDrawArrays(GL_TRIANGLES, 0, object.Squares.size());
}