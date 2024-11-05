#include "Shaders.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include "../Log.hpp"

namespace Future
{
    Shaders::Shaders(const char *vertexPath, const char *fragmentPath)
    {
        std::string vertexCode = GetFileContents(vertexPath);
        std::string fragmentCode = GetFileContents(fragmentPath);

        const char* vertexShaderCode = vertexCode.c_str();
        const char* fragmentShaderCode = fragmentCode.c_str();

        // Create and compile the vertex shader
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
        glCompileShader(vertexShader);
        CheckCompileErrors(vertexShader, "VERTEX");

        // Create and compile the fragment shader
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
        glCompileShader(fragmentShader);
        CheckCompileErrors(fragmentShader, "FRAGMENT");

        // Create and link the shader program
        ID = glCreateProgram();
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        glLinkProgram(ID);
        CheckCompileErrors(ID, "PROGRAM");

        // Delete the individual shaders after linking
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    std::string Shaders::GetFileContents(const char* filename)
    {
        std::ifstream in(filename, std::ios::binary);
        if (in)
        {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return(contents);
        }
        throw(errno);
    }

    void Shaders::Activate()
    {
        glUseProgram(ID);
    }

    void Shaders::Delete()
    {
        glDeleteProgram(ID);
    }

    void Shaders::CheckCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" 
                          << infoLog << "\n -- --------------------------------------------------- -- " 
                          << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" 
                          << infoLog << "\n -- --------------------------------------------------- -- " 
                          << std::endl;
            }
        }
    }
}
