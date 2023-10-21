#include "includes/object.hpp"

void initIMGUI(GLFWwindow *window) {
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init("#version 330");
}

void renderText(Object &object, glm::vec3 &color) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowSize(ImVec2(130, 250));
	ImGui::Begin("window", nullptr, ImGuiWindowFlags_NoDecoration);
	ImGui::SetCursorPos(ImVec2(10, 10));
	ImGui::Text("___Polycount___");
	ImGui::Text("%s", object.text.polyCount.c_str());
	ImGui::Text("___RGB values___");
	std::string r = std::to_string(color.r);
	ImGui::Text("red:   %s", r.c_str());
	std::string g = std::to_string(color.g);
	ImGui::Text("green: %s", g.c_str());
	std::string b = std::to_string(color.b);
	ImGui::Text("blue:  %s", b.c_str());
	ImGui::Text("___Light Pos___");
	ImGui::Text("x:  %s", object.text.lightX.c_str());
	ImGui::Text("y:  %s", object.text.lightY.c_str());
	ImGui::Text("z:  %s", object.text.lightZ.c_str());
	ImGui::Text("__Render Mode__");
	ImGui::Text("%s", object.text.mode.c_str());
}
