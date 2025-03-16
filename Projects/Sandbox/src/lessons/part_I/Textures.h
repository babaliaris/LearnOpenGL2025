#pragma once
#include <FRGL/framework.h>

class Textures: public FRGL::Layer
{
    public:
    Textures();
    virtual ~Textures();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnStart() override;
    virtual void OnUpdate(double time) override;

    private:
    unsigned int m_vao, m_vbo;
    FRGL::Shader *m_shader;
    FRGL::Texture *m_texture1, *m_texture2;
};