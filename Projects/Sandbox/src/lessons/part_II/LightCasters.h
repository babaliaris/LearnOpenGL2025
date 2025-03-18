#pragma once
#include <FRGL/framework.h>

class LightCasters: public FRGL::Layer
{
    public:
    LightCasters();
    virtual ~LightCasters();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnStart() override;
    virtual void OnUpdate(double time) override;

    private:
    unsigned int m_containerVao, m_containerVbo;
    unsigned int m_lightVao, m_lightVbo;

    glm::vec3 m_lightPos = glm::vec3(-2.0f, 2.0f, -2.0f);

    glm::vec3 m_cubePositions[10];

    FRGL::Shader *m_shaderContainer, *m_shaderLight;
    FRGL::Texture *m_containerDiffuse, *m_containerSpecular;
    FRGL::Camera *m_cam;

    private:
    void InitializeGeometry();
};