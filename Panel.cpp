#include "Panel.h"



void Panel::DrawGameMenu()
{
	ImGui::Begin("Settings");


	ImGui::Text("Pause the Game");
	ImGui::SameLine(0, 15);
	ImGui::Checkbox("", (bool*)&m_paused);
	ImGui::Text("Game Settings");
	ImGui::InputFloat("FPS Limit", (float*)&m_FPSLimit, 1, 10);
	ImGui::InputFloat("Game Speed", (float*)&m_gameSpeed, 1);
	ImGui::InputFloat("Camera Speed", (float*)&m_cameraSpeed, 1);
	ImGui::InputFloat("Sensitivity", (float*)&m_sensitivity, 1);
	ImGui::InputFloat("Zoom", &m_zoom, 0.1);


	ImGui::End();
}


void Panel::DrawEditPanel(vector<Body*> bodies, Body* sphere, vec3 position)
{
	//ImGui::InputText("Name", m_namearr, sizeof(char) * 128);
	if (ImGui::Button("Add")) {
		bodies.push_back(sphere);
		bodies.back()->SetPosition(position);
	}
}
