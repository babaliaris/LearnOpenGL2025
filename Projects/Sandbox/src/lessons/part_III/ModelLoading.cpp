#include "ModelLoading.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

ModelLoading::ModelLoading()
:Layer("ModelLoading")
{
}

ModelLoading::~ModelLoading()
{
    delete m_model;
    delete m_shaderModel;
    delete m_shaderLight;
    delete m_cam;
}

void ModelLoading::OnAttach()
{
    glCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));


    m_shaderModel = new FRGL::Shader(
        "Projects/Sandbox/src/shaders/part_III/ModelLoading.v.glsl",
        "Projects/Sandbox/src/shaders/part_III/ModelLoading.f.glsl"
    );

    m_shaderLight = new FRGL::Shader(
        "Projects/Sandbox/src/shaders/light.v.glsl",
        "Projects/Sandbox/src/shaders/light.f.glsl"
    );

    this->InitializeGeometry();
}

void ModelLoading::OnDetach()
{
}

void ModelLoading::OnStart()
{
    glCall(glEnable(GL_DEPTH_TEST));

    //Disable the cursor.
    glfwSetInputMode(GetApp()->GetWindow()->GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Load the model.
    m_model = new FRGL::Model("Projects/Sandbox/assets/models/backpack/backpack.obj");

    //Create a camera.
    m_cam = new FRGL::Camera(GetApp(), glm::vec3(0.0f, 0.0f, 3.0f));
    m_cam->SetSpeed(5.0f);

    //Container fixed uniforms.
    m_shaderModel->SetUniform("uModel", glm::mat4(1.0f));
    m_shaderModel->SetUniform("uNormal", glm::mat3(1.0f));

    //Ambient Light
    m_shaderModel->SetUniform("uLights[0].isFinal", 0);
    m_shaderModel->SetUniform("uLights[0].type", 3);
    m_shaderModel->SetUniform("uLights[0].color", glm::vec3(1.0f, 1.0f, 1.0f));
    m_shaderModel->SetUniform("uLights[0].strength", 0.2f);

    //Point Light.
    m_shaderModel->SetUniform("uLights[1].isFinal", 0);
    m_shaderModel->SetUniform("uLights[1].type", 1);
    m_shaderModel->SetUniform("uLights[1].position", m_lightPos);
    m_shaderModel->SetUniform("uLights[1].color", glm::vec3(1.0f, 1.0f, 1.0f));
    m_shaderModel->SetUniform("uLights[1].strength", 1.0f);
    m_shaderModel->SetUniform("uLights[1].kc", 1.0f);
    m_shaderModel->SetUniform("uLights[1].kl", 0.1f);
    m_shaderModel->SetUniform("uLights[1].kq", 0.03f);

    //Spot Light.
    m_shaderModel->SetUniform("uLights[2].isFinal", 1);
    m_shaderModel->SetUniform("uLights[2].type", 2);
    m_shaderModel->SetUniform("uLights[2].color", glm::vec3(1.0f, 1.0f, 1.0f));
    m_shaderModel->SetUniform("uLights[2].strength", 1.0f);
    m_shaderModel->SetUniform("uLights[2].spotInner", glm::cos(glm::radians(12.0f)));
    m_shaderModel->SetUniform("uLights[2].spotOuter",  glm::cos(glm::radians(17.0f)));
    m_shaderModel->SetUniform("uLights[2].kc", 1.0f);
    m_shaderModel->SetUniform("uLights[2].kl", 0.1f);
    m_shaderModel->SetUniform("uLights[2].kq", 0.03f);

    //Light model matrix/uniform.
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, m_lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(0.2f, 0.2f, 0.2f));
    m_shaderLight->SetUniform("uModel", lightModel);
}

void ModelLoading::OnUpdate(double time)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Camera movement.
    m_cam->Move(FRGL::CameraModeE::KEYBOARD_MOUSE);

    //Calculate the projection matrix.
    glm::mat4 proj = glm::perspective(
        glm::radians(45.0f),
        (float)GetApp()->GetWindow()->GetWidth() / GetApp()->GetWindow()->GetHeight(),
        01.f, 100.0f
    );

    //Set container's uniforms.
    m_shaderModel->SetUniform("uView", m_cam->GetProj());
    m_shaderModel->SetUniform("uProj", proj);
    m_shaderModel->SetUniform("uCamPos", m_cam->GetPos());
    m_shaderModel->SetUniform("uLights[2].direction", m_cam->getDir());
    m_shaderModel->SetUniform("uLights[2].position", m_cam->GetPos());
    
    //Set light's uniforms.
    m_shaderLight->SetUniform("uView", m_cam->GetProj());
    m_shaderLight->SetUniform("uProj", proj);

    //Draw the Model here!
    m_model->Draw(m_shaderModel);

    //Draw the light.
    m_shaderLight->Bind();
    glCall(glBindVertexArray(m_lightVao));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_shaderLight->UnBind();
    glCall(glBindVertexArray(0));
}



void ModelLoading::InitializeGeometry()
{
   //Create the container.
    float containerVertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };



    //Create the light.
    float lightVertices[] = {
        //Positions
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f, 
        0.5f,  0.5f, -0.5f, 
        0.5f,  0.5f, -0.5f, 
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f, 
        0.5f,  0.5f, -0.5f, 
        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f, 

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f, 
        0.5f, -0.5f,  0.5f, 
        0.5f, -0.5f,  0.5f, 
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f, 
        0.5f,  0.5f,  0.5f, 
        0.5f,  0.5f,  0.5f, 
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };


    /*
    glCall(glGenVertexArrays(1, &m_containerVao));
    glCall(glBindVertexArray(m_containerVao));

    glCall(glGenBuffers(1, &m_containerVbo));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_containerVbo));
    glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(containerVertices), containerVertices, GL_STATIC_DRAW));

    //Positions
    glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)0));
    glCall(glEnableVertexAttribArray(0));

    //Normals
    glCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)(sizeof(float)*3)));
    glCall(glEnableVertexAttribArray(1));

    //Texture Coordinates (UVs).
    glCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)(sizeof(float)*6)));
    glCall(glEnableVertexAttribArray(2));

    glCall(glBindVertexArray(0));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    */


    //Light Cube Draw Data Preperation.
    glCall(glGenVertexArrays(1, &m_lightVao));
    glCall(glBindVertexArray(m_lightVao));

    glCall(glGenBuffers(1, &m_lightVbo));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_lightVbo));
    glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(lightVertices), lightVertices, GL_STATIC_DRAW));

    glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void *)0));
    glCall(glEnableVertexAttribArray(0));

    glCall(glBindVertexArray(0));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
