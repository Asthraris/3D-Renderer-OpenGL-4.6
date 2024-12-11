#pragma once
#include <string>      // For std::string


class C_Shader
{
private:
public:
	unsigned int GPUcode;
	std::string FragShaderSource;
	std::string VertShaderSource;

	C_Shader();
	~C_Shader();
	
	bool ErrorCheck(unsigned int type, unsigned int ShaderId);
	

	unsigned int CreateShader();
	unsigned int CompileShader(unsigned int type, const std::string& sourceCode);
};

