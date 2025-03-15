#include <FRGL/shader.h>
#include <FRGL/glcall.h>
#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include <fstream>

GLuint CreateCompileShader(const char *source, GLenum type);
GLuint CreateLinkProgram(const char *shaderSource, const char *fragSource);
std::string ReadSourceFromFile(const char *filename);

namespace FRGL
{
    Shader::Shader(const std::string &vSrc, const std::string &fSrc)
    {
        m_id = CreateLinkProgram(fSrc.c_str(), vSrc.c_str());
    }

    Shader::Shader(const char *vFilename, const char *fFilename)
    {
        std::string vertex_source = ReadSourceFromFile(vFilename);
        std::string fragment_source = ReadSourceFromFile(fFilename);

        m_id = CreateLinkProgram(vertex_source.c_str(), fragment_source.c_str());
    }

    Shader::~Shader()
    {
        glCall(glDeleteProgram(m_id));
    }

    void Shader::Bind()
    {
        glCall(glUseProgram(m_id));
    }

    void Shader::UnBind()
    {
        glCall(glUseProgram(0));
    }
}



GLuint CreateCompileShader(const char *source, GLenum type)
{
    GLuint shader = glCreateShader(type);

    glCall(glShaderSource(shader, 1, &source, NULL));

    glCall(glCompileShader(shader));

    GLint info_length, success;

    glCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    glCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length));

    if (!success)
    {
        char *info = new char[info_length];

        glCall(glGetShaderInfoLog(shader, info_length, NULL, info));

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

    glCall(GLuint program = glCreateProgram());

    glCall(glAttachShader(program, vertexShader));
    glCall(glAttachShader(program, fragShader));

    glCall(glLinkProgram(program));

    glCall(glDeleteShader(vertexShader));
    glCall(glDeleteShader(fragShader));

    GLint info_length, success;

    glCall(glGetProgramiv(program, GL_LINK_STATUS, &success));
    glCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_length));

    if (!success)
    {
        char *info = new char[info_length];

        glCall(glGetProgramInfoLog(program, info_length, NULL, info));

        std::cout << "[Program Linkage Error]\n" << info << std::endl;

        delete info;

        return 0;
    }

    return program;
}



std::string ReadSourceFromFile(const char *filename)
{
    std::ifstream file(filename, std::ios::binary);
    std::stringstream ss;

    if (!file.is_open())
    {
        std::cout << "Failed to open File: " << filename << std::endl;
        return "";
    }

    ss << file.rdbuf();

    return ss.str();
}