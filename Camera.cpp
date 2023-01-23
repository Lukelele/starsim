#include "Camera.h"


Camera::Camera() {
	m_position = vec3(0, 0, 8);
	m_rotation = vec3(0.0f, 0.0f, -1.0f);
	deltaPosition = vec3(0, 0, 0);
}


void Camera::Move(float cameraSpeed, float sensitivity) {
	GetCursorPos(&p);

	deltaPosition.x = ((float)p.x - mousePosition.x) * sensitivity;
	deltaPosition.y = ((float)p.y - mousePosition.y) * sensitivity;

	mousePosition.x = p.x;
	mousePosition.y = p.y;


	if (GetAsyncKeyState(0x57)) {
		m_position += normalize(m_rotation) * cameraSpeed;
	}
	if (GetAsyncKeyState(0x41)) {
		m_position += normalize(cross(-m_rotation, vec3(0, 1, 0))) * cameraSpeed;
	}
	if (GetAsyncKeyState(0x53)) {
		m_position += normalize(-m_rotation) * cameraSpeed;
	}
	if (GetAsyncKeyState(0x44)) {
		m_position += normalize(cross(m_rotation, vec3(0, 1, 0))) * cameraSpeed;
	}
	if (GetAsyncKeyState(VK_SPACE)) {
		m_position += vec3(0, 1, 0) * cameraSpeed;
	}
	if (GetAsyncKeyState(VK_SHIFT)) {
		m_position += vec3(0, -1, 0) * cameraSpeed;
	}
}


void Camera::LockOn(vec3 position, float distance) {
	m_position = position - m_rotation * distance;
}
