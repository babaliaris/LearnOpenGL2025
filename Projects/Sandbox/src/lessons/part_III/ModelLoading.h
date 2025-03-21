#pragma once
#include <FRGL/framework.h>

class ModelLoading: public FRGL::Layer
{
    public:
    ModelLoading();
    virtual ~ModelLoading();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnStart() override;
    virtual void OnUpdate(double time) override;

    private:
    unsigned int m_lightVao, m_lightVbo;

    FRGL::Model *m_model;

    glm::vec3 m_lightPos = glm::vec3(-2.0f, 2.0f, -2.0f);

    FRGL::Shader *m_shaderModel, *m_shaderLight;
    FRGL::Camera *m_cam;

    private:
    void InitializeGeometry();
};