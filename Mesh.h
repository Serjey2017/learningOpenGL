#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

class Mesh
{
public:
    Mesh();
    ~Mesh();

    void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
    void RenderMesh();
    void ClearMesh();
    void CreateMeshNew(GLfloat *vertices, unsigned int numOfVertices,
                       GLfloat *textures, unsigned int numTexCoord,
                       unsigned int *indices, unsigned int numOfIndices);

private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
    GLuint vbo_cube_vertices, vbo_cube_texcoords;
};

#endif // MESH_H
