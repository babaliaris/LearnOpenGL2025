#pragma once
#include <iostream>

#include "TestLesson.h"
#include "part_I/HelloTriangle.h"
#include "part_I/Shaders.h"
#include "part_I/Textures.h"

enum class LessonE
{
    TEST_LESSON, HELLO_TRIANGLE, SHADERS,
    TEXTURES
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
        
        case LessonE::TEXTURES:
            return new Textures();

        default:
            return nullptr;
    }
}