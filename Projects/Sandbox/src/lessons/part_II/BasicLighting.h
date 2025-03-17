#pragma once
#include <FRGL/framework.h>

class BasicLighting: public FRGL::Layer
{
    public:
    BasicLighting();
    virtual ~BasicLighting();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnStart() override;
    virtual void OnUpdate(double time) override;

    private:
    unsigned int m_containerVao, m_containerVbo;
    unsigned int m_lightVao, m_lightVbo;
    glm::vec3 m_lightPos = glm::vec3(-2.0f, 2.0f, -2.0f);
    float m_containerVertices[5*36], m_lightVertices[3*36];
    FRGL::Shader *m_shaderContainer, *m_shaderLight;
    FRGL::Texture *m_textureContainer;
    FRGL::Camera *m_cam;

    private:
    void InitializeVertices();
};