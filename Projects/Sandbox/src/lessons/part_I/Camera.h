#pragma once
#include <FRGL/framework.h>

class CameraLesson: public FRGL::Layer
{
    public:
    CameraLesson();
    virtual ~CameraLesson();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnStart() override;
    virtual void OnUpdate(double time) override;

    private:
    unsigned int m_vao, m_vbo;
    FRGL::Shader *m_shader;
    FRGL::Texture *m_texture1, *m_texture2;
    glm::vec3 m_cubePositions[10];
    FRGL::Camera *m_cam;
};