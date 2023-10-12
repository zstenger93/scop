#include "includes/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "includes/stb_image.h"

void createTexture(unsigned int &texture, char *textureSource) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(textureSource, &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	stbi_image_free(data);
}

void draw(unsigned int &VAO_triangles, unsigned int &VAO_squares, std::vector<float> &Triangles,
		  std::vector<float> &Squares) {
	glBindVertexArray(VAO_triangles);
	glDrawArrays(GL_TRIANGLES, 0, Triangles.size());
	glBindVertexArray(VAO_squares);
	glDrawArrays(GL_TRIANGLES, 0, Squares.size());
}