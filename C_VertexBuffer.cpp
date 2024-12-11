#include "C_VertexBuffer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

C_VertexBuffer::C_VertexBuffer()
{
	vertexBufferScript = 0 ;
	vertexIndexedScript = 0;

	glGenVertexArrays(1, &vertexArrayScript);
	// vertex array make opengl remenber this buffer data aka verticles format so we dont have to specify every time the gpu loads in while loop hence without this gpu will render only once traingle
	glBindVertexArray(vertexArrayScript);
}
C_VertexBuffer::~C_VertexBuffer()
{
// Delete buffers before terminating GLFW
	glDeleteBuffers(1, &vertexBufferScript);
	glDeleteBuffers(1, &vertexIndexedScript);

// Delete vertex array
	glDeleteVertexArrays(1, &vertexArrayScript);
}
//for 3D data or 3point system
void C_VertexBuffer::CreateIndexedBuffer(const float vertices[], const short Nvert, const unsigned int index[], const short Triangles)
{
	//1 idhar no of buffer ke baare me hai
	glGenBuffers(1, &vertexBufferScript);
	//Buffer is just block of raw data which can be passed to Gpu
	//unsigned int  ke form me buffer ki loaction store hoti hai isliye hum %uint send karte hai to gen buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferScript);
	// jo buffer declare kiya uska type batate hai like array data hai ya indexed data hai
	glBufferData(GL_ARRAY_BUFFER, (Nvert * 3) * sizeof(float), vertices, GL_STATIC_DRAW);
	//buffer me jo data hai woh hum specify karte hai like
	//array,kitne saare data fill karna hai in buffer, fir ye  data copy kaha se karna hai, or us data ka kaam kya hai


	glGenBuffers(1, &vertexIndexedScript);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndexedScript);
	// GL_ELEMENT_ARRAY_BUFFER ek enum hai for letting gpu know its not raw data but index
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (Triangles * 3) * sizeof(unsigned int), index, GL_STATIC_DRAW);
	//yaha par humne ek new buffer create kiya to send index of vertecies dont know about the space complexity stuff 
	//weather its efficient this way
}

void C_VertexBuffer::linkvertArray()
{
	glEnableVertexAttribArray(0);
	//ye gpu ke liye reading format of data allow karta hai ki hum gpu ko bataye 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	//is func me buffer kaha se read karna hai , ek processed dat ka size ky
	//a hai here 3xyz POS, normalized karna hai ya nhi(-1:1), strike = steps for next data, void ptr ko act as cursur for gpu
}

