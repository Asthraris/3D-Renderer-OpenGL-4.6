#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<iostream>

#include "C_Shader.h"
#include "vertARRAY.h"
#include "src/shapeDATA.h"
#include "genShape.h"

#include "Camera.h"

	
//#include <glm/gtx/string_cast.hpp>
int WINDOW_WIDTH = 480;
int WINDOW_HEIGHT = 480;

float Z_CHANGE = 5.0f;

const float BGcolor[4] = { 0.7f , 0.75f , 0.85f , 1.0f };

double fpsCOUNTER() {
	static double last_time = 0.0f;
	double curr_time = glfwGetTime();
	double fps = curr_time - last_time;
	fps = 1 / fps;
	last_time = curr_time;
	return fps;
	// yaha fps mene dynamically nikala easier way bhi hai
}
bool ErrorLog();
void pollInput(GLFWwindow* window, int key, int scancode, int action, int mods);

void window_resizer(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	WINDOW_HEIGHT = height;
	WINDOW_WIDTH = width;
	
}


int main() {
	
	double FPS;

	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);


	if (!glfwInit()) {
		std::cout<<"Failed to initialize GLFW \n";
	}
	//specify to show which gl version is we using and core or waht level
	//core me humko khud array buffer banana hota hai
	//default me compactible mode par hota hai usme vao khud banta hai
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//creates window of size with 1st null value shouws to fullscreen or not , 2nd is mystery
	GLFWwindow *Apple = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "crimeMaster GOGO", nullptr, nullptr);
	if (!Apple) {
		glfwTerminate();
		std::cout<<"Failed to create GLFW window \n";
	}

	//used for FrameLimit
	//glfwSwapInterval(1);

	//make our all context region to screen
	glfwMakeContextCurrent(Apple);

	//loads glad for usage 
	//opengl provides some function in driver of gpu which i used by gpu but for us to use that func we need their address so glad gives us address of func if we dont use glad we need to use windows pointer to get func add.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout<<"Failed to initialize GLAD";
	}
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glEnable(GL_DEPTH_TEST);

	glClearColor(BGcolor[0], BGcolor[1], BGcolor[2], BGcolor[3]);
	//specifys clear colour remember not background collor but main colour of window

	shapeDATA mess = genShape::genCUBE();
	
	vertARRAY cache;
	cache.buildGRID(5, 5, 1.0f);
	//cache.colorDivisor();
	cache.parseBuffer(mess);
	cache.sendInstances();
	//itna hosiyari ke jagah me TOTALtiangle bhi use kar sakta tha but wahi hard coded way is not better
	
	C_Shader myShader;
	myShader.activate();
	
	Camera dslr(WINDOW_WIDTH , WINDOW_HEIGHT , 60.0f , 0.1f , 10.0f , myShader);

	glfwSetFramebufferSizeCallback(Apple, window_resizer);

	glfwSetKeyCallback(Apple,pollInput);
	
	while (!glfwWindowShouldClose(Apple)) {

		FPS = fpsCOUNTER();
		std::cout << FPS << "\n";
		
		
		dslr.CamInputs(Apple);
		dslr.CamMouseMove(Apple);
		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// previus buffer jo rewrite nhi huwa usko clean karta hai even when new elements is not drawn at top

	
		dslr.compMatrix();
		cache.renderVertArray(mess);
		
		glfwSwapBuffers(Apple);
		//swaps loaded buffer with present buffer
		glfwPollEvents();
		if (ErrorLog())  std::cout << "An OpenGL error occurred!  \n " ; 

	}
	glfwDestroyWindow(Apple);

	cache.DROP();
	myShader.revoke();

	glfwTerminate();
	return 0;
}

void pollInput(GLFWwindow* window , int key ,int scancode , int action ,int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}



bool ErrorLog() {
	GLenum error = glGetError();
	//fetch error and store for further use
	if (error != GL_NO_ERROR) {
		std::cout << "Main-Error Log - 0x" << error << "\n";
		return true;
	}
	else return false;
}
