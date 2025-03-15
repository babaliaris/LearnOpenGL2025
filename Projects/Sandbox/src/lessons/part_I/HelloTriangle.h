#pragma once
#include <FRGL/framework.h>

class HelloTriangle: public FRGL::Layer
{
    public:
    HelloTriangle();
    virtual ~HelloTriangle();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnStart() override;
    virtual void OnUpdate() override;

    private:
};