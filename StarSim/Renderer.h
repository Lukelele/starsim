#pragma once


#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_internal.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Shape.h"
#include "Camera.h"
#include "Body.h"
#include "System.h"
#include "Panel.h"


class Renderer
{
public:
	Renderer();
	~Renderer();

	GLFWwindow* GetWindow() { return window; }

	void InitWindow(int x = 800, int y = 600, const char* title = "Hello World");
	void Render(VertexArray &vertexArray, Shader &shader, int vertexCounts, GLenum drawType = GL_TRIANGLES);
	void Render(Shape& shape, Shader& shader, GLenum drawType = GL_TRIANGLES);
	void Render(Body& body, Shader& shader, GLenum drawType = GL_TRIANGLES);
	void Render(System& system, Shader& shader, GLenum drawType = GL_TRIANGLES);
	void Render(System& system, Shader& shader, Camera &camera,GLenum drawType = GL_TRIANGLES);
	void StartFrame();
	void Clear(float r = 0, float g = 0, float b = 0);
	void EndFrame(int fps = 60);
	long long GetElapsedTime() { return elapsedTime; }
	void Terminate();

private:
	GLFWwindow* window;
	chrono::high_resolution_clock::time_point timerStart, timerEnd;
	long elapsedTime;
};
