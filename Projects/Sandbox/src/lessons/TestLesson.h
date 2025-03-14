#pragma once
#include <FRGL/framework.h>

class TestLesson: public FRGL::Layer
{
    public:
    TestLesson();
    virtual ~TestLesson();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnStart() override;
    virtual void OnUpdate() override;

    private:
    bool m_printOnUpdateOnce;
};