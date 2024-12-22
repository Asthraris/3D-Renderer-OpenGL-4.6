#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
	glm::mat4 ModelMatrix ;

	int VERTsize() const{
		return NUM_POINTS * sizeof(VERTEX);
	}
	int INDsize() const{
		return NUM_INDEXES * sizeof( unsigned int);
	}
	int VERTEX_SIZE()const {
		return sizeof(VERTEX);
	}
	//send same arg for uniform scale 
	void setScale(const glm::vec3 &scale) {
		ModelMatrix = glm::scale(ModelMatrix, scale);
	}
	//arg - angles in radian and rotational axis
	void setRotation(float angleRAD, const glm::vec3& rotAXIS) {
		ModelMatrix = glm::rotate(ModelMatrix, angleRAD, rotAXIS);
	}
	//where to move
	void setPosition(const glm::vec3 &move) {
		ModelMatrix = glm::translate(ModelMatrix, move);
	}
	glm::mat4 getModel() {
		return ModelMatrix;
	}
};