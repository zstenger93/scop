#include "includes/processObjFile.hpp"

std::vector<std::vector<Vertex>> processObjFile(const std::string &filePath) {
	std::vector<std::vector<int>> faces;
	std::vector<Vertex> vertices;
	std::vector<std::vector<Vertex>> triangles;

	loadFromObjFile(filePath, faces, vertices);
	normalizeTextureCoordinates(vertices);

	for (const auto &face : faces) {
		if (face.size() >= 3) {
			std::vector<Vertex> triangle;
			for (int index : face) triangle.push_back(vertices[index - 1]);
			triangles.push_back(triangle);
		} else
			std::cerr << "Invalid face with less than 3 indices encountered. Ignoring.\n";
	}
	return triangles;
}

void loadFromObjFile(const std::string &filePath, std::vector<std::vector<int>> &faces,
					 std::vector<Vertex> &vertices) {
	std::ifstream objFile(filePath);
	if (!objFile.is_open()) {
		std::cerr << "Error opening the file: " << filePath << std::endl;
		return;
	}
	std::string line;
	while (std::getline(objFile, line)) {
		std::string prefix;
		std::istringstream stream(line);
		std::vector<int> faceIndices;
		Vertex vertex;
		char slash;
		int index;

		stream >> prefix;
		if (prefix == "v") {
			stream >> vertex.x >> vertex.y >> vertex.z;
			vertex.texX = vertex.x;
			vertex.texY = vertex.y;
			vertices.push_back(vertex);
		} else if (prefix == "vn") {
		} else if (prefix == "vt") {
		} else if (prefix == "f") {
			while (stream >> index) {
				faceIndices.push_back(index);
				if (stream.peek() == '/') {
					stream.ignore();
					// Ignore textureCoordinateIndex and normalIndex for now
					stream.ignore(256, '/');
					stream.ignore(256, ' ');
				} else {
					stream.ignore(256, ' ');
				}
			}
			if (faceIndices.size() >= 3) {
				faces.push_back(faceIndices);
			} else
				std::cerr << "Invalid face with " << faceIndices.size() << " Ignoring.\n";
		}
	}
	objFile.close();
}

void normalizeTextureCoordinates(std::vector<Vertex> &vertices) {
	for (auto &vertex : vertices) {
		float theta = atan2(vertex.z, vertex.x);
		float phi =
			acos(vertex.y / sqrt(vertex.x * vertex.x + vertex.y * vertex.y + vertex.z * vertex.z));
		vertex.texX = (theta + M_PI) / (2.0f * M_PI);
		vertex.texY = phi / M_PI;
	}
}

void separateTrianglesAndSquares(const std::vector<std::vector<Vertex>> &objects,
								 std::vector<float> &Triangles, std::vector<float> &Squares) {
	for (const auto &shape : objects) {
		if (shape.size() == 3) {
			for (const auto &vertex : shape) {
				Triangles.push_back(vertex.x);
				Triangles.push_back(vertex.y);
				Triangles.push_back(vertex.z);
				Triangles.push_back(vertex.texX);
				Triangles.push_back(vertex.texY);
			}
		} else if (shape.size() == 4) {
			for (const auto &vertex : shape) {
				Squares.push_back(vertex.x);
				Squares.push_back(vertex.y);
				Squares.push_back(vertex.z);
				Squares.push_back(vertex.texX);
				Squares.push_back(vertex.texY);
			}
		} else
			std::cerr << "Invalid shape detected! Shape must have 3 or 4 vertices. " << shape.size()
					  << std::endl;
	}
}

// our daily sponsor is deprecated functions, no i haven't spent on this one day at all, noo..
std::vector<float> convertSquaresToTriangles(const std::vector<float> &Squares) {
	std::vector<float> triangles;

	for (size_t i = 0; i < Squares.size(); i += 20) {
		float x1 = Squares[i];
		float y1 = Squares[i + 1];
		float z1 = Squares[i + 2];
		float texX1 = Squares[i + 3];
		float texY1 = Squares[i + 4];

		float x2 = Squares[i + 5];
		float y2 = Squares[i + 6];
		float z2 = Squares[i + 7];
		float texX2 = Squares[i + 8];
		float texY2 = Squares[i + 9];

		float x3 = Squares[i + 10];
		float y3 = Squares[i + 11];
		float z3 = Squares[i + 12];
		float texX3 = Squares[i + 13];
		float texY3 = Squares[i + 14];

		float x4 = Squares[i + 15];
		float y4 = Squares[i + 16];
		float z4 = Squares[i + 17];
		float texX4 = Squares[i + 18];
		float texY4 = Squares[i + 19];

		triangles.insert(triangles.end(), {x1, y1, z1, texX1, texY1, x2, y2, z2, texX2, texY2, x3,
										   y3, z3, texX3, texY3});

		triangles.insert(triangles.end(), {x1, y1, z1, texX1, texY1, x3, y3, z3, texX3, texY3, x4,
										   y4, z4, texX4, texY4});
	}
	return triangles;
}