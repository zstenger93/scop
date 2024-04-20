#include "includes/render.hpp"

#include "includes/camera.hpp"
#include "includes/keyPress.hpp"
#include "includes/object.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "includes/texture.hpp"
#define STB_IMAGE_IMPLEMENTATION

void renderingLoop(GLFWwindow *window, Shader &shader, Camera &camera, Object &object) {
	int version = 1;
	int light = 2;
	int prevTex = -1;
	glm::vec3 color(1.0f, 0.0f, 0.0f);
	while (!glfwWindowShouldClose(window)) {
		createTexture(object, prevTex);
		camera.fps(camera);
		keyPressHandler(window, version, camera, object, shader, color);
		shader.settings(object);
		shader.use();
		shader.setTexture_OR_setColor(shader, version, color, light);
		shader.setModel(camera, shader, object.model);
		shader.setPerspective(camera, shader);
		shader.setView(camera, shader);
		draw(object);
		renderText(window, object, color);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
