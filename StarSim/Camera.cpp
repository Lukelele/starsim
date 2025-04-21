#include "Camera.h"



Camera::Camera() {
    m_position = vec3(0, 0, 8);
    m_rotation = vec3(0.0f, 0.0f, -1.0f);
    deltaPosition = vec3(0, 0, 0);
}


//void Camera::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
//        m_position += normalize(cross(-m_rotation, vec3(0, 1, 0))) * m_cameraSpeed;
//    }
//    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
//        m_position += normalize(cross(m_rotation, vec3(0, 1, 0))) * m_cameraSpeed;
//    }
//    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
//        m_position += normalize(-m_rotation) * m_cameraSpeed;
//    }
//    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
//        m_position += normalize(m_rotation) * m_cameraSpeed;
//    }
//    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
//        m_position += vec3(0, 1, 0) * m_cameraSpeed;
//    }
//    if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
//        m_position += vec3(0, -1, 0) * m_cameraSpeed;
//    }
//}
//
//
//void Camera::cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
//    deltaPosition.x = (xPos - mousePosition.x) * m_mouseSensitivity;
//    deltaPosition.y = (yPos - mousePosition.y) * m_mouseSensitivity;
//
//    mousePosition.x = xPos;
//    mousePosition.y = yPos;
//}
