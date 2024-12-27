#pragma once

#include <glm/matrix.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "C_Shader.h"
class Camera
{
public:
	int winWidth, winHeight;
	float FOV , nearPlane ,farPlane;
	glm::mat4 projectionMatrix;
	glm::mat4 ViewMatrix;

	glm::vec3 UP ;
	//axis of cameras up direction
	glm::vec3 Stand;
	//position of camera in world cordinate
	glm::vec3 Focus;
	//focus hamesa unit vector hona chaiye nhi toh inputs me problem aayegi

	float Speed ;
	int finalMatLOCATION;


	Camera(int width, int height, float fov, float nearplane, float farplane , C_Shader shader);
	void CamInputs(GLFWwindow * window , float deltaTime);
	void compMatrix();
	void UpdateProjection(int width , int height);
	void CamMouseMove(GLFWwindow *window  , double deltaTime);

};

