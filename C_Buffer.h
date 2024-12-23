#pragma 
#include "src/shapeDATA.h"
#include <glm/glm.hpp>
#include <vector>
class C_Buffer
{
private :
	
public:
	unsigned int vertexArrayID;
	unsigned int vertexBufferID;
	unsigned int instancedBufferID;
	unsigned int IndexedBufferID;
	std::vector <glm::mat4> InstanceData;
	C_Buffer();
	void parseBuffer( shapeDATA& shapedata);
	void colorDivisor();
	void createInstances(glm::mat4 demoModel);
	void buildInstances(float scale, float DEGangle, glm::vec3 rotateAXis, glm::vec3 Position);
	void sendInstances( );
	void clearInstances();
	void deleteInstances(short index );
	void TRUNCATE();
	void DROP();
};

