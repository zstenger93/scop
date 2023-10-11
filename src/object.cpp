#include "includes/object.hpp"

void createVaoVbo(GLuint &VAO_triangles, GLuint &VAO_squares, GLuint &VBO_triangles,
				  GLuint &VBO_squares, GLuint &normalVBO, std::vector<float> &Squares,
				  std::vector<float> &Triangles, std::vector<glm::vec3> &glmNormals) {
	// Initialize VAOs and VBOs for triangles and squares
	// Generate VAO and VBO for triangles
	glGenVertexArrays(1, &VAO_triangles);
	glGenBuffers(1, &VBO_triangles);
	glBindVertexArray(VAO_triangles);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_triangles);
	glBufferData(GL_ARRAY_BUFFER, Triangles.size() * sizeof(float), Triangles.data(),
				 GL_STATIC_DRAW);
	// Specify vertex attribute pointers for triangles
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Generate VAO and VBO for squares
	glGenVertexArrays(1, &VAO_squares);
	glGenBuffers(1, &VBO_squares);
	glBindVertexArray(VAO_squares);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_squares);
	glBufferData(GL_ARRAY_BUFFER, Squares.size() * sizeof(float), Squares.data(), GL_STATIC_DRAW);
	// Specify vertex attribute pointers for squares
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	if (glmNormals.size() > 0) {
		glGenBuffers(1, &normalVBO);
		glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
		glBufferData(GL_ARRAY_BUFFER, glmNormals.size() * sizeof(glm::vec3), glmNormals.data(),
					 GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	}
}
