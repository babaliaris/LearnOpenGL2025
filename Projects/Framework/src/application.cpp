#include <FRGL/application.h>
#include <iostream>
#include <FRGL/window.h>
#include <GL/glew.h>

namespace FRGL
{
    Application::Application(int width, int height, const std::string &title)
    {
        m_window = new Window(width, height, title);
    }

    Application::~Application()
    {
        delete m_window;
    }

    void Application::Run()
    {
        while (m_window->IsRunning())
        {
            glClear(GL_COLOR_BUFFER_BIT);

            m_window->Update();
        }
    }
}