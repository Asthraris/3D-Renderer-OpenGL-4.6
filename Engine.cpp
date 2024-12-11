#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>


Engine::Engine(unsigned int width, unsigned int height,const std::string& name)
{	

	if (!glfwInit()) {
		throw std::runtime_error("Failed to initialize GLFW");
	}

	//specify to show which gl version is we using and core or waht level
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//creates window of size with 1st null value shouws to fullscreen or not , 2nd is mystery
	window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window");
	}

	//used for FrameLimit
	//glfwSwapInterval(1);

	//make our all context region to screen
	glfwMakeContextCurrent(window);

	//loads glad for usage 
	//opengl provides some function in driver of gpu which i used by gpu but for us to use that func we need their address so glad gives us address of func if we dont use glad we need to use windows pointer to get func add.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}

	glViewport(0, 0, width, height);

	//step2 - make window size responsive
	// HINT
	//glfwSetFramebufferSizeCallback(window, resize_window);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//specifys clear colour remember not background collor but main colour of window

}

Engine::~Engine()
{
	glfwTerminate();
}




void Engine::linkShader()
{
	 VertShader =
		"#version 330 core							\n"
		"layout(location = 0 ) in vec4 position;	\n"
		"void main(){								\n"
		"	gl_Position = position;					\n"
		"}											\n";
	FragShader =
		"#version 330 core							\n"
		"layout(location = 0 ) out vec4 color;		\n"
		"uniform vec4 U_color;						\n"
		"void main(){								\n"
		"	color = U_color;			\n"
		"}											\n";
}

bool Engine::ErrorLog()
{
	GLenum error = glGetError();
	//fetch error and store for further use
	if (error != GL_NO_ERROR) {
		std::cout << "User-Error Log - 0x" << error << "\n";
		return true;
	}
	else return false;
}
void Engine::userInput() {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

unsigned int Engine::CreateShader(const std::string& vertexSh, const std::string& fragmentSh)
{
	unsigned int shaderPack = glCreateProgram();
	// isme shaderpack naam ka program craete hoga that gpu ill execute eact time
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSh);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSh);
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

unsigned int Engine::CompileShader(unsigned int type, const std::string& sourceCode)
{
	unsigned int ShaderId = glCreateShader(type);
	const char* src = sourceCode.c_str();
	// ye func sikhna hoga -converts string and returns first pointer loaction od str
	glShaderSource(ShaderId, 1, &src, nullptr);
	//shaderid ke location me ye string paste karo
	glCompileShader(ShaderId);
	//comiple karo that shader is correct or not

	//error handling entire copy of Cherno

	int result;
	glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &length);
		char* errorMSG = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(ShaderId, length, &length, errorMSG);
		std::cout << "User-Error : " << (type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader") << ": " << errorMSG << "\n";
		glDeleteShader(ShaderId);
		return 0;
	}

	return ShaderId;
}

void Engine::terminate()
{
	if (Shader) {
		glDeleteProgram(Shader); // Delete shader program
	}

	glfwTerminate();
}


