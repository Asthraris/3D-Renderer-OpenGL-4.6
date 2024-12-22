#include "C_Buffer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "src/shapeDATA.h"

//#include <glm/gtx/string_cast.hpp>


C_Buffer::C_Buffer() :vertexBufferID(0), vertexIndexedID(0) , instancedBufferID(0)
{

	glGenVertexArrays(1, &vertexArrayID);
	// vertex array make opengl remenber this buffer data aka verticles format so we dont have to specify every time the gpu loads in while loop hence without this gpu will render only once traingle
	glBindVertexArray(vertexArrayID);
}

//for 3D data or 3point system
void C_Buffer::parseBuffer(shapeDATA & shapedata )
{	
	//1 idhar no of buffer ke baare me hai
	glGenBuffers(1, &vertexBufferID);
	//Buffer is just block of raw data which can be passed to Gpu
	//unsigned int  ke form me buffer ki loaction store hoti hai isliye hum %uint send karte hai to gen buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	// jo buffer declare kiya uska type batate hai like array data hai ya indexed data hai
	glBufferData(GL_ARRAY_BUFFER, shapedata.VERTsize(), shapedata.vertices, GL_STATIC_DRAW);
	//buffer me jo data hai woh hum specify karte hai like
	//array,kitne saare data fill karna hai in buffer, fir ye  data copy kaha se karna hai, or us data ka kaam kya hai





	glGenBuffers(1, &instancedBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, instancedBufferID);
	glBufferData(GL_ARRAY_BUFFER , InstanceData.size() * sizeof(glm::mat4), InstanceData.data(), GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	//ye gpu ke liye reading format of data allow karta hai ki hum gpu ko bataye 
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, shapedata.VERTEX_SIZE(), (void*)offsetof(VERTEX, POS));
	//is func me buffer kaha se read karna hai , ek processed dat ka size ky
	//a hai here 3xyz POS, normalized karna hai ya nhi(-1:1), strike = steps for next data, void ptr ko act as cursur for gpu


	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,shapedata.VERTEX_SIZE(), (void*)offsetof(VERTEX, COLOR));
	//yaaha 3 no of float values in one vec denote karta hai
	/*for (const auto& mat : InstanceData) {
		std::cout << glm::to_string(mat) << std::endl;
	}*/
	for (int i = 2; i <= 5; i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer( i , 4 , GL_FLOAT , GL_FALSE , sizeof(glm::mat4), (void*)(sizeof(glm::vec3) * (i - 2)));
		// 4 beacuse 4 float jauenge as vec4  and sizeof mat 4 is 64 bytes since im sending only one matrix stride is not much use
		glVertexAttribDivisor(i, 1);
	}
	
	glGenBuffers(1, &vertexIndexedID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndexedID);
	// GL_ELEMENT_ARRAY_BUFFER ek enum hai for letting gpu know its not raw data but index
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapedata.INDsize(), shapedata.indexes, GL_STATIC_DRAW);
	//yaha par humne ek new buffer create kiya to send index of vertecies dont know about the space complexity stuff 
	//weather its efficient this way

}

void C_Buffer::makeInstances( shapeDATA& shapedata)
{
	shapedata.ModelMatrix = glm::mat4(1.0f);
	shapedata.setScale(glm::vec3(0.6f, 0.6f, 0.6f));
	shapedata.setRotation(glm::radians(60.0f), glm::vec3(1.0f, 0.7f, 0.0f));
	shapedata.setPosition(glm::vec3(1.0f, 0.0f, -3.0f));
	InstanceData.push_back(shapedata.getModel());
	shapedata.ModelMatrix = glm::mat4(1.0f);
	shapedata.setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	shapedata.setRotation(glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shapedata.setPosition(glm::vec3(1.0f, 1.0f, 1.0f));
	InstanceData.push_back(shapedata.getModel());
}



void C_Buffer::clean()	{

	// Delete buffers before terminating GLFW
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteBuffers(1, &vertexIndexedID);

	// Delete vertex array
	glDeleteVertexArrays(1, &vertexArrayID);
}

