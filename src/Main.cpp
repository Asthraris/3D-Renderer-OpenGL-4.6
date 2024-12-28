#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<iostream>


#include "utils/shapeDATA.h"
#include "myClasses/headers/C_Shader.h"
#include "myClasses/headers/Engine.h"
#include "myClasses/headers/Entity.h"
#include "myClasses/headers/Camera.h"

#include <vector>
// ab mujhe ek hi vertexArray me multiple shapes store karna hai because switching vertearray is tedius


//#include <glm/gtx/string_cast.hpp>
int WINDOW_WIDTH = 1080;
int WINDOW_HEIGHT = 720;

glm::vec4 BGcolor = glm::vec4( 0.7f , 0.75f , 0.85f , 1.0f );

float timeCOUNTER() {
	static double last_time = 0.0f;
	double curr_time = glfwGetTime();
	float dT = (float)(curr_time - last_time);
	last_time = curr_time;
	return dT;
	// yaha fps mene dynamically nikala easier way bhi hai
}
bool ErrorLog();
void pollInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

void window_resizer(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	WINDOW_HEIGHT = height;
	WINDOW_WIDTH = width;
	
}


int main() {
	
	double deltaTime;

	if (!glfwInit()) {
		std::cout<<"Failed to initialize GLFW \n";
		return -1;
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
		return -2;
	}

	std::vector <shapeDATA> MESS;

	//used for FrameLimit
	//glfwSwapInterval(1);

	//make our all context region to screen
	glfwMakeContextCurrent(Apple);

	//loads glad for usage 
	//opengl provides some function in driver of gpu which i used by gpu but for us to use that func we need their address so glad gives us address of func if we dont use glad we need to use windows pointer to get func add.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout<<"Failed to initialize GLAD";
		return -3;
	}
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glEnable(GL_DEPTH_TEST);
	glClearColor(BGcolor.r, BGcolor.g, BGcolor.b, BGcolor.a);
	//specifys clear colour remember not background collor but main colour of window

	MESS.push_back(Entity::genCUBE());
	MESS.push_back(Entity::genPYRAMID());
	Engine cache;
	Entity::buildInstances(MESS[0], 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	Entity::buildInstances(MESS[1],1.0f, glm::vec3(0.0f, 0.0f, 3.0f));
	//cache.colorDivisor();
	cache.parseBuffer(MESS);
	//itna hosiyari ke jagah me TOTALtiangle bhi use kar sakta tha but wahi hard coded way is not better
	
	
	C_Shader myShader;
	myShader.activate();
	
	Camera dslr(WINDOW_WIDTH , WINDOW_HEIGHT , 60.0f , 0.1f , 20.0f , myShader);

	glfwSetFramebufferSizeCallback(Apple, window_resizer);

	glfwSetKeyCallback(Apple,pollInput);
	
	glfwSetInputMode(Apple, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//disable mouse to other window except opengl one
	

	while (!glfwWindowShouldClose(Apple)) {

		deltaTime = timeCOUNTER();
		std::cout << 1/deltaTime << "\n";
		
		
		dslr.CamInputs(Apple, deltaTime);
		dslr.CamMouseMove(Apple , deltaTime);
		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// previus buffer jo rewrite nhi huwa usko clean karta hai even when new elements is not drawn at top

	
		dslr.compMatrix();
		cache.renderVertArray(MESS);
		
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




bool ErrorLog() {
	GLenum error = glGetError();
	//fetch error and store for further use
	if (error != GL_NO_ERROR) {
		std::cout << "Main-Error Log - 0x" << error << "\n";
		return true;
	}
	else return false;
}
