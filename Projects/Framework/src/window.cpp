#include <FRGL/window.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace FRGL
{
    void WindowSizeCB(GLFWwindow* window, int width, int height);


    Window::Window(int width, int height, const std::string &title):
    m_width(width), m_height(height), m_numOfMonitors(0), m_title(title),
    m_window(NULL)
    {
        if (glfwInit() == GLFW_FALSE)
        {
            std::cout << "GLFW failed to be initialized..." << std::endl;
            return;
        }

        m_monitors= glfwGetMonitors(&m_numOfMonitors);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (!m_window)
        {
            std::cout << "GLFW failed to create the window..." << std::endl;
            glfwTerminate();
            return;
        }

        std::cout << "[GLFW] Window created using the default monitor. #Monitors = " << m_numOfMonitors << std::endl;

        glfwMakeContextCurrent(m_window);

        if (GLenum glew_error = glewInit() != GLEW_OK)
        {
            std::cout << "GLEW failed to be initialized: " << glewGetErrorString(glew_error) << std::endl;
            glfwTerminate();
            return;
        }

        glViewport(0, 0, width, height);

        glfwSetWindowUserPointer(m_window, this);

        glfwSetWindowSizeCallback(m_window, WindowSizeCB);
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    void Window::Update()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    bool Window::IsRunning()
    {
        return !glfwWindowShouldClose(m_window);
    }

    double Window::GetTime()
    {
        return glfwGetTime();
    }

    void WindowSizeCB(GLFWwindow* window, int width, int height)
    {
        FRGL::Window *w = (FRGL::Window *)glfwGetWindowUserPointer(window);

        w->m_width = width;
        w->m_height = height;

        glViewport(0, 0, width, height);

        std::cout << "[Window::WindowSizeCB] Window Resized (" << width << " , " << height << ")" << std::endl;
    }
}