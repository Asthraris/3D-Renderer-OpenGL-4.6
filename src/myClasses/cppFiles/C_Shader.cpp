#include "../headers/C_Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


C_Shader::C_Shader()
{	
	VertShaderSource = loadShaderSource("src/shader/Shader.vert");
	FragShaderSource = loadShaderSource("src/shader/Shader.frag");
	//file path relative to solution folder not main folder

	GPUcode = CreateShader();
}
//throws error if compliation is wrong
bool C_Shader::ErrorCheck(unsigned int type,unsigned int ShaderId)
{
	int result;
	glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &length);
		char* errorMSG = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(ShaderId, length, &length, errorMSG);
		std::cout << "Shader-Error : " << (type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader") << ": " << errorMSG << "\n";
		glDeleteShader(ShaderId);
		return false;
	}
	return true;
}

//use loaded shader for GPU
void C_Shader::activate()
{
	glUseProgram(GPUcode);

	GLint success;
	glGetProgramiv(GPUcode, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(GPUcode, 512, nullptr, infoLog);
		std::cout << "Shader Linking Error: " << infoLog << "\n";
	}
}

//creates a program for gpu to run
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

//successfully compile program in human lang to machine for gpu and return its id
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


// Function to load shader code from a file
std::string C_Shader::loadShaderSource(const std::string& filepath) {
	std::ifstream file(filepath); // Open the file
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open shader file: " + filepath);
	}

	std::stringstream buffer;
	buffer << file.rdbuf(); // Read the file into the buffer
	file.close();
	return buffer.str(); // Return the file contents as a string
}

void C_Shader::revoke()
{
	glDeleteProgram(GPUcode);

}





