#include "HelloTriangle.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint CreateCompileShader(const char *source, GLenum type)
{
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, NULL);

    glCompileShader(shader);

    GLint info_length, success;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length);

    if (!success)
    {
        char *info = new char[info_length];

        glGetShaderInfoLog(shader, info_length, NULL, info);

        std::cout << "[Shader Compilation Error]\n" << info << std::endl;

        delete info;

        return 0;
    }

    return shader;
}


GLuint CreateLinkProgram(const char *shaderSource, const char *fragSource)
{
    GLuint vertexShader = CreateCompileShader(shaderSource, GL_VERTEX_SHADER);
    GLuint fragShader = CreateCompileShader(fragSource, GL_FRAGMENT_SHADER);

    if (!vertexShader || !fragShader) return 0;

    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

    GLint info_length, success;

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_length);

    if (!success)
    {
        char *info = new char[info_length];

        glGetProgramInfoLog(program, info_length, NULL, info);

        std::cout << "[Program Linkage Error]\n" << info << std::endl;

        delete info;

        return 0;
    }

    return program;
}

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

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    std::string vertexSrc = ""
    "#version 330 core\n"
    "layout (location=0) in vec3 vPos;"
    "void main(){"
    "gl_Position = vec4(vPos, 1.0f);"
    "}";

    std::string fragSrc = ""
    "#version 330 core\n"
    "out vec4 color;"
    "void main(){"
    "color = vec4(1.0f, 0.0f, 0.0f, 1.0f);"
    "}";

    m_program = CreateLinkProgram(vertexSrc.c_str(), fragSrc.c_str());

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (const void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_VERTEX_ARRAY, 0);

}

void HelloTriangle::OnDetach()
{
    glDeleteProgram(m_program);
}

void HelloTriangle::OnStart()
{
}

void HelloTriangle::OnUpdate()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_program);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(0);
    glBindVertexArray(0);
}