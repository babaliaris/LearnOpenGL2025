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

        void Move(CameraModeE mode, CameraMoveE move);

        glm::mat4 GetProj();

        private:
        float m_sensitivity = 0.4f, m_speed = 0.2f;
        glm::vec3 m_pos, m_right, m_up, m_direction;

        void CalculateLocalSpace();
    };
}