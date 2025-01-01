#pragma 

#include <glm/glm.hpp>
#include <vector>

struct shapeDATA;

struct bufferProperties {
	int allocateBufferSize =0;
	std::vector <int> bufferGAPs;
};

class Engine
{
private :
	
public:
	unsigned int vertexBufferID;
	unsigned int IndexedBufferID;
	unsigned int instancedBufferID;
	
	bufferProperties vertProps;
	bufferProperties indexProps;
	bufferProperties InstanceProps;
	
	int totalSHAPES;
	std::vector <int> renderIndexforeachShape;
	std::vector <unsigned int> ObjectArraysID;

	Engine();
	void parseBuffer( std::vector <shapeDATA>& MESS);
	void colorDivisor();
	void UpdateSINGLEInstancesINGPU(int orderofOBJECT , int orderofINSTANCES , std::vector <shapeDATA>& MESS ,  glm::mat4& upd);
	void renderVertArray(std::vector <shapeDATA>& MESS);
	
	void TRUNCATE();
	void DROP();
};

