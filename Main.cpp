#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void userInput(GLFWwindow *window);

void resize_window(GLFWwindow* window, int WIDTH, int HEIGHT);

static unsigned int CreateShader(const std::string& vertexSh, const std::string& fragmentSh);

static unsigned int CompileShader(unsigned int type, const std::string& sourceCode);

static unsigned int ShaderSource(); 
	

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
		0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f,0.5f,0.0f,
		// ab baar baar points ko redeclare karke space kyu use kare ab hum indexed buffer use karenge 
	};

	unsigned int IndexedVertices[] = {
		0,1,2,0,3,1,
	};
	
	unsigned int vertexArrayScript;
	glGenVertexArrays(1, &vertexArrayScript);
	// vertex array make opengl remenber this buffer data aka verticles format so we dont have to specify every time the gpu loads in while loop hence without this gpu will render only once traingle
	glBindVertexArray(vertexArrayScript);


	//Buffer is just block of raw data which can be passed to Gpu
	unsigned int vertexBufferScript;
	//unsigned int  ke form me buffer ki loaction store hoti hai isliye hum %uint send karte hai to gen buffer
	glGenBuffers(1, &vertexBufferScript);
	//1 idhar no of buffer ke baare me hai
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferScript);
	// jo buffer declare kiya uska type batate hai like array data hai ya indexed data hai
	glBufferData(GL_ARRAY_BUFFER,(9*2)*sizeof(float), vertices, GL_STATIC_DRAW);
	//buffer me jo data hai woh hum specify karte hai like
	//array,kitne saare data fill karna hai in buffer, fir ye  data copy kaha se karna hai, or us data ka kaam kya hai


	unsigned int vertexIndexedScript;
	glGenBuffers(1, &vertexIndexedScript);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vertexIndexedScript);
	// GL_ELEMENT_ARRAY_BUFFER ek enum hai for letting gpu know its not raw data but index
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (3 * 2) * sizeof(unsigned int), IndexedVertices, GL_STATIC_DRAW);
	//yaha par humne ek new buffer create kiya to send index of vertecies dont know about the space complexity stuff 
	//weather its efficient this way


	glEnableVertexAttribArray(0);
	//ye gpu ke liye reading format of data allow karta hai ki hum gpu ko bataye 
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void *)0);
	//is func me buffer kaha se read karna hai , ek processed dat ka size kya hai here 3xyz POS , normalized karna hai ya nhi(-1:1) , strike = steps for next data , void ptr ko act as cursur for gpu

	
	glUseProgram(ShaderSource());
	//ye func iscode ko batata hai ki ye shader use karo
	
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//specifys clear colour remember not background collor but main colour of window

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(vertexArrayScript);

		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);//drawarray sirf vertecis data ko draw karta hai but agar elemnt specify kiya tab gpu indexed buffer read karke uske vertices draw karta hai



		userInput(window);

		glfwSwapBuffers(window);
		//swaps loaded buffer with present buffer
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

unsigned int ShaderSource()
{
	std::string vertexShader =
		"#version 330 core							\n"
		"layout(location = 0 ) in vec4 position;	\n"
		"void main(){								\n"
		"	gl_Position = position;					\n"
		"}											\n";
	std::string fragmentShader =
		"#version 330 core							\n"
		"layout(location = 0 ) out vec4 color;		\n"
		"void main(){								\n"
		"	color = vec4(1.0,0.0,0.0,0.5);			\n"
		"}											\n";

	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	return shader;
}
