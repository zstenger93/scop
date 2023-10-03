#include "includes/headers.hpp"
#include "includes/object.hpp"

int main(int argc, char** argv) {
	Object object;

	object.loadFromObjFile(argv[1]);

	std::vector<std::vector<Vertex>>& triangles = object.getTriangles();
	object.createTriangles(triangles);

	object.debugPrint(object);

	object.initGLFW(object);
	object.runGLFW(object);

	return 0;
}

// const std::vector<Vertex>& vertices = object.getVertices();
// const std::vector<std::vector<int>>& faces = object.getFaces();