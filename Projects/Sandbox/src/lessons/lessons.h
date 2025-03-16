#pragma once
#include <iostream>

#include "TestLesson.h"
#include "part_I/HelloTriangle.h"
#include "part_I/Shaders.h"
#include "part_I/Textures.h"
#include "part_I/Transformations.h"
#include "part_I/CoordinateSpaces.h"
#include "part_I/Camera.h"

enum class LessonE
{
    PART_I_TEST_LESSON, PART_I_HELLO_TRIANGLE,
    PART_I_SHADERS, PART_I_TEXTURES,
    PART_I_TRANSFORMATIONS, PART_I_COORDINATE_SPACES,
    PART_I_CAMERA
};

FRGL::Layer *SelectLesson(LessonE lesson)
{
    switch (lesson)
    {
        case LessonE::PART_I_TEST_LESSON:
            return new TestLesson();

        case LessonE::PART_I_HELLO_TRIANGLE:
            return new HelloTriangle();

        case LessonE::PART_I_SHADERS:
            return new Shaders();

        case LessonE::PART_I_TEXTURES:
            return new Textures();
        
        case LessonE::PART_I_TRANSFORMATIONS:
            return new Transformations();

        case LessonE::PART_I_COORDINATE_SPACES:
            return new CoordinateSpaces();

        case LessonE::PART_I_CAMERA:
            return new CameraLesson();

        default:
            return nullptr;
    }
}