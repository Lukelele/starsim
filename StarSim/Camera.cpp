#include "Camera.h"
#include <iostream>

using namespace std;

Camera::Camera(vec3 position, vec3 up, float yaw, float pitch) 
    : m_front(vec3(0.0f, 0.0f, -1.0f)), m_cameraSpeed(5.0f), m_mouseSensitivity(0.1f), m_firstMouse(true) {
    m_position = position;
    m_worldUp = up;
    m_yaw = yaw;
    m_pitch = pitch;
    m_rotation = vec3(0.0f, 0.0f, -1.0f);
    deltaPosition = vec3(0, 0, 0);
    m_lastX = 600.0f; // Half of window width
    m_lastY = 450.0f; // Half of window height
    updateCameraVectors();
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = m_cameraSpeed * deltaTime;
    
    if (direction == FORWARD)
        m_position += m_front * velocity;
    if (direction == BACKWARD)
        m_position -= m_front * velocity;
    if (direction == LEFT)
        m_position -= m_right * velocity;
    if (direction == RIGHT)
        m_position += m_right * velocity;
    if (direction == UP)
        m_position += m_up * velocity;
    if (direction == DOWN)
        m_position -= m_up * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessInput(GLFWwindow* window, float deltaTime) {
    // Keyboard input
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        ProcessKeyboard(DOWN, deltaTime);
    
    // Mouse input
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    
    if (m_firstMouse) {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }
    
    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos; // Reversed since y-coordinates go from bottom to top
    
    m_lastX = xpos;
    m_lastY = ypos;
    
    // Only process mouse movement if the right mouse button is held down
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        ProcessMouseMovement(xoffset, yoffset);
    }
}

mat4 Camera::GetViewMatrix() {
    return lookAt(m_position, m_position + m_front, m_up);
}

void Camera::updateCameraVectors() {
    // Calculate the new Front vector
    vec3 front;
    front.x = cos(radians(m_yaw)) * cos(radians(m_pitch));
    front.y = sin(radians(m_pitch));
    front.z = sin(radians(m_yaw)) * cos(radians(m_pitch));
    m_front = normalize(front);
    
    // Also re-calculate the Right and Up vector
    m_right = normalize(cross(m_front, m_worldUp));
    m_up = normalize(cross(m_right, m_front));
    
    // Update the rotation vector for backward compatibility
    m_rotation = m_front;
}

void Camera::Move() {
    // Legacy function - kept for compatibility
}

void Camera::LockOn() {
    // Legacy function - kept for compatibility
}

void Camera::LockOn(vec3 position, float distance) {
    m_position = position - m_front * distance;
}
