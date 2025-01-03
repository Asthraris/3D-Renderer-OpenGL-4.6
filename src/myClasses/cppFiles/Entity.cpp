#include "../headers/Entity.h"
#include "../../utils/shapeDATA.h"

#include <glm/gtc/matrix_transform.hpp>
#include <random>


//Update :  yaha par saare pos 1 se 0.5 kiya because cube ka size 2 unit horaha tha since 1 from both side

shapeDATA Entity::genTRIANGLE()
{
    shapeDATA ret;

    ret.vertices = new VERTEX[3]{
    {glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) , glm::vec3(0.0f , 1.0f ,0.0f)},  // Red vertex
    {glm::vec3(0.0f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f) ,glm::vec3(0.0f , 1.0f ,0.0f)},  // Green vertex
    {glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) ,glm::vec3(0.0f , 1.0f ,0.0f)}    // Blue vertex
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

shapeDATA Entity::genPLANE(float width, float height)
{
    shapeDATA sqr;

    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;

    // Plane vertices and indices
    sqr.vertices = new VERTEX[4]{
        {glm::vec3(-halfWidth, 0.0f, -halfHeight), glm::vec3(1.0f, 0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)}, // Bottom-left
        {glm::vec3(halfWidth, 0.0f, -halfHeight), glm::vec3(0.5f, 1.0f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f)}, // Bottom-right
        {glm::vec3(halfWidth, 0.0f,  halfHeight), glm::vec3(0.5f, 0.5f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // Top-right
        {glm::vec3(-halfWidth, 0.0f,  halfHeight), glm::vec3(0.0f, 0.75f, 0.75f), glm::vec3(0.0f, 1.0f, 0.0f)}  // Top-left
    };

    sqr.NUM_POINTS = 4;

    sqr.indexes = new unsigned int [6] {0, 1, 2, 0, 2, 3};

    sqr.NUM_INDEXES = 6;
    return sqr;
}

shapeDATA Entity::genCUBE()
{
    shapeDATA cub;
    cub.vertices = new VERTEX[24]{
        // Back face (normal: 0, 0, -1)
        {glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.5f, 0.5f), glm::vec3(0.0f,  0.0f, -1.0f)}, // Top-left
        {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 1.0f, 0.5f), glm::vec3(0.0f,  0.0f, -1.0f)}, // Bottom-left
        {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 1.0f), glm::vec3(0.0f,  0.0f, -1.0f)}, // Bottom-right
        {glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.75f, 0.75f), glm::vec3(0.0f,  0.0f, -1.0f)}, // Top-right

        // Front face (normal: 0, 0, 1)
        {glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.7f, 0.2f, 0.2f), glm::vec3(0.0f,  0.0f,  1.0f)}, // Top-left
        {glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.2f, 0.7f, 0.2f), glm::vec3(0.0f,  0.0f,  1.0f)}, // Bottom-left
        {glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.2f, 0.2f, 0.7f), glm::vec3(0.0f,  0.0f,  1.0f)}, // Bottom-right
        {glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.6f, 0.4f, 0.5f), glm::vec3(0.0f,  0.0f,  1.0f)}, // Top-right

        // Left face (normal: -1, 0, 0)
        {glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.7f, 0.2f, 0.2f), glm::vec3(-1.0f,  0.0f,  0.0f)}, // Top-front
        {glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.2f, 0.7f, 0.2f), glm::vec3(-1.0f,  0.0f,  0.0f)}, // Bottom-front
        {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 1.0f, 0.5f), glm::vec3(-1.0f,  0.0f,  0.0f)}, // Bottom-back
        {glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.5f, 0.5f), glm::vec3(-1.0f,  0.0f,  0.0f)}, // Top-back

        // Right face (normal: 1, 0, 0)
        {glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.6f, 0.4f, 0.5f), glm::vec3(1.0f,  0.0f,  0.0f)}, // Top-front
        {glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.2f, 0.2f, 0.7f), glm::vec3(1.0f,  0.0f,  0.0f)}, // Bottom-front
        {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 1.0f), glm::vec3(1.0f,  0.0f,  0.0f)}, // Bottom-back
        {glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.75f, 0.75f), glm::vec3(1.0f,  0.0f,  0.0f)}, // Top-back

        // Top face (normal: 0, 1, 0)
        {glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(1.0f, 0.5f, 0.5f), glm::vec3(0.0f,  1.0f,  0.0f)}, // Back-left
        {glm::vec3(0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.75f, 0.75f), glm::vec3(0.0f,  1.0f,  0.0f)}, // Back-right
        {glm::vec3(0.5f,  0.5f,  0.5f), glm::vec3(0.6f, 0.4f, 0.5f), glm::vec3(0.0f,  1.0f,  0.0f)}, // Front-right
        {glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.7f, 0.2f, 0.2f), glm::vec3(0.0f,  1.0f,  0.0f)}, // Front-left

        // Bottom face (normal: 0, -1, 0)
        {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 1.0f, 0.5f), glm::vec3(0.0f, -1.0f,  0.0f)}, // Back-left
        {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 1.0f), glm::vec3(0.0f, -1.0f,  0.0f)}, // Back-right
        {glm::vec3(0.5f, -0.5f,  0.5f), glm::vec3(0.2f, 0.2f, 0.7f), glm::vec3(0.0f, -1.0f,  0.0f)}, // Front-right
        {glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.2f, 0.7f, 0.2f), glm::vec3(0.0f, -1.0f,  0.0f)}  // Front-left
    };


    cub.NUM_POINTS = 24;
    cub.indexes = new unsigned int[36] {
        0, 1, 2, 0, 2, 3,  // Back face
            4, 5, 6, 4, 6, 7,  // Front face
            8, 9, 10, 8, 10, 11, // Left face
            12, 13, 14, 12, 14, 15, // Right face
            16, 17, 18, 16, 18, 19, // Top face
            20, 21, 22, 20, 22, 23  // Bottom face
        };
    cub.NUM_INDEXES = 36;

    return cub;
}
shapeDATA Entity::genPYRAMID() {
    shapeDATA pyr;

    // Define the vertices of the pyramid with per-face normals
    pyr.vertices = new VERTEX[18]{
        // Front face
        {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.7f, 0.0f, 0.0f), glm::vec3(0.0f, 0.447f, 0.894f)},  // Bottom-right
        {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.7f, 0.0f, 0.0f), glm::vec3(0.0f, 0.447f, 0.894f)}, // Bottom-left
        {glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.447f, 0.894f)},    // Apex

        // Left face
        {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.7f, 0.0f, 0.0f), glm::vec3(-0.894f, 0.447f, 0.0f)}, // Bottom-left
        {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.7f, 0.0f, 0.0f), glm::vec3(-0.894f, 0.447f, 0.0f)}, // Top-left
        {glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(-0.894f, 0.447f, 0.0f)},    // Apex

        // Back face
        {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.7f, 0.0f, 0.0f), glm::vec3(0.0f, 0.447f, -0.894f)}, // Top-left
        {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.7f, 0.0f, 0.0f), glm::vec3(0.0f, 0.447f, -0.894f)},  // Top-right
        {glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.447f, -0.894f)},    // Apex

        // Right face
        {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.7f, 0.0f, 0.0f), glm::vec3(0.894f, 0.447f, 0.0f)},  // Top-right
        {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.7f, 0.0f, 0.0f), glm::vec3(0.894f, 0.447f, 0.0f)},   // Bottom-right
        {glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.894f, 0.447f, 0.0f)},    // Apex

        // Base face
        {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.7f), glm::vec3(0.0f, -1.0f, 0.0f)},      // Bottom-right
        {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 0.7f), glm::vec3(0.0f, -1.0f, 0.0f)},     // Bottom-left
        {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.7f), glm::vec3(0.0f, -1.0f, 0.0f)},    // Top-left
        {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.7f), glm::vec3(0.0f, -1.0f, 0.0f)}       // Top-right
    };

    pyr.NUM_POINTS = 18;

    // Define the indices for the pyramid
    pyr.indexes = new unsigned int[18] {
        // Faces connecting base to the apex
        0, 1, 2,  // Front face
            3, 4, 5,  // Left face
            6, 7, 8,  // Back face
            9, 10, 11, // Right face

            // Base of the pyramid
            12, 13, 14, // First triangle
            12, 14, 15  // Second triangle
        };

    pyr.NUM_INDEXES = 18;

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
    glm::mat4* temp = new glm::mat4(1.0f);
    *temp = glm::scale(*temp, glm::vec3(scale));
    *temp = glm::translate(*temp, Position);
    shape.InstanceData.push_back(*temp);
    delete temp; // Clean up the dynamically allocated memory

}

//new random way
void Entity::randomInstances(shapeDATA& shape, int numINT, float scale, int posMax)
{
    static std::random_device rd;  // Seed generator
    static std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_real_distribution<float> rotationDist(0.0f, 360.0f);
    std::uniform_real_distribution<float> positionDist(-float(posMax), float(posMax));
    std::uniform_real_distribution<float> scaleDist(scale, scale);

    glm::mat4 temp;
    for (int i = 0; i < numINT; i++)
    {
        temp = glm::mat4(1.0f);
        temp = glm::scale(temp, glm::vec3(scaleDist(gen), scaleDist(gen), scaleDist(gen)));
        temp = glm::rotate(temp, glm::radians(rotationDist(gen)), glm::normalize(glm::vec3(positionDist(gen), positionDist(gen), positionDist(gen))));
        temp = glm::translate(temp, glm::vec3(positionDist(gen), positionDist(gen), positionDist(gen)));
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


