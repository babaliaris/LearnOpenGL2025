#pragma once
#include <FRGL/framework.h>

class HelloTriangle: public FRGL::Layer
{
    public:
    HelloTriangle();
    virtual ~HelloTriangle();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnStart() override;
    virtual void OnUpdate(double time) override;

    private:
    unsigned int m_vao, m_vbo, m_program;
};