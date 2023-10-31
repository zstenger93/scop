#include "includes/object.hpp"

#include <__config>

void createVaoVbo(Object &object) {
	// Initialize VAOs and VBOs for triangles and squares
	// Generate VAO and VBO for triangles
	glGenVertexArrays(1, &object.VAO_triangles);
	glGenBuffers(1, &object.VBO_triangles);
	glBindVertexArray(object.VAO_triangles);
	glBindBuffer(GL_ARRAY_BUFFER, object.VBO_triangles);
	glBufferData(GL_ARRAY_BUFFER, object.Triangles.size() * sizeof(float), object.Triangles.data(),
				 GL_STATIC_DRAW);
	// Specify vertex attribute pointers for triangles
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	if (object.normals.size() > 0) {
		glGenBuffers(1, &object.normalVBO);
		glBindBuffer(GL_ARRAY_BUFFER, object.normalVBO);
		glBufferData(GL_ARRAY_BUFFER, object.normals.size() * sizeof(glm::vec3),
					 object.normals.data(), GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, object.normalVBO);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	}
}

void saveTextures(Object &object, char **argv) {
	int i = 4;

	if (argv[4] == nullptr) {
		std::cout << "No texture has been provided." << std::endl;
		exit(1);
	}
	while (argv[i] != nullptr) object.textures.push_back(argv[i++]);
}
