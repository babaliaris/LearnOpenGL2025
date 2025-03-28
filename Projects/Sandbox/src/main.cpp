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
        FRGL::Layer *lesson = SelectLesson(LessonE::PART_IV_BLENDING);

        this->GetWindow()->SetTitle(lesson->GetTitle());

        this->AttachLayer(lesson);
    }

    ~LearnOpenGL()
    {

    }
};

FRGL::Application *FRGL::CreateApplication()
{
    return new LearnOpenGL();
}