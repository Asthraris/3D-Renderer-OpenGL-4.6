#include "Engine.h"
#include "C_VertexBuffer.h"
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
	
const short int WIDTH = 1080;
const short HEIGHT = 720;

int main() {

	Engine gigachad(WIDTH,HEIGHT,"TIRBO");

	const float vertices[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.7f,0.7f,0.0f,
		// ab baar baar points ko redeclare karke space kyu use kare ab hum indexed buffer use karenge 
	};

	unsigned int IndexedVertices[] = {
		0,1,2,0,3,1,
	};

	C_VertexBuffer B;
	B.CreateIndexedBuffer(vertices, sizeof(vertices) / (sizeof(float) * 3), IndexedVertices, 2);
	B.linkvertArray();
	
	gigachad.linkShader();
	gigachad.Shader = gigachad.CreateShader(gigachad.VertShader, gigachad.FragShader);
	glUseProgram(gigachad.Shader);

	float initial_color = 0.5f;
	//takes location of gpu stored variable that is her vec4 by checking name of var
	int U_color = glGetUniformLocation(gigachad.Shader, "U_color");
	glUniform4f(U_color, initial_color, 0.0f, 1 - initial_color, 1.0f);

	


	while (!glfwWindowShouldClose(gigachad.window)) {

		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(B.vertexArrayScript);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//drawarray sirf vertecis data ko draw karta hai but agar elemnt specify kiya tab gpu indexed buffer read karke uske vertices draw karta hai
		
		glfwSwapBuffers(gigachad.window);
		//swaps loaded buffer with present buffer
		gigachad.userInput();
		glfwPollEvents();
		if (gigachad.ErrorLog()) { std::cerr << "An OpenGL error occurred!" << std::endl; }
	}

	gigachad.terminate();
	return 0;
}
