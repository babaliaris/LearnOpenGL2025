#include "TestLesson.h"
#include <iostream>

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
    if (m_printOnUpdateOnce)
    {
        std::cout << "TestLesson::OnUpdate()" << std::endl;
        std::cout << "[TestLesson::OnUpdate()] " << GetTitle() << "(" << GetID() << ")" << std::endl;
        m_printOnUpdateOnce = false;
    }
}