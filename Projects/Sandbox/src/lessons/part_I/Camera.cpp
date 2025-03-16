#include "Camera.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

CameraLesson::CameraLesson()
:Layer("CameraLesson")
{
    m_cam.SetSpeed(5.0f);

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

CameraLesson::~CameraLesson()
{
}

void CameraLesson::OnAttach()
{
    glCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

    float vertices[] = {
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

    

    m_shader = new FRGL::Shader(
        "Projects/Sandbox/src/shaders/part_I/Camera.v.glsl",
        "Projects/Sandbox/src/shaders/part_I/Camera.f.glsl"
    );

    m_texture1 = new FRGL::Texture("Projects/Sandbox/assets/textures/container.jpg");
    m_texture2 = new FRGL::Texture("Projects/Sandbox/assets/textures/awesomeface.png");

    glCall(glGenVertexArrays(1, &m_vao));
    glCall(glBindVertexArray(m_vao));

    glCall(glGenBuffers(1, &m_vbo));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    glCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void *)0));
    glCall(glEnableVertexAttribArray(0));

    glCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void *)(sizeof(float)*3)));
    glCall(glEnableVertexAttribArray(1));

    glCall(glBindVertexArray(0));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

}

void CameraLesson::OnDetach()
{
    delete m_shader;
    delete m_texture1;
    delete m_texture2;
}

void CameraLesson::OnStart()
{
    glCall(glEnable(GL_DEPTH_TEST));

    m_shader->SetUniform("uContainer", 0);
    m_shader->SetUniform("uSmily", 1);
}

void CameraLesson::OnUpdate(double time)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->MoveCamera();

    m_shader->SetUniform("uProj", glm::perspective(
        glm::radians(45.0f),
        (float)GetApp()->GetWindow()->GetWidth() / GetApp()->GetWindow()->GetHeight(),
        01.f, 100.0f)
    );

    m_shader->SetUniform("uView", m_cam.GetProj());

    for(unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, m_cubePositions[i]);

        float angle = 20.0f * i; 

        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

        m_shader->SetUniform("uModel", model);

        m_texture1->Bind(0);
        m_texture2->Bind(1);
        m_shader->Bind();
        glCall(glBindVertexArray(m_vao));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}



void CameraLesson::MoveCamera()
{
    if (glfwGetKey(GetApp()->GetWindow()->GetGLFWwindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
        m_cam.Move(FRGL::CameraModeE::KEYBOARD, FRGL::CameraMoveE::LEFT, GetApp()->GetDeltaTime());

    else if (glfwGetKey(GetApp()->GetWindow()->GetGLFWwindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
        m_cam.Move(FRGL::CameraModeE::KEYBOARD, FRGL::CameraMoveE::RIGHT, GetApp()->GetDeltaTime());

    if (glfwGetKey(GetApp()->GetWindow()->GetGLFWwindow(), GLFW_KEY_UP) == GLFW_PRESS)
        m_cam.Move(FRGL::CameraModeE::KEYBOARD, FRGL::CameraMoveE::UP, GetApp()->GetDeltaTime());

    else if (glfwGetKey(GetApp()->GetWindow()->GetGLFWwindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
        m_cam.Move(FRGL::CameraModeE::KEYBOARD, FRGL::CameraMoveE::DOWN, GetApp()->GetDeltaTime());

    if (glfwGetKey(GetApp()->GetWindow()->GetGLFWwindow(), GLFW_KEY_W) == GLFW_PRESS)
        m_cam.Move(FRGL::CameraModeE::KEYBOARD, FRGL::CameraMoveE::FORWARD, GetApp()->GetDeltaTime());

    else if (glfwGetKey(GetApp()->GetWindow()->GetGLFWwindow(), GLFW_KEY_S) == GLFW_PRESS)
        m_cam.Move(FRGL::CameraModeE::KEYBOARD, FRGL::CameraMoveE::BACKWARD, GetApp()->GetDeltaTime());

    if (glfwGetKey(GetApp()->GetWindow()->GetGLFWwindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        m_cam.SetSpeed(10.0f);

    else if (glfwGetKey(GetApp()->GetWindow()->GetGLFWwindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        m_cam.SetSpeed(5.0f);
}