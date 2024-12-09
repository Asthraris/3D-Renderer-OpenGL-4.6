#pragma once
#include <string>      // For std::string
#include<glad/glad.h>
#include <GLFW/glfw3.h> // For GLFWwindow

class Engine
{
private:
	GLFWwindow* window;
	unsigned int vertexArrayScript;
	unsigned int vertexBufferScript;
	unsigned int vertexIndexedScript;

	unsigned int Shader;
	std::string FragShader;
	std::string VertShader;
public:

	Engine(unsigned int width, unsigned int height, const std::string& name);
	~Engine();
	void process();
	void run();
	void linkShader();
	static bool ErrorLog();
	void userInput();

	unsigned int CreateShader(const std::string& vertexSh, const std::string& fragmentSh);
	unsigned int CompileShader(unsigned int type, const std::string& sourceCode);
	void terminate();
};

