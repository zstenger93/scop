#include "includes/processObjFile.hpp"

#include "includes/headers.hpp"

std::vector<std::vector<Vertex>> processObjFile(const std::string &filePath, Mtl &mtl) {
	std::vector<std::vector<int>> faces;
	std::vector<Vertex> vertices;
	std::vector<std::vector<Vertex>> triangles;

	loadFromObjFile(filePath, faces, vertices, mtl);
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
					 std::vector<Vertex> &vertices, Mtl &mtl) {
	std::ifstream objFile(filePath);
	if (!objFile.is_open()) {
		std::cerr << "Error opening the file: " << filePath << std::endl;
		return;
	}
	mtl.illum = 0;
	mtl.Ns = 0;
	mtl.Ni = 0;
	mtl.ka.r = 0, mtl.ka.g = 0, mtl.ka.b = 0;
	mtl.kd.r = 0, mtl.kd.g = 0, mtl.kd.b = 0;
	mtl.ks.r = 0, mtl.ks.g = 0, mtl.ks.b = 0;

	std::string line, mLine;
	while (std::getline(objFile, line)) {
		std::string prefix, fileName;
		std::istringstream stream(line);
		std::vector<int> faceIndices;
		Vertex vertex;
		char slash;
		int index;
		Object window;

		stream >> prefix;
		if (prefix == "o") {
			stream >> window.name;
		} else if (prefix == "mtllib") {
			stream >> fileName;
			std::string file = "../resources/" + fileName;
			std::ifstream mtlFile(file);
			if (!mtlFile.is_open()) {
				std::cerr << "Error opening the file: " << file << std::endl;
				return;
			}
			while (std::getline(mtlFile, mLine)) {
				std::istringstream stream(mLine);
				stream >> prefix;
				if (prefix == "Ns") {
					stream >> mtl.Ns;
				} else if (prefix == "Ka") {
					stream >> mtl.ka.r >> mtl.ka.g >> mtl.ka.b;
				} else if (prefix == "Kd") {
					stream >> mtl.kd.r >> mtl.kd.g >> mtl.kd.b;
				} else if (prefix == "Ks") {
					stream >> mtl.ks.r >> mtl.ks.g >> mtl.ks.b;
				} else if (prefix == "Ni") {
					stream >> mtl.Ni;
				} else if (prefix == "d") {
					stream >> mtl.d;
				} else if (prefix == "illum") {
					stream >> mtl.illum;
				}
			}
			mtlFile.close();
			std::cout << mtl.Ns << std::endl;
			std::cout << mtl.ka.r << " " << mtl.ka.g << " " << mtl.ka.b << std::endl;
			std::cout << mtl.kd.r << " " << mtl.kd.g << " " << mtl.kd.b << std::endl;
			std::cout << mtl.ks.r << " " << mtl.ks.g << " " << mtl.ks.b << std::endl;
			std::cout << mtl.Ni << std::endl;
			std::cout << mtl.d << std::endl;
			std::cout << mtl.illum << std::endl;
		} else if (prefix == "v") {
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
			std::cerr << "Invalid shape detected! " << shape.size() << std::endl;
	}
}

// our daily sponsor is deprecated functions, no i haven't spent on this one day at all, noo..
std::vector<float> convertSquaresToTriangles(const std::vector<float> &Squares) {
	std::vector<float> triangles;

	for (size_t i = 0; i < Squares.size(); i += 20) {
		if (Squares.size() == 0) break;
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