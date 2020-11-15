
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

#include "Sphere.h"

using namespace std;

const float toRadians = 3.14159266f / 180.0f;

Window mainWindow;
std::vector<Shader> shaderList;
Camera camera;

Mesh* mesh;

Texture brickTexture;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

Sphere sphere;

static const char* vShader = "data/Shaders/shader.vsh";
static const char* fShader = "data/Shaders/shader.fsh";

void CreateShaders()
{
    Shader *shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

void CreateObjects()
{
    std::vector<unsigned int> indicesVector = sphere.getIndices();
    std::vector<GLfloat> verticesVector = sphere.getVertices();
    std::vector<GLfloat> texCoordVector = sphere.getTexCoords();

    uint totalVerticesSize = verticesVector.size() + texCoordVector.size();
    vector<GLfloat> totalVertices;

    uint m =0 , n = 0, k = 0;
    // vertices, texture
        for(unsigned int i = 0; i < totalVerticesSize; i++){
            if(k<=2) // 0, 1, 2,
            {
                totalVertices.push_back(verticesVector.at(m)); m++;
            }
            else{
                totalVertices.push_back(texCoordVector.at(n)); n++;
            }
            k++; if(k==5) k=0;
        } //*/



    // vertices, texture, normals
/*    for(unsigned int i = 0; i < totalVerticesSize; i++){
        if(k<=2) // 0, 1, 2,
        {
            verticesVector = verticesVector.at(m); m++;
            //vertices[i+]
        }

        //if((k>=3)&&(k<=4)) // 3, 4,
        if((k>=3)&&(k<=5)) // 3, 4, 5,
        {
            //vertices[i] = texCoordVector.at(n); n++;
            vertices[i] = normalsVector.at(l); l++;
        }

        //if(k>=5) // 5, 6,
        if(k>=6) // 6, 7
        {
            //vertices[i] = normalsVector.at(l); l++;
            vertices[i] = texCoordVector.at(n); n++;
        }

        k++;
        if(k==8) k=0;
    }//*/

/*    // for debug purpose
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    unsigned int verticesSize = 12;
    unsigned int indicesSize = 12;//*/

    mesh = new Mesh();
    mesh->CreateMesh(&totalVertices[0], &indicesVector[0], totalVertices.size(), indicesVector.size());
    /*mesh->CreateMeshNew(
            &verticesVector[0], verticesVector.size(),
            &texCoordVector[0], texCoordVector.size(),
            &indicesVector[0], indicesVector.size()
            ); //*/
}

int main()
{
    mainWindow = Window(1920, 1080);
    mainWindow.Initialise();

    sphere.set(10.0f, 50, 50);
    sphere.printSelf();

    CreateObjects();
    CreateShaders();

    camera = Camera(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

    //brickTexture = Texture("data/Textures/brick.png");
    //brickTexture = Texture("data/Textures/earth2048.png");
    brickTexture = Texture("data/Textures/4_no_ice_clouds_mts_16k.png");
    brickTexture.LoadTexture();


    GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

    // Loop until window closed
    while (!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime();        deltaTime = now - lastTime;        lastTime = now;
        // Get + Handle User Input
        glfwPollEvents();        camera.keyControl(mainWindow.getsKeys(), deltaTime);        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

        // Clear the window
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        uniformView = shaderList[0].GetViewLocation();

        glm::mat4 model(1.0f);
        model = glm::rotate(model, 45*toRadians, glm::vec3(0.0f,1.0f,0.0f)); // rotate in front of view
        model = glm::rotate(model, 90*toRadians, glm::vec3(1.0f,0.0f,0.0f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        brickTexture.UseTexture();
        mesh->RenderMesh();

        glUseProgram(0);

        if(camera.toggle_cursor){mainWindow.toggleCursor();}

        mainWindow.swapBuffers();
    }

    return 0;
}
