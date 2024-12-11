#pragma once
#include <string> 

class Engine
{
private:
public:
	unsigned int Shader;
	std::string FragShader;
	std::string VertShader;
	GLFWwindow* window;

	Engine(unsigned int width, unsigned int height, const std::string& name);
	~Engine();
	void linkShader();
	static bool ErrorLog();
	void userInput();

	unsigned int CreateShader(const std::string& vertexSh, const std::string& fragmentSh);
	unsigned int CompileShader(unsigned int type, const std::string& sourceCode);
	void terminate();
};

