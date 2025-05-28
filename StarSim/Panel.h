#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"
#include "Body.h"
#include "Shape.h"


using glm::vec3;
using std::vector;
using std::string;


class Panel
{
public:
	void DrawGameMenu();
	void DrawEditPanel(vector<Body*> bodies, Body* sphere, vec3 position);
	
	float GetFPSLimit() { return m_FPSLimit; }
	float GetSensitivity() { return m_sensitivity; }
	float GetCameraSpeed() { return m_cameraSpeed; }
	float GetGameSpeed() { return m_gameSpeed; }
	bool GetPaused() { return m_paused; }
	void SetPaused(bool paused) { m_paused = paused; }

	vec3 GetPosition() { return m_position; }
	vec3 GetVelocity() { return m_velocity; }
	vec3 GetAcceleration() { return m_acceleration; }
	float GetScale() { return m_scale; }
	vec3 GetRotation() { return m_rotation; }
	float GetRotationRate() { return m_rotationRate; }
	float getMass() { return m_mass; }
	string GetName() { return string(m_namearr); }

	float m_FPSLimit = 60;
	float m_sensitivity = 1;
	float m_cameraSpeed = 1;
	float m_gameSpeed = 1;
	bool m_paused = 0;
	float m_zoom = 1;

	vec3 m_position;
	vec3 m_velocity;
	vec3 m_acceleration;
	vec3 m_rotation;
	float m_rotationRate;
	float m_scale;
	float m_mass;
	char m_namearr[128];
};

