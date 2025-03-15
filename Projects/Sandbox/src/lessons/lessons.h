#pragma once
#include <iostream>

#include "TestLesson.h"
#include "part_I/HelloTriangle.h"

enum class LessonE
{
    TEST_LESSON, HELLO_TRIANGLE
};

FRGL::Layer *SelectLesson(LessonE lesson)
{
    switch (lesson)
    {
        case LessonE::TEST_LESSON:
            return new TestLesson();

        case LessonE::HELLO_TRIANGLE:
            return new HelloTriangle();

        default:
            return nullptr;
    }
}