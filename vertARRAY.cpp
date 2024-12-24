#include "vertARRAY.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "src/shapeDATA.h"


#include <cstdlib>
#include <ctime>

//#include <iostream>
//#include <glm/gtx/string_cast.hpp>


vertARRAY::vertARRAY() :vertexBufferID(0), IndexedBufferID(0) , instancedBufferID(0)
{

	glGenVertexArrays(1, &vertexArrayID);
	// vertex array make opengl remenber this buffer data aka verticles format so we dont have to specify every time the gpu loads in while loop hence without this gpu will render only once traingle
	glBindVertexArray(vertexArrayID);
	//yaha professional log unbind kardede hai but mai kyuki Cubuffer iniatlize karke uske ki use karunga so no need
}

//for 3D data or 3point system
void vertARRAY::parseBuffer(shapeDATA & shapedata )
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

	glEnableVertexAttribArray(0);
	//ye gpu ke liye reading format of data allow karta hai ki hum gpu ko bataye 
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, shapedata.VERTEX_SIZE(), (void*)offsetof(VERTEX, POS));
	//is func me buffer kaha se read karna hai , ek processed dat ka size ky
	//a hai here 3xyz POS, normalized karna hai ya nhi(-1:1), strike = steps for next data, void ptr ko act as cursur for gpu

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,shapedata.VERTEX_SIZE(), (void*)offsetof(VERTEX, COLOR));
	//yaaha 3 no of float values in one vec denote karta hai

	glGenBuffers(1, &IndexedBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexedBufferID);
	// GL_ELEMENT_ARRAY_BUFFER ek enum hai for letting gpu know its not raw data but index
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapedata.INDsize(), shapedata.indexes, GL_STATIC_DRAW);
	//yaha par humne ek new buffer create kiya to send index of vertecies dont know about the space complexity stuff 
	//weather its efficient this way

	glBindVertexArray(0);
}


//send first color for entire instance
void vertARRAY::colorDivisor()
{
	glVertexAttribDivisor(1, 1);

}

void vertARRAY::createInstances(glm::mat4 demoModel)
{
	InstanceData.push_back(demoModel);
}
void vertARRAY::buildGRID(int row, int coloum , float scale)
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < coloum; j++) {
			this->buildInstances(scale, glm::vec3(float((-row / 2) + i), float((-coloum / 2) + j), 0.0f));
		}
	}
}
// build dynamically LIMITATION- Default Scale,Rotation , Translation lineup
void vertARRAY::buildROTATIONALInstances(float scale , float DEGangle , glm::vec3 rotateAXis , glm::vec3 Position)
{
	glm::mat4 temp = glm::mat4(1.0f);
	temp = glm::scale(temp, glm::vec3(scale));
	temp = glm::rotate(temp , glm::radians(DEGangle) , rotateAXis);
	temp = glm::translate(temp, Position);
	InstanceData.push_back(temp);
}

void vertARRAY::buildInstances(float scale, glm::vec3 Position)
{
	glm::mat4 temp = glm::mat4(1.0f);
	temp = glm::scale(temp, glm::vec3(scale));
	temp = glm::translate(temp, Position);
	InstanceData.push_back(temp);
}

void vertARRAY::randomInstances(int numINT, float scale, int posMax)
{
	srand(time(NULL));

	glm::mat4 temp;
	for (int i = 0; i < numINT; i++)
	{
		temp = glm::mat4(1.0f);
		temp = glm::scale(temp, glm::vec3(scale, scale, scale));
		temp = glm::rotate(temp, glm::radians(float(rand() % 360)), glm::normalize(glm::vec3(float(rand() % 12), float(rand() % 12), float(rand() % 12))));
		temp = glm::translate(temp, glm::vec3(float(rand() % (posMax * 2) - posMax), float(rand() % (posMax * 2) - posMax), float(rand() % (posMax * 2) - posMax)));
		InstanceData.push_back(temp);
	}
}

void vertARRAY::renderVertArray(shapeDATA& shapedata)
{
	glBindVertexArray(vertexArrayID);
	glDrawElementsInstanced(GL_TRIANGLES, shapedata.NUM_INDEXES, GL_UNSIGNED_INT, 0, InstanceData.size());//drawarray sirf vertecis data ko draw karta hai but agar elemnt specify kiya tab gpu indexed buffer read karke uske vertices draw karta hai

	glBindVertexArray(0);
}


void vertARRAY::sendInstances( )
{
	glBindVertexArray(vertexArrayID);

	glGenBuffers(1, &instancedBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, instancedBufferID);
	glBufferData(GL_ARRAY_BUFFER, InstanceData.size() * sizeof(glm::mat4), InstanceData.data(), GL_STATIC_DRAW);
	//error mera isliye aaraha tha because i did vertexatrrib after binding indexed buffer remember to 
	for (int i = 2; i <= 5; i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)((i - 2) * sizeof(glm::vec4)));
		glVertexAttribDivisor(i, 1);
	}

	glBindVertexArray(0);
}

void vertARRAY::clearInstances()
{
	InstanceData.clear();
}

void vertARRAY::deleteInstances(short index)
{
	InstanceData.erase(InstanceData.begin() + index);
}

void vertARRAY::TRUNCATE()
{
	this->clearInstances();
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteBuffers(1, &IndexedBufferID);
	glDeleteBuffers(1, &instancedBufferID);
}



void vertARRAY::DROP()	{

	this->clearInstances();
	// Delete buffers before terminating GLFW
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteBuffers(1, &IndexedBufferID);
	glDeleteBuffers(1 ,&instancedBufferID);

	// Delete vertex array
	glDeleteVertexArrays(1, &vertexArrayID);
}

