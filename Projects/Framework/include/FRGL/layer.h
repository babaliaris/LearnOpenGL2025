#pragma once
#include <string>

namespace FRGL
{
    class Application;

    class Layer
    {
        friend class Application;

        public:
        Layer(const std::string &title = "Layer");
        virtual ~Layer();

        virtual void OnAttach();
        virtual void OnDetach();
        virtual void OnStart();
        virtual void OnUpdate(double time);

        std::string GetDebug() const;

        inline unsigned int GetID() {return m_id;}
        inline std::string GetTitle() {return m_title;}
        inline Application *GetApp() {return m_application;}

        private:
        unsigned int m_id;
        bool m_hasStarted;
        std::string m_title;
        Application *m_application;

    };
}