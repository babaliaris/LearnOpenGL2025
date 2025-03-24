#include "StencilBuffer.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

StencilBuffer::StencilBuffer()
:Layer("Stencil Buffer")
{
}

StencilBuffer::~StencilBuffer()
{
    delete m_shaderContainer;
    delete m_shaderLight;
    delete m_cam;

    glCall(glDeleteBuffers(1, &m_vbo));
    glCall(glDeleteVertexArrays(1, &m_containerVao));
    glCall(glDeleteVertexArrays(1, &m_lightVao));
}

void StencilBuffer::OnAttach()
{
    glCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));


    m_shaderContainer = new FRGL::Shader(
        "Projects/Sandbox/src/shaders/part_IV/StencilBuffer.v.glsl",
        "Projects/Sandbox/src/shaders/part_IV/StencilBuffer.f.glsl"
    );

    m_shaderOutline = new FRGL::Shader(
        "Projects/Sandbox/src/shaders/part_IV/Outline.v.glsl",
        "Projects/Sandbox/src/shaders/part_IV/Outline.f.glsl"
    );

    m_shaderLight = new FRGL::Shader(
        "Projects/Sandbox/src/shaders/light.v.glsl",
        "Projects/Sandbox/src/shaders/light.f.glsl"
    );


    this->InitializeGeometry();
}

void StencilBuffer::OnDetach()
{
}

void StencilBuffer::OnStart()
{
    glCall(glEnable(GL_DEPTH_TEST));
    glCall(glEnable(GL_STENCIL_TEST));

    //Load the textures.
    m_diffuse = new FRGL::Texture("Projects/Sandbox/assets/textures/container_steel_diffuse.png");
    m_specular = new FRGL::Texture("Projects/Sandbox/assets/textures/container_steel_specular.png");

    //Create a camera.
    m_cam = new FRGL::Camera(GetApp(), glm::vec3(0.0f, 0.0f, 3.0f));
    m_cam->SetSpeed(5.0f);

    //Outline fixed uniforms.
    m_shaderOutline->SetUniform("uModel", glm::mat4(1.0f));

    //Container fixed uniforms.
    m_shaderContainer->SetUniform("uModel", glm::mat4(1.0f));
    m_shaderContainer->SetUniform("uNormal", glm::mat3(1.0f));
    m_shaderContainer->SetUniform("uMat.diffuse", 0);
    m_shaderContainer->SetUniform("uMat.specular", 1);
    m_shaderContainer->SetUniform("uMat.shininess", 64);

    //Ambient Light
    m_shaderContainer->SetUniform("uLights[0].isFinal", 0);
    m_shaderContainer->SetUniform("uLights[0].type", 3);
    m_shaderContainer->SetUniform("uLights[0].color", glm::vec3(1.0f, 1.0f, 1.0f));
    m_shaderContainer->SetUniform("uLights[0].strength", 0.2f);

    //Point Light.
    m_shaderContainer->SetUniform("uLights[1].isFinal", 0);
    m_shaderContainer->SetUniform("uLights[1].type", 1);
    m_shaderContainer->SetUniform("uLights[1].position", m_lightPos);
    m_shaderContainer->SetUniform("uLights[1].color", glm::vec3(1.0f, 1.0f, 1.0f));
    m_shaderContainer->SetUniform("uLights[1].strength", 1.0f);
    m_shaderContainer->SetUniform("uLights[1].kc", 1.0f);
    m_shaderContainer->SetUniform("uLights[1].kl", 0.1f);
    m_shaderContainer->SetUniform("uLights[1].kq", 0.03f);

    //Spot Light.
    m_shaderContainer->SetUniform("uLights[2].isFinal", 1);
    m_shaderContainer->SetUniform("uLights[2].type", 2);
    m_shaderContainer->SetUniform("uLights[2].color", glm::vec3(1.0f, 1.0f, 1.0f));
    m_shaderContainer->SetUniform("uLights[2].strength", 1.0f);
    m_shaderContainer->SetUniform("uLights[2].spotInner", glm::cos(glm::radians(12.0f)));
    m_shaderContainer->SetUniform("uLights[2].spotOuter",  glm::cos(glm::radians(17.0f)));
    m_shaderContainer->SetUniform("uLights[2].kc", 1.0f);
    m_shaderContainer->SetUniform("uLights[2].kl", 0.1f);
    m_shaderContainer->SetUniform("uLights[2].kq", 0.03f);

    //Light model matrix/uniform.
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, m_lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(0.2f, 0.2f, 0.2f));
    m_shaderLight->SetUniform("uModel", lightModel);
}

void StencilBuffer::OnUpdate(double time)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //Camera movement.
    m_cam->Move(FRGL::CameraModeE::KEYBOARD_MOUSE);

    //Calculate the projection matrix.
    glm::mat4 proj = glm::perspective(
        glm::radians(45.0f),
        (float)GetApp()->GetWindow()->GetWidth() / GetApp()->GetWindow()->GetHeight(),
        01.f, 100.0f
    );

    //Set container's uniforms.
    m_shaderContainer->SetUniform("uView", m_cam->GetProj());
    m_shaderContainer->SetUniform("uProj", proj);
    m_shaderContainer->SetUniform("uCamPos", m_cam->GetPos());
    m_shaderContainer->SetUniform("uLights[2].direction", m_cam->getDir());
    m_shaderContainer->SetUniform("uLights[2].position", m_cam->GetPos());
    
    //Set light's uniforms.
    m_shaderLight->SetUniform("uView", m_cam->GetProj());
    m_shaderLight->SetUniform("uProj", proj);

    //Set Outline uniforms.
    m_shaderOutline->SetUniform("uView", m_cam->GetProj());
    m_shaderOutline->SetUniform("uProj", proj);

    glCall(glStencilMask(0xFF)); //Enable Stencil Writing.
    glCall(glStencilFunc(GL_ALWAYS, 1, 0xFF));
    glCall(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));

    //Draw the Container here!
    m_shaderContainer->Bind();
    m_diffuse->Bind(0);
    m_specular->Bind(1);
    glCall(glBindVertexArray(m_containerVao));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_shaderContainer->UnBind();
    glCall(glBindVertexArray(0));
    m_diffuse->Unbind();
    m_specular->Unbind();

    glCall(glStencilMask(0x00)); //Disable Stencil Writing.
    glCall(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
    glCall(glDisable(GL_DEPTH_TEST));

    //Draw it Again, scaled and using the Outline shader!
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
    m_shaderOutline->SetUniform("uModel", model);
    m_shaderOutline->Bind();
    glCall(glBindVertexArray(m_containerVao));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_shaderOutline->UnBind();
    glCall(glBindVertexArray(0));

    glCall(glStencilMask(0xFF)); //Enable Stencil Writing (So it can be cleared).
    glCall(glEnable(GL_DEPTH_TEST)); //Enable Depth Test.

    //Draw the light.
    m_shaderLight->Bind();
    glCall(glBindVertexArray(m_lightVao));
    glCall(glDrawArrays(GL_TRIANGLES, 0, 36));
    m_shaderLight->UnBind();
    glCall(glBindVertexArray(0));
}



void StencilBuffer::InitializeGeometry()
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

    //Create the vertex buffer and upload the data.
    glCall(glGenBuffers(1, &m_vbo));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(containerVertices), containerVertices, GL_STATIC_DRAW));

    
    //===================Container VAO and Vertex Atrributes Set-Up===================//

    //Create and bind the containers VAO.
    glCall(glGenVertexArrays(1, &m_containerVao));
    glCall(glBindVertexArray(m_containerVao));

    //Positions
    glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)0));
    glCall(glEnableVertexAttribArray(0));

    //Normals
    glCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)(sizeof(float)*3)));
    glCall(glEnableVertexAttribArray(1));

    //Texture Coordinates (UVs).
    glCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)(sizeof(float)*6)));
    glCall(glEnableVertexAttribArray(2));
    //===================Container VAO and Vertex Atrributes Set-Up===================//


    //===================Light VAO and Vertex Atrributes Set-Up===================//

    //Create and bind the light's VAO.
    glCall(glGenVertexArrays(1, &m_lightVao));
    glCall(glBindVertexArray(m_lightVao));

    //Positions.
    glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)0));
    glCall(glEnableVertexAttribArray(0));

    glCall(glBindVertexArray(0));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    //===================Light VAO and Vertex Atrributes Set-Up===================//
}
