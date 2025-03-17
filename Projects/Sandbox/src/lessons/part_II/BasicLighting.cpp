#include "BasicLighting.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

BasicLighting::BasicLighting()
:Layer("BasicLighting")
{
    this->InitializeVertices();
}

BasicLighting::~BasicLighting()
{
}

void BasicLighting::OnAttach()
{
    glCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));


    m_shaderContainer = new FRGL::Shader(
        "Projects/Sandbox/src/shaders/part_II/BasicLighting.v.glsl",
        "Projects/Sandbox/src/shaders/part_II/BasicLighting.f.glsl"
    );

    m_textureContainer = new FRGL::Texture("Projects/Sandbox/assets/textures/container.jpg");

    glCall(glGenVertexArrays(1, &m_containerVao));
    glCall(glBindVertexArray(m_containerVao));

    glCall(glGenBuffers(1, &m_containerVbo));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_containerVbo));
    glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(m_containerVertices), m_containerVertices, GL_STATIC_DRAW));

    glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void *)0));
    glCall(glEnableVertexAttribArray(0));

    glCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void *)(sizeof(float)*3)));
    glCall(glEnableVertexAttribArray(1));

    glCall(glBindVertexArray(0));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

    m_shaderLight = new FRGL::Shader(
        "Projects/Sandbox/src/shaders/light.v.glsl",
        "Projects/Sandbox/src/shaders/light.f.glsl"
    );

    glCall(glGenVertexArrays(1, &m_lightVao));
    glCall(glBindVertexArray(m_lightVao));

    glCall(glGenBuffers(1, &m_lightVbo));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_lightVbo));
    glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(m_lightVertices), m_lightVertices, GL_STATIC_DRAW));

    glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void *)0));
    glCall(glEnableVertexAttribArray(0));

    glCall(glBindVertexArray(0));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

}

void BasicLighting::OnDetach()
{
    delete m_shaderContainer;
    delete m_shaderLight;
    delete m_textureContainer;
    delete m_cam;
}

void BasicLighting::OnStart()
{
    glCall(glEnable(GL_DEPTH_TEST));

    //Disable the cursor.
    glfwSetInputMode(GetApp()->GetWindow()->GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Create a camera.
    m_cam = new FRGL::Camera(GetApp(), glm::vec3(0.0f, 0.0f, 3.0f));
    m_cam->SetSpeed(5.0f);

    //Container fixed uniforms.
    m_shaderContainer->SetUniform("uContainer", 0);
    m_shaderContainer->SetUniform("uLightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    m_shaderContainer->SetUniform("uModel", glm::mat4(1.0f));

    //Light model matrix/uniform.
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, m_lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(0.2f, 0.2f, 0.2f));
    m_shaderLight->SetUniform("uModel", lightModel);
}

void BasicLighting::OnUpdate(double time)
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
    m_shaderContainer->SetUniform("uProj", proj);
    m_shaderLight->SetUniform("uProj", proj);
    
    //Set light's uniforms.
    m_shaderContainer->SetUniform("uView", m_cam->GetProj());
    m_shaderLight->SetUniform("uView", m_cam->GetProj());

    //Draw the container.
    m_textureContainer->Bind(0);
    m_shaderContainer->Bind();
    glCall(glBindVertexArray(m_containerVao));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_textureContainer->Unbind();
    m_shaderContainer->UnBind();
    glCall(glBindVertexArray(0));

    //Draw the light.
    m_shaderLight->Bind();
    glCall(glBindVertexArray(m_lightVao));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_shaderLight->UnBind();
    glCall(glBindVertexArray(0));
}



void BasicLighting::InitializeVertices()
{
   //Create the container.
   float containerVertices[] = {
    //Positions           TexCoords.
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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


    for (unsigned int i = 0; i < 5*36; i++)
    {
        m_containerVertices[i] = containerVertices[i];
    }


    for (unsigned int i = 0; i < 3*36; i++)
    {
        m_lightVertices[i] = lightVertices[i];
    }
}
