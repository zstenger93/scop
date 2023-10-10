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
std::vector<std::vector<Vertex>> processObjFile(const std::string &filePath, Mtl &mtl, Faces &face,
												std::vector<glm::vec3> &glmNormals,
												std::vector<Normal> &normal, std::vector<Uv> &uv);
void normalizeTextureCoordinates(std::vector<Vertex> &vertices);
void separateTrianglesAndSquares(const std::vector<std::vector<Vertex>> &objects,
								 std::vector<float> &Triangles, std::vector<float> &Squares);
std::vector<float> convertSquaresToTriangles(const std::vector<float> &Squares);

void initMtl(Mtl &mtl);
void saveMtlAttributes(std::istringstream &stream, Mtl &mtl, std::string &prefix, std::string fileName);
void saveVertexCoordinates(std::istringstream &stream, Vertex &vertex, std::vector<Vertex> &vertices);

#endif