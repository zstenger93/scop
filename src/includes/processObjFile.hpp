#ifndef PROCESSOBJFILE_HPP
#define PROCESSOBJFILE_HPP

/*
	Here we deal with loading our object files,
	organizing and svaing the attributes into our
	variables, normalizing UV coordinates and
	converting square vertices into triangle vertices
	because we don't like deprecated functions like GL_QUADS
*/

#include "headers.hpp"

void loadFromObjFile(const std::string &filePath, std::vector<std::vector<int>> &faces,
					 std::vector<Vertex> &vertices, Mtl &mtl, Faces &face, std::vector<Uv> &uv,
					 std::vector<Normal> &normal);
std::vector<std::vector<Vertex>> processObjFile(const std::string &filePath, Mtl &mtl, Faces &face);
void normalizeTextureCoordinates(std::vector<Vertex> &vertices);
void separateTrianglesAndSquares(const std::vector<std::vector<Vertex>> &objects,
								 std::vector<float> &Triangles, std::vector<float> &Squares);
std::vector<float> convertSquaresToTriangles(const std::vector<float> &Squares);

// void loadFromObjFile(const std::string &filePath, std::vector<std::vector<Faces>> &faces,
//                      std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &textureCoords,
//                      std::vector<glm::vec3> &normals, Mtl &mtl);
#endif