#pragma once
#include <string>
#include <vector>

namespace FRGL
{
    class Window;

    class Application
    {
        public:
        Application(int width, int height, const std::string &title);
        virtual ~Application();

        void Run();

        private:
        Window *m_window;
    };

    Application *CreateApplication();
}