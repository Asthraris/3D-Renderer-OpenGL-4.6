#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<iostream>
#include "C_Shader.h"
#include "C_Buffer.h"
#include "src/shapeDATA.h"
#include "genShape.h"
	
const short int WINDOW_WIDTH = 480;
const short WINDOW_HEIGHT = 480;
const float BGcolor[4] = { 0.7f , 0.75f , 0.85f , 1.0f };


bool ErrorLog();
void UserInput(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
	float CURR_TIME , PREV_TIME =0;
	float DELTA_TIME;
	float FPS;


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

	//step2 - make window size responsive
	// HINT
	//glfwSetFramebufferSizeCallback(Apple, resize_window);

	glClearColor(BGcolor[0], BGcolor[1], BGcolor[2], BGcolor[3]);
	//specifys clear colour remember not background collor but main colour of window

	shapeDATA mess = genShape::genCUBE();
	
	C_Buffer cache;
	cache.parseBuffer(mess);
	//itna hosiyari ke jagah me TOTALtiangle bhi use kar sakta tha but wahi hard coded way is not better
	
	C_Shader newShader;
	newShader.activate();

	glfwSetKeyCallback(Apple,UserInput);
	while (!glfwWindowShouldClose(Apple)) {
		CURR_TIME = glfwGetTime();
		DELTA_TIME = CURR_TIME - PREV_TIME;
		FPS = 1 / DELTA_TIME;
		//std::cout << FPS << "\n" ;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// previus buffer jo rewrite nhi huwa usko clean karta hai even when new elements is not drawn at top
		
		glBindVertexArray(cache.vertexArrayScript);

		glDrawElements(GL_TRIANGLES, mess.NUM_INDEXES, GL_UNSIGNED_INT, 0);//drawarray sirf vertecis data ko draw karta hai but agar elemnt specify kiya tab gpu indexed buffer read karke uske vertices draw karta hai

		glfwSwapBuffers(Apple);
		//swaps loaded buffer with present buffer
		glfwPollEvents();
		if (ErrorLog())  std::cout << "An OpenGL error occurred!  \n " ; 

		PREV_TIME = CURR_TIME;

	}
	glfwDestroyWindow(Apple);
	cache.clean();
	newShader.revoke();

	glfwTerminate();
	return 0;
}

void UserInput(GLFWwindow* window , int key ,int scancode , int action ,int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)glfwSetWindowShouldClose(window, true);
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
