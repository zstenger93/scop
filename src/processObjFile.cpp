#include "includes/processObjFile.hpp"

#include "includes/headers.hpp"

std::vector<std::vector<Vertex>> processObjFile(const std::string &filePath, Object &object) {
	std::vector<std::vector<Vertex>> triangles;

	loadFromObjFile(filePath, object);
	if (object.vertices.size() == 0) return triangles;
	normalizeTextureCoordinates(object);
	triangleAssembly(triangles, object);
	return triangles;
}

void loadFromObjFile(const std::string &filePath, Object &object) {
	std::string line;
	std::ifstream objFile(filePath);
	if (!objFile.is_open()) {
		std::cerr << "Error opening the file: " << filePath << std::endl;
		return;
	}
	initMtl(object);
	while (std::getline(objFile, line)) {
		std::string prefix, fileName;
		std::istringstream stream(line);
		Uv uvVal;
		float normalX, normalY, normalZ;

		stream >> prefix;
		if (prefix == "o") {
			stream >> object.name;
		} else if (prefix == "mtllib") {
			saveMtlAttributes(object, stream, prefix, fileName);
		} else if (prefix == "v") {
			saveVertexCoordinates(stream, object);
		} else if (prefix == "vn") {
			stream >> normalX >> normalY >> normalZ;
			object.normals.push_back(glm::vec3(normalX, normalY, normalZ));
		} else if (prefix == "vt") {
			stream >> uvVal.u >> uvVal.v >> uvVal.w;
			object.uv.push_back(uvVal);
		} else if (prefix == "f") {
			saveFaceIndexes(stream, object);
		}
	}
	objFile.close();
}

void initMtl(Object &object) {
	object.mtl.illum = 0;
	object.mtl.Ns = 0;
	object.mtl.Ni = 0;
	object.mtl.ka.r = 0, object.mtl.ka.g = 0, object.mtl.ka.b = 0;
	object.mtl.kd.r = 0, object.mtl.kd.g = 0, object.mtl.kd.b = 0;
	object.mtl.ks.r = 0, object.mtl.ks.g = 0, object.mtl.ks.b = 0;
	object.mtl.d = 1;
}

void saveMtlAttributes(Object &object, std::istringstream &stream, std::string &prefix,
					   std::string fileName) {
	stream >> fileName;
	std::string mLine, file = "../resources/" + fileName;
	std::ifstream mtlFile(file);
	if (mtlFile.is_open()) {
		while (std::getline(mtlFile, mLine)) {
			std::istringstream stream(mLine);
			stream >> prefix;
			if (prefix == "Ns") {
				stream >> object.mtl.Ns;
			} else if (prefix == "Ka") {
				stream >> object.mtl.ka.r >> object.mtl.ka.g >> object.mtl.ka.b;
			} else if (prefix == "Kd") {
				stream >> object.mtl.kd.r >> object.mtl.kd.g >> object.mtl.kd.b;
			} else if (prefix == "Ks") {
				stream >> object.mtl.ks.r >> object.mtl.ks.g >> object.mtl.ks.b;
			} else if (prefix == "Ni") {
				stream >> object.mtl.Ni;
			} else if (prefix == "d") {
				stream >> object.mtl.d;
			} else if (prefix == "illum") {
				stream >> object.mtl.illum;
			}
		}
		mtlFile.close();
	} else
		std::cerr << "Error opening the file: " << file << std::endl;
}

void saveVertexCoordinates(std::istringstream &stream, Object &object) {
	Vertex vertex;
	stream >> vertex.x >> vertex.y >> vertex.z;
	vertex.texX = vertex.x;
	vertex.texY = vertex.y;
	object.vertices.push_back(vertex);
}

void saveFaceIndexes(std::istringstream &stream, Object &object) {
	int index, uvIndex;
	std::vector<int> faceIndices, uv_indexes;

	while (stream >> index) {
		faceIndices.push_back(index);
		if (stream.peek() == '/') {
			stream.ignore();
			object.hasSlash = true;
			stream >> uvIndex;
			uv_indexes.push_back(uvIndex);
			stream.ignore(256, ' ');
		} else
			stream.ignore(256, ' ');
	}
	if (faceIndices.size() >= 3) {
		object.faces.push_back(faceIndices);
		if (object.hasSlash == true) object.uv_index.push_back(uv_indexes);
	} else
		std::cerr << "Invalid face with " << faceIndices.size() << " Ignoring.\n";
}

void normalizeTextureCoordinates(Object &object) {
	for (auto &vertex : object.vertices) {
		float theta = atan2(vertex.z, vertex.x);
		float phi =
			acos(vertex.y / sqrt(vertex.x * vertex.x + vertex.y * vertex.y + vertex.z * vertex.z));
		vertex.texX = (theta + M_PI) / (2.0f * M_PI);
		vertex.texY = phi / M_PI;
	}
}

void triangleAssembly(std::vector<std::vector<Vertex>> &triangles, Object &object) {
	if (object.hasSlash == true) {
		for (size_t i = 0; i < object.faces.size(); ++i) {
			const auto &face = object.faces[i];
			const auto &uvIndices = object.uv_index[i];

			if (face.size() >= 3 && uvIndices.size() >= 3) {
				std::vector<Vertex> triangle;
				for (size_t j = 0; j < face.size(); ++j) {
					int index = face[j];
					int uvIndex = uvIndices[j];
					if (uvIndex > 0 && uvIndex <= static_cast<int>(object.uv.size())) {
						object.vertices[index - 1].texX = object.uv[uvIndex - 1].u;
						object.vertices[index - 1].texY = object.uv[uvIndex - 1].v;
					}
					triangle.push_back(object.vertices[index - 1]);
				}
				triangles.push_back(triangle);
			} else
				std::cerr << "Invalid face with less than 3 indices encountered. Ignoring.\n";
		}

	} else {
		for (const auto &face : object.faces) {
			if (face.size() >= 3) {
				std::vector<Vertex> triangle;
				for (int index : face) {
					if (object.uv.size() > 0) {
						object.vertices[index - 1].texX = object.uv[index - 1].u;
						object.vertices[index - 1].texY = object.uv[index - 1].v;
					}
					triangle.push_back(object.vertices[index - 1]);
				}
				triangles.push_back(triangle);
			} else
				std::cerr << "Invalid face with less than 3 indices encountered. Ignoring.\n";
		}
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
