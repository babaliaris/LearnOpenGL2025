#include <FRGL/application.h>
#include <iostream>
#include <GL/glew.h>

#include <FRGL/window.h>
#include <FRGL/layer.h>

namespace FRGL
{
    Application::Application(int width, int height, const std::string &title):
    m_layer_incremental(0), m_window(nullptr), m_deltatime(0)
    {
        m_window = new Window(width, height, title);
    }

    Application::~Application()
    {
        for (Layer *l : m_layers)
        {
            delete l;
        }

        delete m_window;
    }

    void Application::Run()
    {
        float currentFrameTime  = m_window->GetTime();
        float previousFrameTime = m_window->GetTime();

        while (m_window->IsRunning())
        {
            currentFrameTime    = m_window->GetTime();
            m_deltatime         = currentFrameTime - previousFrameTime;
            previousFrameTime   = currentFrameTime;

            for (Layer *l : m_layers)
            {
                if (!l->m_hasStarted)
                {
                    l->OnStart();
                    l->m_hasStarted = true;
                }

                else
                {
                    l->OnUpdate(m_window->GetTime());
                }
            }

            m_window->Update();
        }
    }

    Layer *Application::AttachLayer(Layer *layer)
    {
        m_layer_incremental++;

        layer->m_id = m_layer_incremental;

        layer->m_application = this;

        m_layers.push_back(layer);

        std::cout << "Starting Lesson: " << layer->GetDebug() << std::endl;

        layer->OnAttach();

        return layer;
    }

    void Application::DetachLayer(unsigned int id)
    {
        for (size_t i = 0; i < m_layers.size(); i++)
        {
            if (m_layers[i]->GetID() == id)
            {
                m_layers[i]->OnDetach();
                m_layers.erase(m_layers.begin() + i);
                break;
            }
        }
    }
}