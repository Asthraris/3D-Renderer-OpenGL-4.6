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

shapeDATA genShape::genSQUARE()
{
    shapeDATA sqr;
    sqr.vertices = new VERTEX[4]{
        {glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},  
        {glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},  
        {glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
        {glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f)},    
    };
    sqr.NUM_POINTS = 4;
    sqr.indexes = new unsigned int [6] {0, 1, 2,0, 2,3};
    sqr.NUM_INDEXES = 6;
    return sqr;
}

shapeDATA genShape::genCUBE()
{
    shapeDATA cub;
    cub.vertices = new VERTEX[8]{
        {glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        {glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
        {glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 1.0f)},

        {glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        {glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
        {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f)},
    };
    cub.NUM_POINTS = 8;
    cub.indexes = new unsigned int [36] {
            0,1,2,
            0,2,3,

            4,5,1,
            4,1,0,

            3,2,6,
            3,6,7,

            4,0,3,
            4,3,7,

            5,1,2,
            5,2,6,

            7,6,5,
            7,5,4,
        };
    cub.NUM_INDEXES = 36;

    return cub;
}

