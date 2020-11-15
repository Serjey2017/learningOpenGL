
#include <iostream>
#include <iomanip>
#include <cmath>
#include "Sphere.h"

Sphere::Sphere(){}

void Sphere::set(float radius, int sectors, int stacks)
{
    this->radius = radius;
    this->sectorCount = sectors;
    if(sectors < MIN_SECTOR_COUNT)
        this->sectorCount = MIN_SECTOR_COUNT;
    this->stackCount = stacks;
    if(sectors < MIN_STACK_COUNT)
        this->sectorCount = MIN_STACK_COUNT;
        buildVerticesSmooth();
}

std::vector<GLfloat> Sphere::getVertices(){
    return vertices;
}
std::vector<unsigned int> Sphere::getIndices(){
    return indices;
}
std::vector<GLfloat> Sphere::getNormals(){
    return normals;
}
std::vector<GLfloat> Sphere::getTexCoords(){
    return texCoords;
}

void Sphere::printSelf() const
{

    auto getIndexCount = (unsigned int)indices.size();
    auto getTriangleCount = getIndexCount / 3;
    auto getVertexCount = (unsigned int)vertices.size() / 3;
    auto getNormalCount = (unsigned int)normals.size() / 3;
    auto getTexCoordCount = (unsigned int)texCoords.size() / 2;
    std::cout << "===== Sphere =====\n"
              << "        Radius: " << radius << "\n"
              << "  Sector Count: " << sectorCount << "\n"
              << "   Stack Count: " << stackCount << "\n"
              << "Smooth Shading: " << "true"  << "\n"
              << "Triangle Count: " << getTriangleCount << "\n"
              << "   Index Count: " << getIndexCount << "\n"
              << "  Vertex Count: " << getVertexCount << "\n"
              << "  Normal Count: " << getNormalCount << "\n"
              << "TexCoord Count: " << getTexCoordCount << std::endl;
}

void Sphere::clearArrays()
{
    std::vector<GLfloat>().swap(vertices);
    std::vector<GLfloat>().swap(normals);
    std::vector<GLfloat>().swap(texCoords);
    std::vector<unsigned int>().swap(indices);
}


void Sphere::buildVerticesSmooth()
{
    // clear memory of prev arrays
    clearArrays();

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // normal
    float s, t;                                     // texCoord

    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;

    for(int i = 0; i <= stackCount; ++i)
    {
        stackAngle = M_PI / 2 - i * stackStep;        // starting from M_PI/2 to -M_PI/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for(int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2M_PI

            // vertex position
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            addVertex(x, y, z);

            // normalized vertex normal
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            addNormal(nx, ny, nz);

            // vertex tex coord between [0, 1]
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            addTexCoord(-s, -t);
        }
    }

    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned int k1, k2;
    for(int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if(i != 0)
            {
                addIndices(k1, k2, k1+1);   // k1---k2---k1+1
            }

            if(i != (stackCount-1))
            {
                addIndices(k1+1, k2, k2+1); // k1+1---k2---k2+1
            }
        }
    }
}

void Sphere::addVertex(float x, float y, float z)
{
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
}

void Sphere::addNormal(float nx, float ny, float nz)
{
    normals.push_back(nx);
    normals.push_back(ny);
    normals.push_back(nz);
}

void Sphere::addTexCoord(float s, float t)
{
    texCoords.push_back(s);
    texCoords.push_back(t);
}

void Sphere::addIndices(unsigned int i1, unsigned int i2, unsigned int i3)
{
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);
}
