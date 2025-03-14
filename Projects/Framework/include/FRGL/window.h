#pragma once
#include <string>

struct GLFWwindow;
struct GLFWmonitor;

namespace FRGL
{
    class Window
    {
        friend class Application;

        public:
        Window(int width, int height, const std::string &title);
        ~Window();

        void Update();
        bool IsRunning();

        inline int GetWidth() const {return m_width;}
        inline int GetHeight() const {return m_height;}
        inline std::string GetTitle() const {return m_title;}
        inline GLFWwindow *GetGLFWwindow() const {return m_window;}

        private:
        int m_width, m_height, m_numOfMonitors;
        std::string m_title;
        GLFWwindow *m_window;
        GLFWmonitor **m_monitors;
    };
}