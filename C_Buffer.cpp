#include "C_Buffer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

C_Buffer::C_Buffer()
{
	vertexBufferScript = 0 ;
	vertexIndexedScript = 0;

	glGenVertexArrays(1, &vertexArrayScript);
	// vertex array make opengl remenber this buffer data aka verticles format so we dont have to specify every time the gpu loads in while loop hence without this gpu will render only once traingle
	glBindVertexArray(vertexArrayScript);
}

//for 3D data or 3point system
void C_Buffer::createBuffer(const float vertices[],short nVerts, const unsigned int index[], const short Triangles)
{
	//1 idhar no of buffer ke baare me hai
	glGenBuffers(1, &vertexBufferScript);
	//Buffer is just block of raw data which can be passed to Gpu
	//unsigned int  ke form me buffer ki loaction store hoti hai isliye hum %uint send karte hai to gen buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferScript);
	// jo buffer declare kiya uska type batate hai like array data hai ya indexed data hai
	glBufferData(GL_ARRAY_BUFFER, (nVerts* 6 )*sizeof(float), vertices, GL_STATIC_DRAW);
	//buffer me jo data hai woh hum specify karte hai like
	//array,kitne saare data fill karna hai in buffer, fir ye  data copy kaha se karna hai, or us data ka kaam kya hai


	glGenBuffers(1, &vertexIndexedScript);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexIndexedScript);
	// GL_ELEMENT_ARRAY_BUFFER ek enum hai for letting gpu know its not raw data but index
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (Triangles * 3) * sizeof(unsigned int), index, GL_STATIC_DRAW);
	//yaha par humne ek new buffer create kiya to send index of vertecies dont know about the space complexity stuff 
	//weather its efficient this way
}


//enable/vertex details default storey =0
void C_Buffer::linkvertArray( unsigned short page , short sweep, short gap,short start)	{
	glEnableVertexAttribArray(page);

	
	//ye gpu ke liye reading format of data allow karta hai ki hum gpu ko bataye 
	glVertexAttribPointer(page, sweep, GL_FLOAT, GL_FALSE, gap, (void*)(start*sizeof(float)));
	//is func me buffer kaha se read karna hai , ek processed dat ka size ky
	//a hai here 3xyz POS, normalized karna hai ya nhi(-1:1), strike = steps for next data, void ptr ko act as cursur for gpu
}



void C_Buffer::revoke()	{

	// Delete buffers before terminating GLFW
	glDeleteBuffers(1, &vertexBufferScript);
	glDeleteBuffers(1, &vertexIndexedScript);

	// Delete vertex array
	glDeleteVertexArrays(1, &vertexArrayScript);
}

