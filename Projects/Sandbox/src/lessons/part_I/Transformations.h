#pragma once
#include <FRGL/framework.h>

class Transformations: public FRGL::Layer
{
    public:
    Transformations();
    virtual ~Transformations();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnStart() override;
    virtual void OnUpdate(double time) override;

    private:
    unsigned int m_vao, m_vbo;
    FRGL::Shader *m_shader;
    FRGL::Texture *m_texture1, *m_texture2;
};