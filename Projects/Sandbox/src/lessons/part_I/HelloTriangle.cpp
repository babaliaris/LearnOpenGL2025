#include "HelloTriangle.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

HelloTriangle::HelloTriangle()
:Layer("HelloTriangle")
{
}

HelloTriangle::~HelloTriangle()
{
}

void HelloTriangle::OnAttach()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void HelloTriangle::OnDetach()
{
}

void HelloTriangle::OnStart()
{
}

void HelloTriangle::OnUpdate()
{
    glClear(GL_COLOR_BUFFER_BIT);
}