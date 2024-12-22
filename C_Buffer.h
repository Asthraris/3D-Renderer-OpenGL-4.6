#pragma 
#include "src/shapeDATA.h"
#include <vector>
class C_Buffer
{
private :
	
public:
	unsigned int vertexArrayID;
	unsigned int vertexBufferID;
	unsigned int instancedBufferID;
	unsigned int vertexIndexedID;
	std::vector <glm::mat4> InstanceData;
	C_Buffer();
	void parseBuffer( shapeDATA& shapedata);
	void makeInstances( shapeDATA& shapedata);
	void clean();
};

