#include <string>

#include "includes/headers.hpp"
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
	} else if (glfwGetKey(window, GLFW_KEY_7) == GLFW_RELEASE)
		keyPressed = false;
	if (drawText == 1) {
		drawInfoPanel(object, color);
		drawKeyBindingsPanel();
	}
	object.end_time = std::chrono::high_resolution_clock::now();
	object.frame_duration = std::chrono::duration_cast<std::chrono::duration<double>>(
		object.end_time - object.start_time);
	object.frame_time = object.frame_duration.count();
	object.fps_count = 1 / object.frame_time;
	object.fps = std::to_string(object.fps_count);
}

void drawInfoPanel(Object &object, glm::vec3 &color) {
	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowPos(
		ImVec2(mode->width - (mode->width - 200), (mode->height - (mode->height - 50))));
	ImGui::SetNextWindowSize(ImVec2(130, 320));
	ImGui::Begin("window", nullptr, ImGuiWindowFlags_NoDecoration);
	ImGui::SetCursorPos(ImVec2(10, 10));
	ImGui::Text("___Polycount___");
	ImGui::Text("    %s", object.text.polyCount.c_str());
	ImGui::Text("__Vertex count__");
	ImGui::Text("    %s", object.text.vertexCount.c_str());
	ImGui::Text("___RGB values___");
	std::string r = std::to_string(color.r);
	ImGui::Text("Red:   %s", r.c_str());
	std::string g = std::to_string(color.g);
	ImGui::Text("Green: %s", g.c_str());
	std::string b = std::to_string(color.b);
	ImGui::Text("Blue:  %s", b.c_str());
	ImGui::Text("___Light Pos___");
	ImGui::Text("X:     %s", object.text.lightX.c_str());
	ImGui::Text("Y:     %s", object.text.lightY.c_str());
	ImGui::Text("Z:     %s", object.text.lightZ.c_str());
	ImGui::Text("__Camera speed__");
	ImGui::Text("   %s", object.text.cameraSpeed.c_str());
	ImGui::Text("__Render Mode__");
	ImGui::Text("    %s", object.text.mode.c_str());
	ImGui::Text("   ___FPS___   ");
	ImGui::Text("      %s", object.fps.c_str());
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void drawKeyBindingsPanel() {
	const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowPos(ImVec2((mode->width - 210), (mode->height - (mode->height - 50))));
	ImGui::SetNextWindowSize(ImVec2(160, 760));
	ImGui::Begin("window", nullptr, ImGuiWindowFlags_NoDecoration);
	ImGui::SetCursorPos(ImVec2(10, 10));
	ImGui::Text(" _____KEYBINDS_____");
	ImGui::Text("   __Render text__");
	ImGui::Text("      On/Off 7");
	ImGui::Text(" __General moving__");
	ImGui::Text("    Forward:   W");
	ImGui::Text("    Left:      A");
	ImGui::Text("    Backwards: S");
	ImGui::Text("    Right:     D");
	ImGui::Text("    Up:      SPACE");
	ImGui::Text("    Down:      X");
	ImGui::Text("  __Camera speed__");
	ImGui::Text("      Up:   8");
	ImGui::Text("      Down: 9");
	ImGui::Text("   __RGB values__");
	ImGui::Text("     Red:   4");
	ImGui::Text("     Green: 5");
	ImGui::Text("     Blue:  6");
	ImGui::Text("  __Render mode__");
	ImGui::Text("    Wireframe: 1");
	ImGui::Text("    Points:    2");
	ImGui::Text("    Filled:    3");
	ImGui::Text("__Object rotation__");
	ImGui::Text("      X:  U, O");
	ImGui::Text("      Y:  J, L");
	ImGui::Text("      Z:  I, K");
	ImGui::Text(" __Auto rotation__");
	ImGui::Text("       On:  P");
	ImGui::Text("       Off: 0");
	ImGui::Text("__Object rot speed__");
	ImGui::Text("      Up:   M");
	ImGui::Text("      Down: N");
	ImGui::Text("__Light position__");
	ImGui::Text("     X:  Q, E");
	ImGui::Text("     Y:  R, F");
	ImGui::Text("     Z:  G, H");
	ImGui::Text(" __Texture type__");
	ImGui::Text("     Next:  T");
	ImGui::Text("     Prev:  Y");
	ImGui::Text("  __Color type__");
	ImGui::Text("   RGB color: C");
	ImGui::Text("   Color mix: B");
	ImGui::Text("   Light on:  Z");
	ImGui::Text("   Texture:   V");

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
