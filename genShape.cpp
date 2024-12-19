#include "genShape.h"
#include <glm/glm.hpp>
#include "src/shapeDATA.h"

shapeDATA genShape::genTRIANGLE()
{
    shapeDATA ret;

    ret.vertices = new VERTEX[3]{
    {glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},  // Red vertex
    {glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},  // Green vertex
    {glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}    // Blue vertex
    };
    ret.NUM_POINTS = 3;
    ret.indexes = new unsigned int[3] {0, 1, 2};

    ret.NUM_INDEXES = 3;

    return ret;
}

void genShape::deleteShapeData(shapeDATA& data)
{
    delete[] data.vertices;
    delete[] data.indexes;
    data.NUM_POINTS = 0;
    data.NUM_INDEXES = 0;
 
}
