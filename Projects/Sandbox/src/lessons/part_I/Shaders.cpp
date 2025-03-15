#include "Shaders.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Shaders::Shaders()
:Layer("Shaders")
{
}

Shaders::~Shaders()
{
}

void Shaders::OnAttach()
{
    glCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    m_shader = new FRGL::Shader(
        "Projects/Sandbox/src/shaders/part_I/Shaders.v.glsl",
        "Projects/Sandbox/src/shaders/part_I/Shaders.f.glsl"
    );

    glCall(glGenVertexArrays(1, &m_vao));
    glCall(glBindVertexArray(m_vao));

    glCall(glGenBuffers(1, &m_vbo));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (const void *)0));
    glCall(glEnableVertexAttribArray(0));

    glCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (const void *)(sizeof(float)*3)));
    glCall(glEnableVertexAttribArray(1));

    glCall(glBindVertexArray(0));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

}

void Shaders::OnDetach()
{
    delete m_shader;
}

void Shaders::OnStart()
{
    m_shader->SetUniform("uBrightness", 1.0f);
}

void Shaders::OnUpdate(double time)
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_shader->Bind();
    glCall(glBindVertexArray(m_vao));
    glCall(glDrawArrays(GL_TRIANGLES, 0, 3));
    m_shader->UnBind();
    glCall(glBindVertexArray(0));
}