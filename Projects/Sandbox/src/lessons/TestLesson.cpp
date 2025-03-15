#include "TestLesson.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

TestLesson::TestLesson()
:Layer("TestLesson"), m_printOnUpdateOnce(true)
{
    std::cout << "TestLesson::TestLesson()" << std::endl;
}

TestLesson::~TestLesson()
{
    std::cout << "TestLesson::~TestLesson()" << std::endl;
}

void TestLesson::OnAttach()
{
    std::cout << "TestLesson::OnAttach()" << std::endl;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void TestLesson::OnDetach()
{
    std::cout << "TestLesson::OnDetach()" << std::endl;
}

void TestLesson::OnStart()
{
    std::cout << "TestLesson::OnStart()" << std::endl;
}

void TestLesson::OnUpdate()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_printOnUpdateOnce)
    {
        std::cout << "TestLesson::OnUpdate()" << std::endl;
        std::cout << "[TestLesson::OnUpdate()] " << GetTitle() << "(" << GetID() << ")" << std::endl;
        m_printOnUpdateOnce = false;
    }

    if (glfwGetKey(GetApp()->GetWindow()->GetGLFWwindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        std::cout << "[" << GetDebug() << "] GLFW_KEY_SPACE" << std::endl;
    }
}