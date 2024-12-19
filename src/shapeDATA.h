#pragma once
#include <glm/glm.hpp>
struct VERTEX {
	glm::vec3 POS;
	glm::vec3 COLOR;
};

struct shapeDATA
{
	shapeDATA(): vertices(0) , NUM_POINTS(0) , indexes(0) , NUM_INDEXES(0) { }
	VERTEX* vertices;
	unsigned int NUM_POINTS;
	unsigned int* indexes;
	unsigned int NUM_INDEXES;

	int VERTsize() const{
		return NUM_POINTS * sizeof(VERTEX);
	}
	int INDsize() const{
		return NUM_INDEXES * sizeof( unsigned int);
	}
	int VERTEX_SIZE()const {
		return sizeof(VERTEX);
	}
	

};