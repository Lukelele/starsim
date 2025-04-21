#include "Shader.h"

Shader::Shader()
{
	programID = glCreateProgram();
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	programID = glCreateProgram();
	AddShadersByFilepath(vertexShaderPath, fragmentShaderPath);
	Bind();
}

Shader::~Shader()
{
	glDeleteProgram(programID);
}

void Shader::Bind() {
	glUseProgram(programID);
}

void Shader::UnBind() {
	glUseProgram(0);
}

void Shader::AddShadersBySource(const char* vertexShaderSource, const char* fragmentShaderSource) {
	GLuint vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::AddShadersByFilepath(const char* vertexShaderPath, const char* fragmentShaderPath) {
	//const char* vertexShaderSource = loadShaderSource(vertexShaderPath).c_str();
	//const char* fragmentShaderSource = loadShaderSource(fragmentShaderPath).c_str();    do not convert, pass right into function instead

	GLuint vertexShader = compileShader(loadShaderSource(vertexShaderPath).c_str(), GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(loadShaderSource(fragmentShaderPath).c_str(), GL_FRAGMENT_SHADER);

	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::SendUniform(const char* uniformName, float x) 
{
	glUniform1f(getUniformLocation(programID, uniformName), x);
}

void Shader::SendUniform(const char* uniformName, float x, float y)
{
	glUniform2f(getUniformLocation(programID, uniformName), x, y);
}

void Shader::SendUniform(const char* uniformName, float x, float y, float z)
{
	glUniform3f(getUniformLocation(programID, uniformName), x, y, z);
}

void Shader::SendUniform(const char* uniformName, float x, float y, float z, float w)
{
	glUniform4f(getUniformLocation(programID, uniformName), x, y, z, w);
}

void Shader::SendUniform(const char* uniformName, int x)
{
	glUniform1i(getUniformLocation(programID, uniformName), x);
}

void Shader::SendUniform(const char* uniformName, int x, int y)
{
	glUniform2i(getUniformLocation(programID, uniformName), x, y);
}

void Shader::SendUniform(const char* uniformName, int x, int y, int z)
{
	glUniform3i(getUniformLocation(programID, uniformName), x, y, z);
}

void Shader::SendUniform(const char* uniformName, int x, int y, int z, int w)
{
	glUniform4i(getUniformLocation(programID, uniformName), x, y, z, w);
}

void Shader::SendUniform(const char* uniformName, mat4 &matrix4) {
	glUniformMatrix4fv(getUniformLocation(programID, uniformName), 1, false, &matrix4[0][0]);
}



GLuint Shader::compileShader(const char* shaderSource, GLenum shaderType) {
	GLuint shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderSource, 0);
	glCompileShader(shaderID);

	int result;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		char message[256];
		glGetShaderInfoLog(shaderID, 256, 0, message);
		if (shaderType == GL_VERTEX_SHADER) {
			cout << "vertex shader failed to compile" << endl;
		}
		else if (shaderType == GL_FRAGMENT_SHADER) {
			cout << "fragment shader failed to compile" << endl;
		}
		cout << message << endl;

		glDeleteShader(shaderID);
	}

	return shaderID;
}

string Shader::loadShaderSource(const char* filepath) {
	ifstream file(filepath);
	string source((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));

	return source;
}

GLuint Shader::getUniformLocation(GLuint programID, const char* uniformName) {
	if (uniformLocations[uniformName] == 0) {
		uniformLocations[uniformName] = glGetUniformLocation(programID, uniformName);
		if (uniformLocations[uniformName] == -1) {
			cout << "Uniform not found" << endl;
		}
	}

	return uniformLocations[uniformName];
}