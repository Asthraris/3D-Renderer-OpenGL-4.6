#include "../headers/Camera.h"
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>


#include <iostream>
const float NORMAL_SPEED = 2.5f;
const float MAXSPEED = 4.0f;
const float Accelaration = 0.01f;
const float SENSITIVITY = 90.0f;
	// ye sab config values hai 
bool FIRST_MOVE = true;
// jab humara window load hoat hai lab lastPos nhi hota is liye hum Fisrt _move boo bante hai since at staring it might cause error or disloaction
Camera::Camera(int width, int height, float fov, float nearplane, float farplane, C_Shader shader)
{
	UP = glm::vec3(0.0f, 1.0f, 0.0f);
	Stand = glm::vec3(0.0f);
	//start me pos 0.0 hoga
	Focus = glm::vec3(0.0f, 0.f, -3.0f);
	// ye start ka focus hai

	winWidth = width;
	winHeight = height;
	nearPlane = nearplane;
	farPlane = farplane;
	FOV = glm::radians(fov);
	//ye deafault set karega
	Speed = NORMAL_SPEED;
	

	projectionMatrix = glm::perspective(FOV, (float)winWidth / (float)winHeight, nearPlane, farPlane);


	camPosLOCATION = glGetUniformLocation(shader.GLSL, "CameraPosition");
	
	finalMatLOCATION = glGetUniformLocation(shader.GLSL, "finalMatrix");
}

void Camera::CamInputs(GLFWwindow* window , float deltaTime)
{
	if (glfwGetKey(window , GLFW_KEY_W) == GLFW_PRESS ){
		Stand += Speed * Focus * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Stand += Speed * (-Focus) * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Stand += Speed * glm::normalize(glm::cross(UP,Focus)) * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Stand += Speed * glm::normalize(glm::cross(Focus,UP)) * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
		Stand += Speed * UP * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		Stand += Speed * (-UP) * deltaTime;
	}
	/*
	if ((glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) && (Speed <= MAXSPEED) ) {
		Speed += Accelaration;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		Speed = NORMAL_SPEED;
	}
	
	 yaha par expected result nhi milraha becuase loop baar baar pressstate check karraha hai or mene input delay rakhahai jab 60 input hojata hai tab speed reset ho jata hai to norm */
}

void Camera::compMatrix()
{
	ViewMatrix = glm::mat4(1.0f);
	ViewMatrix = glm::lookAt(Stand,Stand+ Focus, UP);
	//yaha pe stand + focus kiya kyuki if not toh camera along focus rotatehori hai when gettin to left
	ViewMatrix = projectionMatrix * ViewMatrix;
	glUniformMatrix4fv(finalMatLOCATION, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
	glUniform3fv(camPosLOCATION , 1 , &Stand[0] );
}

void Camera::UpdateProjection(int width, int height)
{
	projectionMatrix = glm::mat4(1.0f);

	projectionMatrix = glm::perspective(FOV, (float)width / (float)height, nearPlane, farPlane);
}

void Camera::CamMouseMove(GLFWwindow* window, double deltaTime)
{
	static double lastXpos, lastYpos;
	double Xpos, Ypos;
	float offsetX, offsetY;
	//mistake 1 - not making yaw nas pitch static
	static float yaw = -90.0f, pitch = 0.0f;
	glm::vec3 tempFocus;

	glfwGetCursorPos(window, &Xpos, &Ypos);
	if (FIRST_MOVE) {
		lastXpos = Xpos;
		lastYpos = Ypos;
		FIRST_MOVE = false;
	}
	offsetX = SENSITIVITY * (float)(Xpos - lastXpos) * deltaTime;
	offsetY = SENSITIVITY * (float)(lastYpos - Ypos) * deltaTime;// idk why its reversed do research

	/*Yaw and Pitch are two of the three angles used to describe the orientation of an object in a 3D space.The third angle is Roll.

		Yaw: This is the rotation around the vertical axis(usually the y - axis).Think of yaw as turning your head left or right.If you imagine looking down at an object from above, yaw would be the angle you turn left or right.

		Pitch : This is the rotation around the lateral or horizontal axis(usually the x - axis).Imagine nodding your head up and down; that's pitch. It tilts the object up or down.*/

		// yaw & pitch records czmera angle preview and used to set next value
	yaw += offsetX;
	pitch += offsetY;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;
	/*
	agar y me topmost ans bottom most lock karna hotoh
	*/
	
	tempFocus.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	tempFocus.y = sin(glm::radians(pitch));
	tempFocus.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	Focus = glm::normalize(tempFocus);
	lastXpos = Xpos;
	lastYpos = Ypos;
}
