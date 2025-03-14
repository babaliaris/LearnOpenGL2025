#include <iostream>

#define FRGL_ENTRY_POINT
#include <FRGL/framework.h>

#include "lessons/TestLesson.h"

class LearnOpenGL : public FRGL::Application
{
    public:
    LearnOpenGL():
    Application(512, 512, "Learn OpenGL")
    {
        this->AttachLayer(new TestLesson());
    }

    ~LearnOpenGL()
    {

    }
};

FRGL::Application *FRGL::CreateApplication()
{
    return new LearnOpenGL();
}