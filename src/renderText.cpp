#include "includes/object.hpp"

void initIMGUI(GLFWwindow *window) {
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init("#version 330");
}
int drawText = 0;
void renderText(GLFWwindow *window, Object &object, glm::vec3 &color) {
	static bool keyPressed = false;
	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS && !keyPressed) {
		keyPressed = true;
		drawText++;
		if (drawText > 1) drawText = 0;

	} else if (glfwGetKey(window, GLFW_KEY_7) == GLFW_RELEASE) {
		keyPressed = false;
	}
	if (drawText == 1) {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::SetNextWindowPos(ImVec2(200, 100));
		ImGui::SetNextWindowSize(ImVec2(130, 290));
		ImGui::Begin("window", nullptr, ImGuiWindowFlags_NoDecoration);
		ImGui::SetCursorPos(ImVec2(10, 10));
		ImGui::Text("___Polycount___");
		ImGui::Text("%s", object.text.polyCount.c_str());
		ImGui::Text("__Vertex count__");
		ImGui::Text("%s", object.text.vertexCount.c_str());
		ImGui::Text("___RGB values___");
		std::string r = std::to_string(color.r);
		ImGui::Text("red:   %s", r.c_str());
		std::string g = std::to_string(color.g);
		ImGui::Text("green: %s", g.c_str());
		std::string b = std::to_string(color.b);
		ImGui::Text("blue:  %s", b.c_str());
		ImGui::Text("___Light Pos___");
		ImGui::Text("x:     %s", object.text.lightX.c_str());
		ImGui::Text("y:     %s", object.text.lightY.c_str());
		ImGui::Text("z:     %s", object.text.lightZ.c_str());
		ImGui::Text("__Camera speed__");
		ImGui::Text("       %s", object.text.cameraSpeed.c_str());
		ImGui::Text("__Render Mode__");
		ImGui::Text("    %s", object.text.mode.c_str());

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::SetNextWindowPos(ImVec2(1700, 100));
		ImGui::SetNextWindowSize(ImVec2(160, 690));
		ImGui::Begin("window", nullptr, ImGuiWindowFlags_NoDecoration);
		ImGui::SetCursorPos(ImVec2(10, 10));
		ImGui::Text("  ___KEYBINDINGS___");
		ImGui::Text("Render text on/off: 7");
		ImGui::Text(" __General moving__");
		ImGui::Text("    Forward: W");
		ImGui::Text("    Backwards: S");
		ImGui::Text("    Left: A");
		ImGui::Text("    Right: D");
		ImGui::Text("    Up: SPACE");
		ImGui::Text("    down: X");
		ImGui::Text(" __Camera speed__");
		ImGui::Text("      Up: 8");
		ImGui::Text("     down: 9");
		ImGui::Text("  __RGB values__");
		ImGui::Text("     Red: 4");
		ImGui::Text("    Green: 5");
		ImGui::Text("    Blue: 6");
		ImGui::Text(" __Render mode__");
		ImGui::Text("   Wireframe: 1");
		ImGui::Text("    Points: 2");
		ImGui::Text("    Filled: 3");
		ImGui::Text("__Object rotation__");
		ImGui::Text("    x:, U, O");
		ImGui::Text("    y:, J, L");
		ImGui::Text("    z:, I, K");
		ImGui::Text("__Object rot speed__");
		ImGui::Text("      Up: M");
		ImGui::Text("      down: N");
		ImGui::Text("__Light position__");
		ImGui::Text("     x:, Q, E");
		ImGui::Text("     y:, R, F");
		ImGui::Text("     z:, G, H");
		ImGui::Text(" __Texture type__");
		ImGui::Text("     next:, T");
		ImGui::Text("   previous: Y");
		ImGui::Text("  __Color type__");
		ImGui::Text("   RGB color: C");
		ImGui::Text("   Color mix: B");
		ImGui::Text("   Light on: Z");
		ImGui::Text("   Texture: V");

		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
