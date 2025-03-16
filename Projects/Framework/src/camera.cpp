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

        else
        {
            double mouseX, mouseY;
            glfwGetCursorPos(m_app->GetWindow()->GetGLFWwindow(), &mouseX, &mouseY);

            if (m_firstMouse)
            {
                m_lastX = (float)mouseX;
                m_lastY = (float)mouseY;
                m_firstMouse = false;
            }

            float xOffset = mouseX - m_lastX;
            float yOffset = m_lastY - mouseY;

            m_lastX = mouseX;
            m_lastY = mouseY;

            m_pitch += yOffset * m_sensitivity * m_app->GetDeltaTime();
            m_yaw   += xOffset * m_sensitivity * m_app->GetDeltaTime();

            if (m_pitch > 89.0f)
                m_pitch = 89.0f;

            if (m_pitch < -89.0f)
                m_pitch = -89.0f;

            float yaw_rad = glm::radians(m_yaw);
            float pitch_rad = glm::radians(m_pitch);

            m_direction = glm::normalize(glm::vec3(
                cos(yaw_rad) * cos(pitch_rad),
                sin(pitch_rad),
                sin(yaw_rad) * cos(pitch_rad)
            ));


            if (glfwGetKey(m_app->GetWindow()->GetGLFWwindow(), GLFW_KEY_A) == GLFW_PRESS)
                m_pos = m_pos - m_right * m_actualSpeed * m_app->GetDeltaTime();

            else if (glfwGetKey(m_app->GetWindow()->GetGLFWwindow(), GLFW_KEY_D) == GLFW_PRESS)
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