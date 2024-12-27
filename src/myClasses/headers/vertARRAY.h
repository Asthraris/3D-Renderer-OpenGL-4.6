#pragma 

#include <glm/glm.hpp>
#include <vector>

struct shapeDATA;

class vertARRAY
{
private :
	
public:
	unsigned int vertexArrayID;
	unsigned int vertexBufferID;
	unsigned int instancedBufferID;
	unsigned int IndexedBufferID;
	std::vector <glm::mat4> InstanceData;
	vertARRAY();
	void parseBuffer( shapeDATA& shapedata);
	void colorDivisor();
	void createInstances(glm::mat4 demoModel);
	void buildGRID(int row ,int coloum  , float scale);
	void buildROTATIONALInstances(float scale, float DEGangle, glm::vec3 rotateAXis, glm::vec3 Position);
	void buildInstances(float scale , glm::vec3 Position);
	void randomInstances(int numINT, float scale, int posMax);
	void renderVertArray(shapeDATA& shapedata);
	void sendInstances( );
	void clearInstances();
	void deleteInstances(short index );
	void TRUNCATE();
	void DROP();
};

