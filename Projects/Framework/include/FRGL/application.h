#pragma once
#include <string>
#include <vector>

namespace FRGL
{
    class Window;
    class Layer;

    class Application
    {
        public:
        Application(int width, int height, const std::string &title);
        virtual ~Application();

        void Run();

        void AttachLayer(Layer *layer);
        void DetachLayer(unsigned int id);

        private:
        unsigned int m_layer_incremental;
        Window *m_window;
        std::vector<Layer *> m_layers;
    };

    Application *CreateApplication();
}