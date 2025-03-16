#include "Textures.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Textures::Textures()
:Layer("Textures")
{
}

Textures::~Textures()
{
}

void Textures::OnAttach()
{
    glCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

    
    float vertices[] = {
        //Positions              //Colors               //Tex Coords
        -0.5f,  -0.5f,  0.0f,    1.0f,  0.0f,  0.0f,    0.0f,  0.0f, //Left Bottom
         0.5f,  -0.5f,  0.0f,    0.0f,  1.0f,  0.0f,    1.0f,  0.0f, //Right Bottom
         0.5f,   0.5f,  0.0f,    0.0f,  0.0f,  1.0f,    1.0f,  1.0f, //Right Up

        -0.5f,   0.5f,  0.0f,    1.0f,  1.0f,  0.0f,    0.0f,  1.0f, //Left Up
        -0.5f,  -0.5f,  0.0f,    1.0f,  0.0f,  0.0f,    0.0f,  0.0f, //Left Bottom
         0.5f,   0.5f,  0.0f,    0.0f,  0.0f,  1.0f,    1.0f,  1.0f  //Right Up
    };

    

    m_shader = new FRGL::Shader(
        "Projects/Sandbox/src/shaders/part_I/Textures.v.glsl",
        "Projects/Sandbox/src/shaders/part_I/Textures.f.glsl"
    );

    m_texture1 = new FRGL::Texture("Projects/Sandbox/assets/textures/container.jpg");
    m_texture2 = new FRGL::Texture("Projects/Sandbox/assets/textures/awesomeface.png");

    glCall(glGenVertexArrays(1, &m_vao));
    glCall(glBindVertexArray(m_vao));

    glCall(glGenBuffers(1, &m_vbo));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)0));
    glCall(glEnableVertexAttribArray(0));

    glCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)(sizeof(float)*3)));
    glCall(glEnableVertexAttribArray(1));

    glCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (const void *)(sizeof(float)*6)));
    glCall(glEnableVertexAttribArray(2));

    glCall(glBindVertexArray(0));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

}

void Textures::OnDetach()
{
    delete m_shader;
    delete m_texture1;
    delete m_texture2;
}

void Textures::OnStart()
{
    m_shader->SetUniform("uContainer", 0);
    m_shader->SetUniform("uSmily", 1);
}

void Textures::OnUpdate(double time)
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_shader->Bind();
    m_texture1->Bind(0);
    m_texture2->Bind(1);
    glCall(glBindVertexArray(m_vao));
    glCall(glDrawArrays(GL_TRIANGLES, 0, 6));
    m_shader->UnBind();
    glCall(glBindVertexArray(0));
}