#include "includes/render.hpp"

#include "includes/camera.hpp"
#include "includes/keyPress.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "includes/texture.hpp"
#define STB_IMAGE_IMPLEMENTATION

void renderingLoop(GLFWwindow *window, Shader &shader, Camera &camera, RenderMode &renderMode,
				   unsigned int &texture, unsigned int &VAO_triangles, unsigned int &VAO_squares,
				   std::vector<float> &Triangles, std::vector<float> &Squares) {
	int version = 1;
	glm::vec3 color(1.0f, 0.0f, 0.0f);
	while (!glfwWindowShouldClose(window)) {
		camera.fps(camera);
		keyPressHandler_Camera_wasdSpaceX(window, camera);
		keyPressHandler_Camera_Speed(window, camera);
		keyPressHandler_PolygonModes(window, renderMode);
		glm::mat4 model = keyPressHandler_ObjectCenterRotation(window, Triangles, Squares, model);
		keyPressHandler_Color_OR_Texture(window, version);
		keyPressHandler_SetColor(window, color);
		shader.settings(renderMode, texture);
		shader.use();

		shader.setTexture_OR_setColor(shader, version, color);

		shader.setPerspective(camera, shader);
		shader.setView(camera, shader);
		shader.setModel(camera, shader, model);
		draw(VAO_triangles, VAO_squares, Triangles, Squares);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
