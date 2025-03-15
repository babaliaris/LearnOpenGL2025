#include <FRGL/shader.h>
#include <FRGL/glcall.h>
#include <GL/glew.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <glm/gtc/type_ptr.hpp>

namespace FRGL
{
    Shader::Shader(const std::string &vSrc, const std::string &fSrc)
    {
        m_id = CreateLinkProgram(vSrc.c_str(), fSrc.c_str());
    }

    Shader::Shader(const char *vFilename, const char *fFilename)
    : m_id(0), m_vFilename(vFilename), m_fFilename(fFilename)
    {
        std::string vertex_source = ReadSourceFromFile(vFilename);
        std::string fragment_source = ReadSourceFromFile(fFilename);

        m_id = CreateLinkProgram(vertex_source.c_str(), fragment_source.c_str());

        std::filesystem::path vPath(vFilename);
        std::filesystem::path fPath(fFilename);

        std::stringstream ss;
        ss << vPath.filename() << "_" << fPath.filename();

        m_programName = ss.str();
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

    void Shader::SetUniform(const char *name, int value)
    {
        this->Bind();

        glCall(GLuint loc = glGetUniformLocation(m_id, name));

        if (loc < 0)
        {
            printf("[Shader: %s] Uniform Location: %s, was not found!\n", m_programName, name);
            return;
        }

        glCall(glUniform1i(loc, value));

        this->UnBind();
    }


    void Shader::SetUniform(const char *name, float value)
    {
        this->Bind();

        glCall(GLuint loc = glGetUniformLocation(m_id, name));

        if (loc < 0)
        {
            printf("[Shader: %s] Uniform Location: %s, was not found!\n", m_programName, name);
            return;
        }

        glCall(glUniform1f(loc, value));

        this->UnBind();
    }


    void Shader::SetUniform(const char *name, const glm::vec2 &vec2)
    {
        this->Bind();

        glCall(GLuint loc = glGetUniformLocation(m_id, name));

        if (loc < 0)
        {
            printf("[Shader: %s] Uniform Location: %s, was not found!\n", m_programName, name);
            return;
        }

        glCall(glUniform2fv(loc, 1, glm::value_ptr(vec2)));

        this->UnBind();
    }


    void Shader::SetUniform(const char *name, const glm::vec3 &vec3)
    {
        this->Bind();

        glCall(GLuint loc = glGetUniformLocation(m_id, name));

        if (loc < 0)
        {
            printf("[Shader: %s] Uniform Location: %s, was not found!\n", m_programName, name);
            return;
        }

        glCall(glUniform3fv(loc, 1, glm::value_ptr(vec3)));

        this->UnBind();
    }


    void Shader::SetUniform(const char *name, const glm::vec4 &vec4)
    {
        this->Bind();

        glCall(GLuint loc = glGetUniformLocation(m_id, name));

        if (loc < 0)
        {
            printf("[Shader: %s] Uniform Location: %s, was not found!\n", m_programName, name);
            return;
        }

        glCall(glUniform4fv(loc, 1, glm::value_ptr(vec4)));

        this->UnBind();
    }


    void Shader::SetUniform(const char *name, const glm::mat3 &mat3)
    {
        this->Bind();

        glCall(GLuint loc = glGetUniformLocation(m_id, name));

        if (loc < 0)
        {
            printf("[Shader: %s] Uniform Location: %s, was not found!\n", m_programName, name);
            return;
        }

        glCall(glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(mat3)));

        this->UnBind();
    }


    void Shader::SetUniform(const char *name, const glm::mat4 &mat4)
    {
        this->Bind();

        glCall(GLuint loc = glGetUniformLocation(m_id, name));

        if (loc < 0)
        {
            printf("[Shader: %s] Uniform Location: %s, was not found!\n", m_programName, name);
            return;
        }

        glCall(glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat4)));

        this->UnBind();
    }


    unsigned int Shader::CreateCompileShader(const char *source, GLenum type)
    {
        GLuint shader = glCreateShader(type);

        glCall(glShaderSource(shader, 1, &source, NULL));

        glCall(glCompileShader(shader));

        GLint info_length, success;

        glCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
        glCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length));


        if (!success)
        {
            std::string filename = (type == GL_VERTEX_SHADER ? m_vFilename : m_fFilename);

            char *info = new char[info_length];

            glCall(glGetShaderInfoLog(shader, info_length, NULL, info));

            std::cout << "[Shader Compilation Error]: " << filename << std::endl << info << std::endl;

            delete info;

            return 0;
        }

        return shader;
    }


    unsigned int Shader::CreateLinkProgram(const char *vertexSource, const char *fragSource)
    {
        GLuint vertexShader = CreateCompileShader(vertexSource, GL_VERTEX_SHADER);
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



    std::string Shader::ReadSourceFromFile(const char *filename)
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
}
