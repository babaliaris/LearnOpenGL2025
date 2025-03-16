#include <FRGL/camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <FRGL/application.h>
#include <FRGL/window.h>

namespace FRGL
{
    Camera::Camera(Application *app, const glm::vec3 &pos):
    m_pos(pos), m_direction(glm::vec3(0.0f, 0.0f, -1.0f)), m_app(app)
    {
        this->CalculateLocalSpace();
    }

    Camera::Camera(Application *app, float posx, float posy, float posz):
    m_direction(glm::vec3(0.0f, 0.0f, -1.0f)), m_app(app)
    {
        m_pos = glm::vec3(posx, posy, posz);
        this->CalculateLocalSpace();
    }


    Camera::~Camera()
    {

    }


    void Camera::Move(CameraModeE mode)
    {
        if (glfwGetKey(m_app->GetWindow()->GetGLFWwindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            m_actualSpeed = m_sprint;

        else if (glfwGetKey(m_app->GetWindow()->GetGLFWwindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
            m_actualSpeed = m_speed;

        if (mode == CameraModeE::KEYBOARD)
        {
            if (glfwGetKey(m_app->GetWindow()->GetGLFWwindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
                m_pos = m_pos - m_right * m_actualSpeed * m_app->GetDeltaTime();

            else if (glfwGetKey(m_app->GetWindow()->GetGLFWwindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
                m_pos = m_pos + m_right * m_actualSpeed * m_app->GetDeltaTime();

            if (glfwGetKey(m_app->GetWindow()->GetGLFWwindow(), GLFW_KEY_UP) == GLFW_PRESS)
                m_pos = m_pos + m_up * m_actualSpeed * m_app->GetDeltaTime();

            else if (glfwGetKey(m_app->GetWindow()->GetGLFWwindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
                m_pos = m_pos - m_up * m_actualSpeed * m_app->GetDeltaTime();

            if (glfwGetKey(m_app->GetWindow()->GetGLFWwindow(), GLFW_KEY_W) == GLFW_PRESS)
                m_pos = m_pos + m_direction * m_actualSpeed * m_app->GetDeltaTime();

            else if (glfwGetKey(m_app->GetWindow()->GetGLFWwindow(), GLFW_KEY_S) == GLFW_PRESS)
                m_pos = m_pos - m_direction * m_actualSpeed * m_app->GetDeltaTime();
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