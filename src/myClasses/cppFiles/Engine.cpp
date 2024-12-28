#include "../headers/Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../../utils/shapeDATA.h"




//#include <iostream>
//#include <glm/gtx/string_cast.hpp>


Engine::Engine() :vertexBufferID(0), IndexedBufferID(0) , instancedBufferID(0) ,totalSHAPES(0)
{
	vertProps.bufferGAPs.push_back(0);
	indexProps.bufferGAPs.push_back(0);
	InstanceProps.bufferGAPs.push_back(0);
	//start value for gap is set to zero fo phela offset 0 ka hoga
	glGenVertexArrays(1, &vertexArrayID);
	// vertex array make opengl remenber this buffer data aka verticles format so we dont have to specify every time the gpu loads in while loop hence without this gpu will render only once traingle
	glBindVertexArray(vertexArrayID);
	//yaha professional log unbind kardede hai but mai kyuki Cubuffer iniatlize karke uske ki use karunga so no need
}

//for 3D data or 3point system
void Engine::parseBuffer(std::vector <shapeDATA>& MESS)
{
	totalSHAPES = MESS.size();

	for (int i = 0; i < totalSHAPES; i++) {
		vertProps.allocateBufferSize += MESS[i].VERTsize();
		indexProps.allocateBufferSize += MESS[i].INDsize();
		InstanceProps.allocateBufferSize += MESS[i].sizeInstanceinBYTES();

		vertProps.bufferGAPs.push_back(MESS[i].VERTsize());
		indexProps.bufferGAPs.push_back(MESS[i].INDsize());
		InstanceProps.bufferGAPs.push_back(MESS[i].sizeInstanceinBYTES());
		renderIndexforeachShape.push_back(MESS[i].NUM_INDEXES);
	};

	//1 idhar no of buffer ke baare me hai
	glGenBuffers(1, &vertexBufferID);
	//Buffer is just block of raw data which can be passed to Gpu
	//unsigned int  ke form me buffer ki loaction store hoti hai isliye hum %uint send karte hai to gen buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	// jo buffer declare kiya uska type batate hai like array data hai ya indexed data hai


	glBufferData(GL_ARRAY_BUFFER, vertProps.allocateBufferSize, NULL, GL_DYNAMIC_DRAW);
	//buffer me jo data hai woh hum specify karte hai like
	//array,kitne saare data fill karna hai in buffer, fir ye  data copy kaha se karna hai, or us data ka kaam kya hai
	for (int i = 0; i < totalSHAPES; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER,vertProps.bufferGAPs[i], MESS[i].VERTsize(), MESS[i].vertices);
	};

	glEnableVertexAttribArray(0);
	//ye gpu ke liye reading format of data allow karta hai ki hum gpu ko bataye 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3)*2, (void*)offsetof(VERTEX, POS));
	//is func me buffer kaha se read karna hai , ek processed dat ka size ky
	//a hai here 3xyz POS, normalized karna hai ya nhi(-1:1), strike = steps for next data, void ptr ko act as cursur for gpu

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) *2, (void*)offsetof(VERTEX, COLOR));
	//yaaha 3 no of float values in one vec denote karta hai

	glGenBuffers(1, &IndexedBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexedBufferID);

	// GL_ELEMENT_ARRAY_BUFFER ek enum hai for letting gpu know its not raw data but index
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexProps.allocateBufferSize, NULL, GL_DYNAMIC_DRAW);
	//yaha par humne ek new buffer create kiya to send index of vertecies dont know about the space complexity stuff 
	//weather its efficient this way

	for (int i = 0; i < totalSHAPES; i++){
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, indexProps.bufferGAPs[i], MESS[i].INDsize(), MESS[i].indexes);
	};

	glGenBuffers(1, &instancedBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, instancedBufferID);
	glBufferData(GL_ARRAY_BUFFER, InstanceProps.allocateBufferSize,NULL, GL_DYNAMIC_DRAW);
	//error mera isliye aaraha tha because i did vertexatrrib after binding indexed buffer remember to 
	for (int i = 0; i < totalSHAPES; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER,InstanceProps.bufferGAPs[i] ,MESS[i].sizeInstanceinBYTES(),MESS[i].InstanceData.data());
	}

	for (int i = 2; i <= 5; i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)((i - 2) * sizeof(glm::vec4)));
		glVertexAttribDivisor(i, 1);
	}

	glBindVertexArray(0);
}


//send first color for entire instance
void Engine::colorDivisor()
{
	glVertexAttribDivisor(1, 1);

}



void Engine::renderVertArray(std::vector <shapeDATA>& MESS)
{
	glBindVertexArray(vertexArrayID);
	for (int i = 0; i < totalSHAPES; i++) {
		glDrawElementsInstanced(GL_TRIANGLES, indexProps.bufferGAPs[i+1] / sizeof(unsigned int), GL_UNSIGNED_INT, (void*)indexProps.bufferGAPs[i] , MESS[i].InstanceData.size());//drawarray sirf vertecis data ko draw karta hai but agar elemnt specify kiya tab gpu indexed buffer read karke uske vertices draw karta hai
	}
	glBindVertexArray(0);
}




void Engine::TRUNCATE()
{
	
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteBuffers(1, &IndexedBufferID);
	glDeleteBuffers(1, &instancedBufferID);
}



void Engine::DROP()	{

	// Delete buffers before terminating GLFW
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteBuffers(1, &IndexedBufferID);
	glDeleteBuffers(1 ,&instancedBufferID);

	// Delete vertex array
	glDeleteVertexArrays(1, &vertexArrayID);
}

