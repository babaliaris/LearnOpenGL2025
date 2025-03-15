#include <FRGL/layer.h>
#include <sstream>

namespace FRGL
{
    Layer::Layer(const std::string &title):
    m_id(0), m_hasStarted(false), m_title(title),
    m_application(nullptr)
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

    void Layer::OnUpdate(double time)
    {
    }

    std::string Layer::GetDebug() const
    {
        std::stringstream ss;

        ss << "" << m_title << "(" << m_id << ")";

        return ss.str();
    }
}