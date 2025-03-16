#pragma once
#include <glm/glm.hpp>

namespace FRGL
{
    enum class CameraMoveE
    {
        UP, DOWN, LEFT, RIGHT,
        FORWARD, BACKWARD
    };


    enum class CameraModeE
    {
        KEYBOARD, KEYBOARD_MOUSE
    };


    class Camera
    {
        public:
        Camera(const glm::vec3 &pos);
        Camera(float posx, float posy, float posz);
        ~Camera();

        void Move(CameraModeE mode, CameraMoveE move, float deltaTime);

        glm::mat4 GetProj();

        inline void SetSensitivity(float sens) {m_sensitivity = sens;}
        inline void SetSpeed(float speed) {m_speed = speed;}
        inline void SetDirection(const glm::vec3 &dir){m_direction = dir;this->CalculateLocalSpace();}
        inline void SetPosition(const glm::vec3 &pos){m_pos = pos;this->CalculateLocalSpace();}

        private:
        float m_sensitivity = 0.4f, m_speed = 1.0f;
        glm::vec3 m_pos, m_right, m_up, m_direction;

        void CalculateLocalSpace();
    };
}