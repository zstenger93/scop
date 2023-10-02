#include "includes/headers.hpp"
#include "includes/object.hpp"

void Object::loadFromObjFile(const std::string& filePath) {
	std::ifstream objFile(filePath);
	if (!objFile.is_open()) {
		std::cerr << "Error opening the file: " << filePath << std::endl;
		return;
	}

	std::string line;
	while (std::getline(objFile, line)) {
		std::istringstream stream(line);
		std::string prefix;
		stream >> prefix;

		if (prefix == "o") {
			stream >> name;
		} else if (prefix == "mtllib") {
			std::string materialFileName, materialLibrary, attribute;
			stream >> materialFileName;
			materialLibrary = "resources/" + materialFileName;
			std::ifstream materialFile(materialLibrary);

			if (materialFile.is_open()) {
				while (materialFile >> attribute) {
					if (attribute == "Ns") {
						materialFile >> Ns;
					} else if (attribute == "Ni") {
						materialFile >> Ni;
					} else if (attribute == "d") {
						materialFile >> d;
					} else if (attribute == "illum") {
						materialFile >> illum;
					} else if (attribute == "Ka") {
						materialFile >> Ka.r >> Ka.g >> Ka.b;
					} else if (attribute == "Kd") {
						materialFile >> Kd.r >> Kd.g >> Kd.b;
					} else if (attribute == "Ks") {
						materialFile >> Ks.r >> Ks.g >> Ks.b;
					}
				}
				materialFile.close();
			} else {
				std::cerr << "Failed to open material library: " << materialLibrary << std::endl;
			}
		} else if (prefix == "v") {
			Vertex vertex;
			stream >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
		} else if (prefix == "f") {
			std::vector<int> faceIndices;
			int index;
			while (stream >> index) {
				faceIndices.push_back(index);
				char slash;
				if (stream.peek() == '/') {
					stream.ignore();
					if (stream.peek() != ' ' && stream >> index) {
					}
				}
			}
			if (faceIndices.size() >= 1 && faceIndices.size() <= 4) {
				faces.push_back(faceIndices);
			} else {
				std::cerr << "Invalid face with " << faceIndices.size()
						  << " indices encountered. Ignoring.\n";
			}
		}
	}
	objFile.close();
}