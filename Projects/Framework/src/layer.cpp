#include <FRGL/layer.h>

namespace FRGL
{
    Layer::Layer(const std::string &title):
    m_id(0), m_hasStarted(false), m_title(title)
    {
    }

    Layer::~Layer()
    {
    }

    void Layer::OnAttach()
    {
    }

    void Layer::OnDetach()
    {
    }

    void Layer::OnStart()
    {
    }

    void Layer::OnUpdate()
    {
    }
}