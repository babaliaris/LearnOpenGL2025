#include <FRGL/application.h>
#include <iostream>
#include <GL/glew.h>

#include <FRGL/window.h>
#include <FRGL/layer.h>

namespace FRGL
{
    Application::Application(int width, int height, const std::string &title):
    m_layer_incremental(0), m_window(nullptr)
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
        while (m_window->IsRunning())
        {
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer *l : m_layers)
            {
                if (!l->m_hasStarted)
                {
                    l->OnStart();
                    l->m_hasStarted = true;
                }

                else
                {
                    l->OnUpdate();
                }
            }

            m_window->Update();
        }
    }

    Layer *Application::AttachLayer(Layer *layer)
    {
        m_layer_incremental++;

        layer->m_id = m_layer_incremental;

        m_layers.push_back(layer);

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