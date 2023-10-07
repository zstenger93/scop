#ifndef PROCESSOBJFILE_HPP
#define PROCESSOBJFILE_HPP

#include "../includes/headers.hpp"

void loadFromObjFile(const std::string &filePath, std::vector<std::vector<int>> &faces,
					 std::vector<Vertex> &vertices);
std::vector<std::vector<Vertex>> processObjFile(const std::string &filePath);
void normalizeTextureCoordinates(std::vector<Vertex> &vertices);
void separateTrianglesAndSquares(const std::vector<std::vector<Vertex>> &objects,
								 std::vector<float> &Triangles, std::vector<float> &Squares);
std::vector<float> convertSquaresToTriangles(const std::vector<float> &Squares);

#endif