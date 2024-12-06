#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void userInput(GLFWwindow *window);

void resize_window(GLFWwindow* window, int WIDTH, int HEIGHT);

static unsigned int CreateShader(const std::string& vertexSh, const std::string& fragmentSh);

static unsigned int CompileShader(unsigned int type, const std::string& sourceCode);

int main() {

	if (!glfwInit())return 1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//specify to show which gl version is we using and core or waht level

	GLFWwindow* window = glfwCreateWindow(1080, 720, "WHAt THE Fuck", NULL, NULL);
	//creates window of size with 1st null value shouws to fullscreen or not , 2nd is mystery

	glfwMakeContextCurrent(window);
	//make our all context region to screen

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	//loads glad for usage 
	//opengl provides some function in driver of gpu which i used by gpu but for us to use that func we need their address so glad gives us address of func if we dont use glad we need to use windows pointer to get func add.

	glViewport(0, 0, 1080, 720);
	//step2 - make window size responsive
	// HINT
	//glfwSetFramebufferSizeCallback(window, resize_window);

	const float vertices[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, 0.8f, 0.0f,
		-0.5f, -0.0f, 0.0f,
	};
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	// vertex array make opengl remenber this buffer data aka verticles format so we dont have to specify every time the gpu loads in while loop hence without this gpu will render only once traingle
	glBindVertexArray(vao);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER,9*sizeof(float), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void *)0);

	std::string vertexShader =
		"#version 330 core							\n"
		"layout(location = 0 ) in vec4 position;	\n"
		"void main(){								\n"
		"	gl_Position = position;					\n"
		"}											\n";
	std::string fragmnetShader =
		"#version 330 core							\n"
		"layout(location = 0 ) out vec4 color;	\n"
		"void main(){								\n"
		"	color = vec4(1.0,0.0,0.0,1.0);			\n"
		"}											\n";

	unsigned int shader = CreateShader(vertexShader,fragmnetShader);
	glUseProgram(shader);
	int success;
	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
	}

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES,0,3);
		// takes user input
		userInput(window);

		glfwSwapBuffers(window);
		//swapps loaded buffer with present buffer
		glfwPollEvents();
		//works to detect changes in window 

	}
	glfwTerminate();
	return 0;
}

void userInput(GLFWwindow* window) {
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

void resize_window(GLFWwindow* window, int WIDTH, int HEIGHT)
{
	glViewport(0, 0, WIDTH, HEIGHT);
}

unsigned int CreateShader(const std::string& vertexSh, const std::string& fragmentSh)
{
	unsigned int shaderPack = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexSh);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSh);

	glAttachShader(shaderPack, vs);
	glAttachShader(shaderPack, fs);
	glLinkProgram(shaderPack);
	glValidateProgram(shaderPack);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return shaderPack;
}

unsigned int CompileShader(unsigned int type, const std::string& sourceCode)
{
	unsigned int ShaderId = glCreateShader(type);
	const char* src = sourceCode.c_str();
	glShaderSource(ShaderId, 1, &src, nullptr);
	glCompileShader(ShaderId);

	//error handling entire copy of Cherno

	int result;
	glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &length);
		char* errorMSG = (char*) alloca(length * sizeof(char));
		glGetShaderInfoLog(ShaderId,length,&length,errorMSG);
		std::cout << "Error : " << ( type == GL_VERTEX_SHADER? "Vertex Shader":"Fragment Shader" ) << ": " << errorMSG << "\n";
		glDeleteShader(ShaderId);
		return 0;
	}

	return ShaderId;
}
