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
		std::string prefix, materialFileName, materialLibrary;
		std::istringstream stream(line);
		std::vector<int> faceIndices;
		stream >> prefix;
		Vertex vertex;
		char slash;
		int index;

		if (prefix == "o") {
			stream >> name;
		} else if (prefix == "mtllib") {
			stream >> materialFileName;
			materialLibrary = "resources/" + materialFileName;
			loadMtllibFile(materialLibrary);
		} else if (prefix == "v") {
			stream >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
		} else if (prefix == "f") {
			while (stream >> index) {
				faceIndices.push_back(index);
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

void Object::loadMtllibFile(const std::string& filePath) {
	std::ifstream materialFile(filePath);
	std::string attribute;

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
		std::cerr << "Failed to open material library: " << filePath << std::endl;
	}
}