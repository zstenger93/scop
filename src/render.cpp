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
	int light = 2;
	int prevTex = -1;
	glm::vec3 color(1.0f, 0.0f, 0.0f);
	while (!glfwWindowShouldClose(window)) {
		createTexture(object, prevTex);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("window", nullptr, ImGuiWindowFlags_NoDecoration);



		// Set cursor position to the top-left corner
		ImGui::SetCursorPos(ImVec2(10, 10));

		// Render text at the top-left corner
		ImGui::Text("%s", object.text.polyCount.c_str());

		// Render other ImGui UI elements as needed

		// End ImGui frame

		camera.fps(camera);
		keyPressHandler_Camera_wasdSpaceX(window, camera);
		keyPressHandler_Camera_Speed(window, camera);
		keyPressHandler_PolygonModes(window, object.renderMode);
		glm::mat4 model =
			keyPressHandler_ObjectCenterRotation(window, object.Triangles, object.Squares, model);
		keyPressHandler_Color_OR_Texture(window, version, object);
		keyPressHandler_SetColor(window, color);
		keyPressHandler_SetColorVersion(window, version, object);
		keyPressHandler_SetLight(window, shader, object);
		shader.settings(object.renderMode, object.texture);
		shader.use();
		shader.setTexture_OR_setColor(shader, version, color, light);
		shader.setPerspective(camera, shader);
		shader.setView(camera, shader);
		shader.setModel(camera, shader, model);
		draw(object);

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
