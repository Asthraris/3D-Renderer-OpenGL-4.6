#include "../headers/Entity.h"
#include "../../utils/shapeDATA.h"

#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <ctime>

//Update :  yaha par saare pos 1 se 0.5 kiya because cube ka size 2 unit horaha tha since 1 from both side

shapeDATA Entity::genTRIANGLE()
{
    shapeDATA ret;

    ret.vertices = new VERTEX[3]{
    {glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},  // Red vertex
    {glm::vec3(0.0f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},  // Green vertex
    {glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}    // Blue vertex
    };
    ret.NUM_POINTS = 3;
    ret.indexes = new unsigned int[3] {0, 1, 2};

    ret.NUM_INDEXES = 3;
    return ret;
}

void Entity::deleteShapeData(shapeDATA& data)
{
    delete[] data.vertices;
    delete[] data.indexes;
    data.NUM_POINTS = 0;
    data.NUM_INDEXES = 0;
 
}

shapeDATA Entity::genSQUARE()
{
    shapeDATA sqr;
    sqr.vertices = new VERTEX[4]{
        {glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)},
        {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)},
        {glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
        {glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f)},
    };
    sqr.NUM_POINTS = 4;
    sqr.indexes = new unsigned int [6] {0, 1, 2,0, 2,3};
    sqr.NUM_INDEXES = 6;
    return sqr;
}

shapeDATA Entity::genCUBE()
{
    shapeDATA cub;
    cub.vertices = new VERTEX[8]{
    {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(1.0f, 0.5f, 0.5f)}, // Soft Red
    {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 1.0f, 0.5f)}, // Soft Green
    {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 1.0f)}, // Soft Blue
    {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.75f, 0.75f)}, // Soft Cyan

    {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.7f, 0.2f, 0.2f)},   // Warm Red
    {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.2f, 0.7f, 0.2f)},  // Warm Green
    {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.2f, 0.2f, 0.7f)},   // Warm Blue
    {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.6f, 0.4f, 0.5f)}     // Soft Purple
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
shapeDATA Entity::genPYRAMID()
{
    shapeDATA pyr;
    pyr.vertices =new VERTEX[5]{
        {glm::vec3(0.5f,-0.5f,0.5f),glm::vec3(0.7f,0.0f,0.0f)},
        {glm::vec3(-0.5f,-0.5f,0.5f),glm::vec3(0.7f,0.0f,0.0f)},
        {glm::vec3(-0.5f,-0.5f,-0.5f),glm::vec3(0.7f,0.0f,0.0f)},
        {glm::vec3(0.5f,-0.5f,-0.5f),glm::vec3(0.7f,0.0f,0.0f)},
        {glm::vec3(0.0f,0.5f,0.0f),glm::vec3(1.0f,1.0f,1.0f)}
    };
pyr.NUM_POINTS =5;
    pyr.indexes= new unsigned int[18]{
        0,1,4,
        1,2,4,
        2,3,4,
        0,4,3,
        0,1,2,
        0,3,2
    };
pyr.NUM_INDEXES =18;
return pyr;
}

void Entity::createInstances(shapeDATA& shape, glm::mat4 &demoModel)
{
    shape.InstanceData.push_back(demoModel);
}

void Entity::buildGRID(shapeDATA& shape, int row, int coloum, float scale)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < coloum; j++) {
            float x = float((-row / 2) + i);
            float y = float((-coloum / 2) + j);
            Entity::buildInstances(shape, scale, glm::vec3(x, y, 0.0f));
        }
    }
}

void Entity::buildROTATIONALInstances(shapeDATA& shape, float scale, float DEGangle, glm::vec3 rotateAXis, glm::vec3 Position)
{
    glm::mat4 temp = glm::mat4(1.0f);
    temp = glm::scale(temp, glm::vec3(scale));
    temp = glm::rotate(temp, glm::radians(DEGangle), rotateAXis);
    temp = glm::translate(temp, Position);
    shape.InstanceData.push_back(temp);
}

void Entity::buildInstances(shapeDATA& shape, float scale, glm::vec3 Position)
{
    glm::mat4 temp = glm::mat4(1.0f);
    temp = glm::scale(temp, glm::vec3(scale));
    temp = glm::translate(temp, Position);
    shape.InstanceData.push_back(temp);

}

void Entity::randomInstances(shapeDATA& shape, int numINT, float scale, int posMax)
{
    srand(time(NULL));

    glm::mat4 temp;
    for (int i = 0; i < numINT; i++)
    {
        temp = glm::mat4(1.0f);
        temp = glm::scale(temp, glm::vec3(scale, scale, scale));
        temp = glm::rotate(temp, glm::radians(float(rand() % 360)), glm::normalize(glm::vec3(float(rand() % 12), float(rand() % 12), float(rand() % 12))));
        temp = glm::translate(temp, glm::vec3(float(rand() % (posMax * 2) - posMax), float(rand() % (posMax * 2) - posMax), float(rand() % (posMax * 2) - posMax)));
        shape.InstanceData.push_back(temp);
    }
}

void Entity::clearInstances(shapeDATA& shape)
{
    shape.InstanceData.clear();
}

void Entity::deleteInstances(shapeDATA& shape, short index)
{
    shape.InstanceData.erase(shape.InstanceData.begin() + index);
}


