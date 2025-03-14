#include <iostream>
#define FRGL_ENTRY_POINT
#include <FRGL/framework.h>

class LearnOpenGL : public FRGL::Application
{
    public:
    LearnOpenGL()
    {

    }

    ~LearnOpenGL()
    {

    }
};

FRGL::Application *FRGL::CreateApplication()
{
    return new LearnOpenGL();
}