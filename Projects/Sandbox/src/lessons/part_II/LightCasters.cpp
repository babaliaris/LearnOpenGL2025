#include "LightCasters.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

LightCasters::LightCasters()
:Layer("LightCasters")
{
    m_cubePositions[0] = glm::vec3( 0.0f,  0.0f,  0.0f);
    m_cubePositions[1] = glm::vec3( 2.0f,  5.0f, -15.0f);
    m_cubePositions[2] = glm::vec3(-1.5f, -2.2f, -2.5f);
    m_cubePositions[3] = glm::vec3(-3.8f, -2.0f, -12.3f);
    m_cubePositions[4] = glm::vec3( 2.4f, -0.4f, -3.5f);
    m_cubePositions[5] = glm::vec3(-1.7f,  3.0f, -7.5f);
    m_cubePositions[6] = glm::vec3( 1.3f, -2.0f, -2.5f);
    m_cubePositions[7] = glm::vec3( 1.5f,  2.0f, -2.5f);
    m_cubePositions[8] = glm::vec3( 1.5f,  0.2f, -1.5f);
    m_cubePositions[9] = glm::vec3(-1.3f,  1.0f, -1.5f);
}

LightCasters::~LightCasters()
{
}

void LightCasters::OnAttach()
{
    glCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));


    m_shaderContainer = new FRGL::Shader(
        "Projects/Sandbox/src/shaders/part_II/LightCasters.v.glsl",
        "Projects/Sandbox/src/shaders/part_II/LightCasters.f.glsl"
    );

    m_shaderLight = new FRGL::Shader(
        "Projects/Sandbox/src/shaders/light.v.glsl",
        "Projects/Sandbox/src/shaders/light.f.glsl"
    );

    m_containerDiffuse = new FRGL::Texture("Projects/Sandbox/assets/textures/container_steel_diffuse.png");
    m_containerSpecular = new FRGL::Texture("Projects/Sandbox/assets/textures/container_steel_specular.png");

    this->InitializeGeometry();
}

void LightCasters::OnDetach()
{
    delete m_shaderContainer;
    delete m_shaderLight;
    delete m_containerDiffuse;
    delete m_containerSpecular;
    delete m_cam;
}

void LightCasters::OnStart()
{
    glCall(glEnable(GL_DEPTH_TEST));

    //Disable the cursor.
    glfwSetInputMode(GetApp()->GetWindow()->GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Create a camera.
    m_cam = new FRGL::Camera(GetApp(), glm::vec3(0.0f, 0.0f, 3.0f));
    m_cam->SetSpeed(5.0f);

    //0=Directional Light, 1=Point Light, 2=Spot Light.
    m_shaderContainer->SetUniform("uChooseLight", 1);;

    //Container fixed uniforms.
    m_shaderContainer->SetUniform("uMat.diffuse", 0);
    m_shaderContainer->SetUniform("uMat.specular", 1);
    m_shaderContainer->SetUniform("uMat.shininess", 32);
    m_shaderContainer->SetUniform("uModel", glm::mat4(1.0f));
    m_shaderContainer->SetUniform("uNormal", glm::mat3(1.0f));

    //Ambient Light
    m_shaderContainer->SetUniform("uAmbient.color", glm::vec3(1.0f, 1.0f, 1.0f));
    m_shaderContainer->SetUniform("uAmbient.strength", 0.2f);

    //Spot Light.
    m_shaderContainer->SetUniform("uPointLight.pos", m_lightPos);
    m_shaderContainer->SetUniform("uPointLight.color", glm::vec3(1.0f, 1.0f, 1.0f));
    m_shaderContainer->SetUniform("uPointLight.strength", 1.0f);
    m_shaderContainer->SetUniform("uPointLight.kc", 1.0f);
    m_shaderContainer->SetUniform("uPointLight.kl", 0.1f);
    m_shaderContainer->SetUniform("uPointLight.kq", 0.03f);

    //Light model matrix/uniform.
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, m_lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(0.2f, 0.2f, 0.2f));
    m_shaderLight->SetUniform("uModel", lightModel);
}

void LightCasters::OnUpdate(double time)
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
    m_shaderContainer->SetUniform("uView", m_cam->GetProj());
    m_shaderContainer->SetUniform("uProj", proj);
    m_shaderContainer->SetUniform("uCamPos", m_cam->GetPos());
    
    //Set light's uniforms.
    m_shaderLight->SetUniform("uView", m_cam->GetProj());
    m_shaderLight->SetUniform("uProj", proj);

    //Draw the container multiple times in different positions.
    for(unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, m_cubePositions[i]);

        float angle = 20.0f * i; 

        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        m_shaderContainer->SetUniform("uModel", model);
        m_shaderContainer->SetUniform("uNormal", glm::transpose(glm::inverse(glm::mat3(model))) );

        //Draw the container.
        m_containerDiffuse->Bind(0);
        m_containerSpecular->Bind(1);
        m_shaderContainer->Bind();
        glCall(glBindVertexArray(m_containerVao));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        m_containerDiffuse->Unbind();
        m_containerSpecular->Unbind();
        m_shaderContainer->UnBind();
        glCall(glBindVertexArray(0));
    }

    //Draw the light.
    m_shaderLight->Bind();
    glCall(glBindVertexArray(m_lightVao));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    m_shaderLight->UnBind();
    glCall(glBindVertexArray(0));
}



void LightCasters::InitializeGeometry()
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
