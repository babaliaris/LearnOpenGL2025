#pragma once
#include <string>

namespace FRGL
{
    class Layer
    {
        friend class Application;

        public:
        Layer(const std::string &title = "Layer");
        virtual ~Layer();

        virtual void OnAttach();
        virtual void OnDetach();
        virtual void OnStart();
        virtual void OnUpdate();

        inline unsigned int GetID() {return m_id;}
        inline std::string GetTitle() {return m_title;}

        private:
        unsigned int m_id;
        bool m_hasStarted;
        std::string m_title;
    };
}