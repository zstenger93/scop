#include "includes/render.hpp"

#include "includes/camera.hpp"
#include "includes/keyPress.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "includes/texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "includes/renderText.hpp"
#define STB_IMAGE_IMPLEMENTATION

void renderingLoop(GLFWwindow *window, Shader &shader, Camera &camera, Object &object) {
	int version = 1;
	glm::vec3 color(1.0f, 0.0f, 0.0f);
	while (!glfwWindowShouldClose(window)) {
		camera.fps(camera);
		keyPressHandler_Camera_wasdSpaceX(window, camera);
		keyPressHandler_Camera_Speed(window, camera);
		keyPressHandler_PolygonModes(window, object.renderMode);
		glm::mat4 model =
			keyPressHandler_ObjectCenterRotation(window, object.Triangles, object.Squares, model);
		keyPressHandler_Color_OR_Texture(window, version);
		keyPressHandler_SetColor(window, color);
		keyPressHandler_SetColorVersion(window, version);
		shader.settings(object.renderMode, object.texture);
		shader.use();
		shader.setTexture_OR_setColor(shader, version, color);
		shader.setPerspective(camera, shader);
		shader.setView(camera, shader);
		shader.setModel(camera, shader, model);
		draw(object);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
