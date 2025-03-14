#pragma once

namespace FRGL
{
    class Application
    {
        public:
        Application();
        virtual ~Application();

        void Run();

        private:
    };

    Application *CreateApplication();
}