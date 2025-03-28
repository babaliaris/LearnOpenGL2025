#pragma once
#include <FRGL/framework.h>

class Blending: public FRGL::Layer
{
    public:
    Blending();
    virtual ~Blending();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnStart() override;
    virtual void OnUpdate(double time) override;

    private:
    unsigned int m_vbo, m_containerVao, m_lightVao;

    glm::vec3 m_lightPos = glm::vec3(-2.0f, 2.0f, -2.0f);

    FRGL::Shader *m_shaderContainer, *m_shaderLight, *m_shaderOutline;
    FRGL::Camera *m_cam;

    FRGL::Texture *m_diffuse, *m_specular;

    private:
    void InitializeGeometry();
};