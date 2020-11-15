#include "Mesh.h"

Mesh::Mesh()
{
    VAO = 0;
    VBO = 0;
    IBO = 0;
    indexCount = 0;

    vbo_cube_vertices = 0;
    vbo_cube_texcoords = 0;
}

void Mesh::CreateMeshNew(GLfloat *vertices, unsigned int numOfVertices,
                         GLfloat *textures, unsigned int numTexCoord,
                         unsigned int *indices, unsigned int numOfIndices)
{
    indexCount = numOfIndices;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof (indices[0])*numOfIndices, indices, GL_STATIC_DRAW);

    glGenBuffers(1, &vbo_cube_vertices); // VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof (vertices[0])*numOfVertices, vertices, GL_STATIC_DRAW);

//    glGenBuffers(1, &vbo_cube_texcoords);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_texcoords);
//    glBufferData(GL_ARRAY_BUFFER, sizeof (textures[0])*numTexCoord, textures, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 3, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Mesh::CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices)
{
    indexCount = numOfIndices;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);


//    // only for vertices
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // 0 - first layout, 3 - number of coords, type, ..., 20 bytes,
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, (void*)0);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (void*)12); // shift by 3*4bytes

////    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, 0);
////    glEnableVertexAttribArray(0);
////    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (void*)(12)); // 4x3 +3 -> 4x2 +2
////    glEnableVertexAttribArray(1);
////    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 32, (void*)(20)); // 4x3 +2 ->  4x3 +3 - was texture
////    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Mesh::RenderMesh()
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::ClearMesh()
{
    if (IBO != 0)
    {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }

    if (VBO != 0)
    {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }

    if (VAO != 0)
    {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }

    indexCount = 0;
}


Mesh::~Mesh()
{
    ClearMesh();
}
