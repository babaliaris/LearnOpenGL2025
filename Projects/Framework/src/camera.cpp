#include <FRGL/camera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace FRGL
{
    Camera::Camera(const glm::vec3 &pos):
    m_pos(pos), m_direction(glm::vec3(0.0f, 0.0f, -1.0f))
    {
        this->CalculateLocalSpace();
    }

    Camera::Camera(float posx, float posy, float posz):
    m_direction(glm::vec3(0.0f, 0.0f, -1.0f))
    {
        m_pos = glm::vec3(posx, posy, posz);
        this->CalculateLocalSpace();
    }


    Camera::~Camera()
    {

    }


    void Camera::Move(CameraModeE mode, CameraMoveE move)
    {
        if (mode == CameraModeE::KEYBOARD)
        {
            if (move == CameraMoveE::LEFT)
                m_pos = m_pos - m_right * m_speed;

            else if (move == CameraMoveE::RIGHT)
                m_pos = m_pos + m_right * m_speed;

            if (move == CameraMoveE::UP)
                m_pos = m_pos + m_up * m_speed;

            else if (move == CameraMoveE::DOWN)
                m_pos = m_pos - m_up * m_speed;

            if (move == CameraMoveE::FORWARD)
                m_pos = m_pos + m_direction * m_speed;

            else if (move == CameraMoveE::BACKWARD)
                m_pos = m_pos - m_direction * m_speed;
        }

        this->CalculateLocalSpace();
    }


    glm::mat4 Camera::GetProj()
    {
        return glm::lookAt(m_pos, m_pos + m_direction, glm::vec3(0.0f, 1.0f, 0.0f));
    }


    void Camera::CalculateLocalSpace()
    {
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        m_direction = glm::normalize(m_direction);
        m_right     = glm::normalize(glm::cross(m_direction, up));
        m_up        = glm::normalize(glm::cross(m_right, m_direction));
    }
}