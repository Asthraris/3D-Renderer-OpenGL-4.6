#pragma once
#include <string>      // For std::string


class C_Shader
{
private:
public:
	unsigned int GLSL;
	std::string FragShaderSource;
	std::string VertShaderSource;

	C_Shader();
	
	bool ErrorCheck(unsigned int type, unsigned int ShaderId);
	std::string loadShaderSource(const std::string& filepath);
	void activate();
	unsigned int CreateShader();
	unsigned int CompileShader(unsigned int type, const std::string& sourceCode);
	void revoke();
};

