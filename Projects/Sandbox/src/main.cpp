#include <iostream>

#define FRGL_ENTRY_POINT
#include <FRGL/framework.h>
#include "lessons/lessons.h"

class LearnOpenGL : public FRGL::Application
{
    public:
    LearnOpenGL():
    Application(512, 512, "Learn OpenGL")
    {
        this->AttachLayer(SelectLesson(LessonE::SHADERS));
    }

    ~LearnOpenGL()
    {

    }
};

FRGL::Application *FRGL::CreateApplication()
{
    return new LearnOpenGL();
}