#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "headers.hpp"
#include "object.hpp"

void createTexture(Object &object, std::vector<char *> textureSource);
void draw(Object &object);

#endif