#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <functional>
#include "Shader.h"


using namespace glm;
using std::function;


enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};


class Camera
{
public:
	Camera();
    
	void LockOn(vec3 position, float distance);
	void SetPosition(vec3 position) { m_position = position; }
	vec3 GetPosition() { return m_position; }
	void SetRotation(vec3 rotation) { m_rotation = rotation; }
	vec3 GetRotation() { return m_rotation; }
	vec2 GetMouseDelta() { return deltaPosition; }
	float GetSpeed() { return m_cameraSpeed; }
	void SetSpeed(float speed) { m_cameraSpeed = speed; }
	float GetSensitvity() { return m_mouseSensitivity; }
	void SetSensitivity(float sensitivity) { m_mouseSensitivity = sensitivity; }
    
    void Move();
    void LockOn();
private:
	vec3 m_position;
	vec3 m_rotation;

	vec3 mousePosition;
	vec3 deltaPosition;

	float m_cameraSpeed = 1;
	float m_mouseSensitivity = 1;
};

