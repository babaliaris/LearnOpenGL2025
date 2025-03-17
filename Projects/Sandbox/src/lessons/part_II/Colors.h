#pragma once
#include <FRGL/framework.h>

class ColorsLesson: public FRGL::Layer
{
    public:
    ColorsLesson();
    virtual ~ColorsLesson();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnStart() override;
    virtual void OnUpdate(double time) override;

    private:
    unsigned int m_containerVao, m_containerVbo;
    unsigned int m_lightVao, m_lightVbo;
    glm::vec3 m_lightPos = glm::vec3(-2.0f, 2.0f, -2.0f);
    FRGL::Shader *m_shaderContainer, *m_shaderLight;
    FRGL::Texture *m_textureContainer;
    FRGL::Camera *m_cam;
};