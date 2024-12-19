#include "C_Shader.h"
#include "C_Buffer.h"
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>

#include<iostream>
	
const short int WINDOW_WIDTH = 480;
const short WINDOW_HEIGHT = 480;
const float BGcolor[4] = { 0.7f , 0.75f , 0.85f , 1.0f };
struct VECTOR {
	float x, y, z;
};
	
struct VERTEX {
	VECTOR POS;
	VECTOR COLOR;
};

VERTEX vertices[] = {
	// points || Color || Position
		-0.8f ,  0.8f , 0.0f ,
		0.6f ,  0.0f,  0.0f ,

		-0.8f , -0.8f , 0.0f ,
		0.6f ,  0.0f,  0.0f ,

		 0.8f , -0.8f , 0.0f ,	
		 0.6f ,  0.0f,  0.0f ,

		 0.8f ,  0.0f , 0.0f ,	
		 0.2f ,  0.0f,  0.2f ,

		 0.5f , -0.5f ,-1.0f ,	
		 0.9f ,  0.2f,  0.0f ,
		// ab baar baar points ko redeclare karke space kyu use kare ab hum indexed buffer use karenge 
	//ab gl enable depth kitya toh z axis use kar payenge 
	// imp -> near to us [-1] far most [1]
};
short TOTALPOINTS = sizeof(vertices) / sizeof(*vertices);
unsigned int IndexedVertices[] = {
	0,1,2,
	0,3,2,
	0,3,4,

};
short TOTALTRIANGLES = (sizeof(IndexedVertices) / sizeof(*IndexedVertices)) / 3 ;


bool ErrorLog();
void UserInput(GLFWwindow* window);

int main() {
	float CURR_TIME , PREV_TIME =0;
	float DELTA_TIME;
	float FPS;
	glm::vec3 aman = glm::vec3(1.0f);



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

	
	C_Buffer cache;
	cache.createBuffer(vertices, TOTALPOINTS , IndexedVertices , TOTALTRIANGLES);
	//itna hosiyari ke jagah me TOTALtiangle bhi use kar sakta tha but wahi hard coded way is not better
	cache.linkvertArray(0,3,6*sizeof(float),0); //for vertices
	cache.linkvertArray(1,3,6*sizeof(float),3); //for color
	
	C_Shader newShader;
	newShader.activate();


	//float initial_color = 0.5f;
	////takes location of gpu stored variable that is her vec4 by checking name of var
	//int U_color = glGetUniformLocation(newShader.GPUcode, "U_color");
	//if (U_color == -1) {
	//	std::cout << "Failed to find uniform location for 'U_color'  \n ";
	//}
	//glUniform4f(U_color, initial_color, 0.0f, 1 - initial_color, 1.0f);


	while (!glfwWindowShouldClose(Apple)) {
		CURR_TIME = glfwGetTime();
		DELTA_TIME = CURR_TIME - PREV_TIME;
		FPS = 1 / DELTA_TIME;
		std::cout << vertices[1].POS.x << "\n" ;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// previus buffer jo rewrite nhi huwa usko clean karta hai even when new elements is not drawn at top
		
		glBindVertexArray(cache.vertexArrayScript);

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);//drawarray sirf vertecis data ko draw karta hai but agar elemnt specify kiya tab gpu indexed buffer read karke uske vertices draw karta hai

		glfwSwapBuffers(Apple);
		//swaps loaded buffer with present buffer
		UserInput(Apple);
		glfwPollEvents();
		if (ErrorLog())  std::cout << "An OpenGL error occurred!  \n " ; 

		PREV_TIME = CURR_TIME;

	}
	glfwDestroyWindow(Apple);
	cache.revoke();
	newShader.revoke();

	glfwTerminate();
	return 0;
}

void UserInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
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
