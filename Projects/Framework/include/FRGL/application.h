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

        Layer *AttachLayer(Layer *layer);
        void DetachLayer(unsigned int id);

        inline Window *GetWindow() const {return m_window;}
        inline float GetDeltaTime() const {return m_deltatime;}

        private:
        unsigned int m_layer_incremental;
        Window *m_window;
        float m_deltatime;
        std::vector<Layer *> m_layers;
    };

    Application *CreateApplication();
}