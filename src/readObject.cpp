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

		}
        if (prefix == "v") {
            Vertex vertex;
            stream >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if (prefix == "f") {
            std::vector<int> faceIndices;
            int index;
            char slash;
            while (stream >> index >> slash) {
                faceIndices.push_back(index - 1);
            }
            faces.push_back(faceIndices);
        }
    }

    objFile.close();
}