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
		keyPressHandler_Color_OR_Texture(window, version, object);
		keyPressHandler_SetColorVersion(window, version, object);
		keyPressHandler_Camera_Speed(window, camera, object);
		keyPressHandler_ObjectCenterRotation(window, object);
		keyPressHandler_SetLight(window, shader, object);
		keyPressHandler_Camera_wasdSpaceX(window, camera);
		keyPressHandler_PolygonModes(window, object);
		keyPressHandler_SetColor(window, color);
		shader.settings(object.renderMode, object.texture);
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
