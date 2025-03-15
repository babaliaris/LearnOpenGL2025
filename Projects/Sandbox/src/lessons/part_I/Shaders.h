#pragma once
#include <FRGL/framework.h>

class Shaders: public FRGL::Layer
{
    public:
    Shaders();
    virtual ~Shaders();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnStart() override;
    virtual void OnUpdate(double time) override;

    private:
    unsigned int m_vao, m_vbo;
    FRGL::Shader *m_shader;
};