#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
	Camera(vec3 position = vec3(0.0f, 0.0f, 8.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
    
	void LockOn(vec3 position, float distance);
	void SetPosition(vec3 position) { m_position = position; }
	vec3 GetPosition() { return m_position; }
	void SetRotation(vec3 rotation) { m_rotation = rotation; }
	vec3 GetRotation() { return m_rotation; }
	vec3 GetFront() { return m_front; }
	vec3 GetUp() { return m_up; }
	vec3 GetRight() { return m_right; }
	vec2 GetMouseDelta() { return deltaPosition; }
	float GetSpeed() { return m_cameraSpeed; }
	void SetSpeed(float speed) { m_cameraSpeed = speed; }
	float GetSensitvity() { return m_mouseSensitivity; }
	void SetSensitivity(float sensitivity) { m_mouseSensitivity = sensitivity; }
    
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessInput(GLFWwindow* window, float deltaTime);
    mat4 GetViewMatrix();
    
    void Move();
    void LockOn();
    
private:
    void updateCameraVectors();
    
	vec3 m_position;
	vec3 m_rotation;
	vec3 m_front;
	vec3 m_up;
	vec3 m_right;
	vec3 m_worldUp;

	vec3 mousePosition;
	vec3 deltaPosition;
	
	float m_yaw;
	float m_pitch;
	
	bool m_firstMouse;
	float m_lastX;
	float m_lastY;

	float m_cameraSpeed;
	float m_mouseSensitivity;
};
