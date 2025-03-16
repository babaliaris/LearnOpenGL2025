#pragma once
#include <glm/glm.hpp>

namespace FRGL
{
    class Application;

    enum class CameraModeE
    {
        KEYBOARD, KEYBOARD_MOUSE
    };


    class Camera
    {
        public:
        Camera(Application *app, const glm::vec3 &pos);
        Camera(Application *app, float posx, float posy, float posz);
        ~Camera();

        void Move(CameraModeE mode);

        glm::mat4 GetProj();

        inline void SetSensitivity(float sens) {m_sensitivity = sens;}
        inline void SetSpeed(float speed) {m_speed = speed;}
        inline void SetSprint(float sprintSpeed) {m_sprint = sprintSpeed;}
        inline void SetDirection(const glm::vec3 &dir){m_direction = dir;this->CalculateLocalSpace();}
        inline void SetPosition(const glm::vec3 &pos){m_pos = pos;this->CalculateLocalSpace();}

        private:
        float m_sensitivity = 0.4f, m_actualSpeed = 5.0f, m_speed = 5.0f, m_sprint = 10.0f;
        glm::vec3 m_pos, m_right, m_up, m_direction;
        Application *m_app;

        void CalculateLocalSpace();
    };
}