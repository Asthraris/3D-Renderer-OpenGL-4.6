#pragma once
#include <glm/glm.hpp>
#include <vector>

struct VERTEX {
	glm::vec3 POS;
	glm::vec3 COLOR;
	glm::vec3 NORMAL;
};

struct shapeDATA
{
public:
	shapeDATA() : vertices(0), NUM_POINTS(0), indexes(0), NUM_INDEXES(0) {};
	VERTEX* vertices;
	unsigned int NUM_POINTS;
	unsigned int* indexes;
	unsigned int NUM_INDEXES;
	std::vector <glm::mat4> InstanceData;


	int VERTsize() {
		return NUM_POINTS * sizeof(VERTEX);
	}
		
	int INDsize() {
		return NUM_INDEXES * sizeof(unsigned int);
	}
	int VERTEX_SIZE() {
		return sizeof(VERTEX);
	}
	int sizeInstanceinBYTES(){
		return InstanceData.size() * sizeof(glm::mat4);
	}

	
	
};