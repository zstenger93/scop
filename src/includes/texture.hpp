#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "headers.hpp"

void createTexture(unsigned int &texture, char *textureSource);
void draw(unsigned int &VAO_triangles, unsigned int &VAO_squares, std::vector<float> &Triangles,
		  std::vector<float> &Squares);

#endif