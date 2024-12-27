#pragma once
struct shapeDATA;
class genShape
{
public:
    static void deleteShapeData(shapeDATA& data);
    static shapeDATA genTRIANGLE();
    static shapeDATA genSQUARE();
    static shapeDATA genCUBE();
    static shapeDATA genPYRAMID();
 
};

