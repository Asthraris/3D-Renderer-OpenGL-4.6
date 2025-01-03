#include "../headers/Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../../utils/shapeDATA.h"




#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>





Engine::Engine() :vertexBufferID(0), IndexedBufferID(0) , instancedBufferID(0) ,totalSHAPES(0)
{
	vertProps.bufferGAPs.push_back(0);
	indexProps.bufferGAPs.push_back(0);
	InstanceProps.bufferGAPs.push_back(0);
	//start value for gap is set to zero fo phela offset 0 ka hoga
	
	// vertex array make opengl remenber this buffer data aka verticles format so we dont have to specify every time the gpu loads in while loop hence without this gpu will render only once traingle
	
	//yaha professional log unbind kardede hai but mai kyuki Cubuffer iniatlize karke uske ki use karunga so no need
}

//for 3D data or 3point system
void Engine::parseBuffer(std::vector <shapeDATA>& MESS) {
        totalSHAPES = static_cast<size_t>(MESS.size());

        // Calculate buffer sizes and offsets
        for (size_t i = 0; i < totalSHAPES; i++) {
            vertProps.allocateBufferSize += MESS[i].VERTsize() ;
            indexProps.allocateBufferSize += MESS[i].INDsize() ;
            InstanceProps.allocateBufferSize += MESS[i].sizeInstanceinBYTES() ;

            vertProps.bufferGAPs.push_back(vertProps.allocateBufferSize);
            indexProps.bufferGAPs.push_back(indexProps.allocateBufferSize );
            InstanceProps.bufferGAPs.push_back(InstanceProps.allocateBufferSize );
            renderIndexforeachShape.push_back(MESS[i].NUM_INDEXES);
        }
        //generate vertarray of objects //here i m doing 1buffer for multiple object not one vertArray
        ObjectArraysID.resize(totalSHAPES);
        //made vector to hold totalShape size dynamically
        glGenVertexArrays(totalSHAPES, ObjectArraysID.data());
        //used morethan one VOA gen and sended first address of vector of unsigned int
        // Generate and bind index buffer

        glGenBuffers(1, &IndexedBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexedBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexProps.allocateBufferSize, NULL, GL_DYNAMIC_DRAW);

        for (size_t i = 0; i < totalSHAPES; i++) {
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, indexProps.bufferGAPs[i], MESS[i].INDsize(), MESS[i].indexes);
        }

        // Generate and bind vertex buffer
        glGenBuffers(1, &vertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, vertProps.allocateBufferSize, NULL, GL_DYNAMIC_DRAW);
        //fillup the buffer
        for (size_t i = 0; i < totalSHAPES; i++){
            glBufferSubData(GL_ARRAY_BUFFER, vertProps.bufferGAPs[i], MESS[i].VERTsize(), MESS[i].vertices);
        }

        // Generate and bind instanced buffer
        glGenBuffers(1, &instancedBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, instancedBufferID);
        glBufferData(GL_ARRAY_BUFFER, InstanceProps.allocateBufferSize, NULL, GL_DYNAMIC_DRAW);
        for (size_t i = 0; i < totalSHAPES; i++)
        {
            glBufferSubData(GL_ARRAY_BUFFER, InstanceProps.bufferGAPs[i], MESS[i].sizeInstanceinBYTES(), MESS[i].InstanceData.data());
        }

        // Set up vertex attributes
        for (size_t i = 0; i < totalSHAPES; i++) {

            glBindVertexArray(ObjectArraysID[i]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexedBufferID);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX), (void*)(vertProps.bufferGAPs[i] + offsetof(VERTEX, POS)));

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX), (void*)(vertProps.bufferGAPs[i] + offsetof(VERTEX, COLOR)));

            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX), (void*)(vertProps.bufferGAPs[i] + offsetof(VERTEX, NORMAL)));

            glBindBuffer(GL_ARRAY_BUFFER, instancedBufferID);

            for (int j = 3; j <= 6; j++) {
                glEnableVertexAttribArray(j);
                glVertexAttribPointer(j, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(InstanceProps.bufferGAPs[i] + ((j - 2) * sizeof(glm::vec4))));
                glVertexAttribDivisor(j, 1);
            }

        }

        glBindVertexArray(0);
}


//send first color for entire instance
void Engine::colorDivisor()
{
	glVertexAttribDivisor(1, 1);

}


/*
translation, rotataion and scaling dynamically
LIMITATION :saare instance of that object will get updated even when change is only wanted on one instaneces*/
void Engine::UpdateSINGLEInstancesINGPU(int orderofOBJECT,int orderofINSTANCES , std::vector <shapeDATA> & MESS , glm::mat4& upd)
{
    if (orderofOBJECT > MESS.size() || orderofINSTANCES > MESS[orderofOBJECT].InstanceData.size()) {
        std::cout << "Logic error : Objects  OR Instances are less than u provided\n";
        return ;
    }
    MESS[orderofOBJECT].InstanceData[orderofINSTANCES] = upd;
    glBindVertexArray(ObjectArraysID[orderofOBJECT]);
    glBufferSubData(GL_ARRAY_BUFFER, InstanceProps.bufferGAPs[orderofOBJECT] + (orderofINSTANCES * sizeof(glm::mat4)), sizeof(glm::mat4), glm::value_ptr(MESS[orderofOBJECT].InstanceData[orderofINSTANCES]));

}



void Engine::renderVertArray(std::vector <shapeDATA>& MESS)
{
	for (int i = 0; i < totalSHAPES; i++) {
	    glBindVertexArray(ObjectArraysID[i]);
        glDrawElementsInstanced(GL_TRIANGLES, renderIndexforeachShape[i], GL_UNSIGNED_INT, (void*)indexProps.bufferGAPs[i], MESS[i].InstanceData.size());
        //drawarray sirf vertecis data ko draw karta hai but agar elemnt specify kiya tab gpu indexed buffer read karke uske vertices draw karta hai
	}
	glBindVertexArray(0);
}




void Engine::TRUNCATE()
{
	
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteBuffers(1, &IndexedBufferID);
	glDeleteBuffers(1, &instancedBufferID);
}



void Engine::DROP()	{

	// Delete buffers before terminating GLFW
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteBuffers(1, &IndexedBufferID);
	glDeleteBuffers(1 ,&instancedBufferID);

	// Delete vertex array
}

