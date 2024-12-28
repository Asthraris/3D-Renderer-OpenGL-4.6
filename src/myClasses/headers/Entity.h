#pragma once

#include <glm/glm.hpp>
struct shapeDATA;
class Entity
{
public:
    static void deleteShapeData(shapeDATA& data);
    static shapeDATA genTRIANGLE();
    static shapeDATA genSQUARE();
    static shapeDATA genCUBE();
    static shapeDATA genPYRAMID();

    static void createInstances(shapeDATA &shape,glm::mat4 &demoModel);
    static void buildGRID(shapeDATA& shape, int row, int coloum, float scale);
    static void buildROTATIONALInstances(shapeDATA& shape, float scale, float DEGangle, glm::vec3 rotateAXis, glm::vec3 Position);
    static void buildInstances(shapeDATA& shape, float scale, glm::vec3 Position);
    static void randomInstances(shapeDATA& shape, int numINT, float scale, int posMax);
    static void clearInstances(shapeDATA& shape);
    static void deleteInstances(shapeDATA& shape, short index);
 
};

