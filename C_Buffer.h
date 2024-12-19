#pragma 
#include "src/shapeDATA.h"
class C_Buffer
{
private :
	
public:
	unsigned int vertexArrayScript;
	unsigned int vertexBufferScript;
	unsigned int vertexIndexedScript;
	C_Buffer();
	void parseBuffer(const shapeDATA& shapdata);
	void clean();
};

