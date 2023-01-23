#include "Renderer.h"


Renderer::Renderer()
{
	if (!glfwInit()) {
		cout << "glfw failed to initialise" << endl;
		return;
	}
}

Renderer::~Renderer()
{

}


void Renderer::InitWindow(int x, int y, const char* title) {
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(x, y, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		cout << "window failed to initialise" << endl;
		return;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

}


void Renderer::Render(VertexArray& vertexArray, Shader& shader, int vertexCounts, GLenum drawType) {
	vertexArray.Bind();
	shader.Bind();

	glDrawArrays(drawType, 0, vertexCounts);
}


void Renderer::Render(Shape& shape, Shader& shader, GLenum drawType) {
	shape.GetVertexArray().Bind();
	shader.Bind();

	glDrawArrays(drawType, 0, shape.GetVerticesCount());
} 


void Renderer::Render(Body& body, Shader& shader, GLenum drawType) {
	body.GetShape()->GetVertexArray().Bind();
	shader.Bind();

	mat4 translationMatrix = translate(body.GetPosition());
	shader.SendUniform("u_translationMatrix", translationMatrix);
	mat4 rotationMatrix = rotate(radians(body.GetRotationRate()), body.GetRotation());
	shader.SendUniform("u_rotationMatrix", rotationMatrix);
	mat4 scaleMatrix = glm::scale(vec3(body.GetScale(), body.GetScale(), body.GetScale()));
	shader.SendUniform("u_scaleMatrix", scaleMatrix);

	glDrawArrays(drawType, 0, body.GetShape()->GetVerticesCount());
}


void Renderer::Render(System& system, Shader& shader, GLenum drawType) {
	shader.Bind();
	for (int i = 0; i < system.GetBodies().size(); i++) {
		system.GetBodies()[i]->GetShape()->GetVertexArray().Bind();

		mat4 translationMatrix = translate(system.GetBodies()[i]->GetPosition());
		shader.SendUniform("u_translationMatrix", translationMatrix);
		mat4 rotationMatrix = rotate(radians(system.GetBodies()[i]->GetRotationRate()), system.GetBodies()[i]->GetRotation());
		shader.SendUniform("u_rotationMatrix", rotationMatrix);
		mat4 scaleMatrix = glm::scale(vec3(system.GetBodies()[i]->GetScale(), system.GetBodies()[i]->GetScale(), system.GetBodies()[i]->GetScale()));
		shader.SendUniform("u_scaleMatrix", scaleMatrix);

		glDrawArrays(drawType, 0, system.GetBodies()[i]->GetShape()->GetVerticesCount());
	}
}

void Renderer::Render(System& system, Shader& shader, Camera &camera, GLenum drawType) {
	if (GetAsyncKeyState(VK_LBUTTON)) {
		camera.SetRotation(mat3(rotate((float)(-camera.GetMouseDelta().x * 0.01), vec3(0, 1, 0))) * camera.GetRotation());
		camera.SetRotation(mat3(rotate((float)(-camera.GetMouseDelta().y * 0.01), cross(camera.GetRotation(), vec3(0, 1, 0)))) * camera.GetRotation());
	}

	mat4 cameraViewMatrix = lookAt(camera.GetPosition(), camera.GetPosition() + camera.GetRotation(), vec3(0, 1, 0));
	shader.SendUniform("u_viewMatrix", cameraViewMatrix);

	shader.Bind();
	for (int i = 0; i < system.GetBodies().size(); i++) {
		if (system.GetBodies()[i]->GetActive()) {
			system.GetBodies()[i]->GetShape()->GetVertexArray().Bind();
			mat4 translationMatrix = translate(system.GetBodies()[i]->GetPosition());
			shader.SendUniform("u_translationMatrix", translationMatrix);
			mat4 rotationMatrix = rotate(radians(system.GetBodies()[i]->GetRotationRate()), system.GetBodies()[i]->GetRotation());
			shader.SendUniform("u_rotationMatrix", rotationMatrix);
			mat4 scaleMatrix = glm::scale(vec3(system.GetBodies()[i]->GetScale(), system.GetBodies()[i]->GetScale(), system.GetBodies()[i]->GetScale()));
			shader.SendUniform("u_scaleMatrix", scaleMatrix);

			glDrawArrays(drawType, 0, system.GetBodies()[i]->GetShape()->GetVerticesCount());
		}
	}
}


void Renderer::StartFrame()
{
	timerStart = chrono::high_resolution_clock::now();

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}


void Renderer::Clear(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Renderer::EndFrame(int fps)
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
	glfwPollEvents();

	timerEnd = chrono::high_resolution_clock::now();
	float timeElapsed = chrono::duration_cast<chrono::milliseconds>(timerEnd - timerStart).count();


	if (timeElapsed < 1000 / fps) {
		Sleep(1000 / fps - timeElapsed);
		elapsedTime = 1000 / fps;
	}
	else {
		elapsedTime = timeElapsed;
	}
}


void Renderer::Terminate() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}
