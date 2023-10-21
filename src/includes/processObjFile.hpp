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

void initMtl(Object &object);
void triangleAssembly(Object &object);
void assemblySlashMode(Object &object);
void assemblyNormalMode(Object &object);
void inputValidaThor(int argc, char **argv);
void convertSquaresToTriangles(Object &object);
void normalizeTextureCoordinates(Object &object);
void separateTrianglesAndSquares(Object &object);
void saveFaceIndexes(std::istringstream &stream, Object &object);
void processObjFile(const std::string &filePath, Object &object);
void loadFromObjFile(const std::string &filePath, Object &object);
void saveVertexCoordinates(std::istringstream &stream, Object &object);
void saveMtlAttributes(Object &object, std::istringstream &stream, std::string &prefix,
					   std::string fileName);

#endif