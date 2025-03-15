#pragma once
#include <iostream>

#include "TestLesson.h"
#include "part_I/HelloTriangle.h"
#include "part_I/Shaders.h"

enum class LessonE
{
    TEST_LESSON, HELLO_TRIANGLE, SHADERS
};

FRGL::Layer *SelectLesson(LessonE lesson)
{
    switch (lesson)
    {
        case LessonE::TEST_LESSON:
            return new TestLesson();

        case LessonE::HELLO_TRIANGLE:
            return new HelloTriangle();

        case LessonE::SHADERS:
            return new Shaders();

        default:
            return nullptr;
    }
}