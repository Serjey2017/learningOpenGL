#ifndef GEOMETRY_SPHERE_H
#define GEOMETRY_SPHERE_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>


const int MIN_SECTOR_COUNT = 3;
const int MIN_STACK_COUNT  = 2;

class Sphere
{
public:
    // ctor/dtor
    Sphere();
    ~Sphere() {}

    // getters/setters
    float getRadius() const                 { return radius; }
    int getSectorCount() const              { return sectorCount; }
    int getStackCount() const               { return stackCount; }
    void set(float radius, int sectorCount, int stackCount);

    std::vector<GLfloat> getVertices();
    std::vector<unsigned int> getIndices();
    std::vector<GLfloat> getNormals();
    std::vector<GLfloat> getTexCoords();

    // debug
    void printSelf() const;

protected:

private:
    // member functions
    void buildVerticesSmooth();
    void clearArrays();
    void addVertex(float x, float y, float z);
    void addNormal(float x, float y, float z);
    void addTexCoord(float s, float t);
    void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);


    // memeber vars
    float radius;
    int sectorCount;                        // longitude, # of slices
    int stackCount;                         // latitude, # of stacks

    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texCoords;
    std::vector<unsigned int> indices;
};

#endif
