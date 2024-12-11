#include "C_Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>


C_Shader::C_Shader()
{	
	VertShaderSource =
		"#version 330 core							\n"
		"layout(location = 0 ) in vec4 position;	\n"
		"void main(){								\n"
		"	gl_Position = position;					\n"
		"}											\n";
	FragShaderSource =
		"#version 330 core							\n"
		"layout(location = 0 ) out vec4 color;		\n"
		"uniform vec4 U_color;						\n"
		"void main(){								\n"
		"	color = U_color;			\n"
		"}											\n";

	GPUcode = CreateShader();
}
C_Shader::~C_Shader()
{
	glDeleteProgram(GPUcode);
}
bool C_Shader::ErrorCheck(unsigned int type,unsigned int ShaderId)
{
	int result;
	glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &length);
		char* errorMSG = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(ShaderId, length, &length, errorMSG);
		std::cout << "User-Error : " << (type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader") << ": " << errorMSG << "\n";
		glDeleteShader(ShaderId);
		return false;
	}
	return true;
}


unsigned int C_Shader::CreateShader()
{
	unsigned int shaderPack = glCreateProgram();
	// isme shaderpack naam ka program craete hoga that gpu ill execute eact time
	unsigned int vs = CompileShader(GL_VERTEX_SHADER,VertShaderSource );
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragShaderSource );
	//ye mera func hai to copy souce into shader as type and store them in Uint

	glAttachShader(shaderPack, vs);
	glAttachShader(shaderPack, fs);
	//ye dono ke ek me jode ga bc gpu me ek program h send karte hai hum
	glLinkProgram(shaderPack);
	//link  matlab ab hum is shader ki baat karenge abse
	glValidateProgram(shaderPack);


	glDeleteShader(vs);
	glDeleteShader(fs);
	//temp shader string ko delete kiya 

	return shaderPack;
}

unsigned int C_Shader::CompileShader(unsigned int type, const std::string& sourceCode)
{
	unsigned int ShaderId = glCreateShader(type);
	const char* src = sourceCode.c_str();
	// ye func sikhna hoga -converts string and returns first pointer loaction od str
	glShaderSource(ShaderId, 1, &src, nullptr);
	//shaderid ke location me ye string paste karo
	glCompileShader(ShaderId);
	//comiple karo that shader is correct or not

	//error handling entire copy of Cherno

	

	 return ErrorCheck(type, ShaderId) ?  ShaderId:  NULL;
}





