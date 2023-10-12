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
#include "object.hpp"

std::vector<std::vector<Vertex>> processObjFile(const std::string &filePath, Object &object);
void loadFromObjFile(const std::string &filePath, Object &object);
void normalizeTextureCoordinates(Object &object);
void separateTrianglesAndSquares(const std::vector<std::vector<Vertex>> &objects,
								 std::vector<float> &Triangles, std::vector<float> &Squares);
std::vector<float> convertSquaresToTriangles(const std::vector<float> &Squares);
void initMtl(Object &object);
void saveMtlAttributes(Object &object, std::istringstream &stream, std::string &prefix,
					   std::string fileName);
void saveVertexCoordinates(std::istringstream &stream, Object &object);
void saveFaceIndexes(std::istringstream &stream, Object &object);
void triangleAssembly(std::vector<std::vector<Vertex>> &triangles, Object &object);

#endif