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
	unsigned int vertexArrayID;
	unsigned int vertexBufferID;
	unsigned int instancedBufferID;
	unsigned int IndexedBufferID;
	
	bufferProperties vertProps;
	bufferProperties indexProps;
	bufferProperties InstanceProps;
	
	int totalSHAPES;
	std::vector <int> renderIndexforeachShape;

	Engine();
	void parseBuffer( std::vector <shapeDATA>& MESS);
	void colorDivisor();

	void renderVertArray(std::vector <shapeDATA>& MESS);
	
	void TRUNCATE();
	void DROP();
};

