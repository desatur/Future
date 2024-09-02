#include "Shaders.hpp"

#include <fstream>
#include <stddef.h>
#include <../../../thirdParty/glad/include/glad/glad.h>
#include "../Log.hpp"

namespace Future
{
    Shaders::Shaders(const char* vertexPath, const char* fragmentPath)
    {
        std::string vertexCode = GetFileContents(vertexPath);
        std::string fragmentCode = GetFileContents(fragmentPath);

        const char* vertexShaderCode = vertexCode.c_str();
        const char* fragmentShaderCode = fragmentCode.c_str();

        // Create Vertex Shader Object and get its reference
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        // Attach Vertex Shader source to the Vertex Shader Object
        glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
        // Compile the Vertex Shader into machine code
        glCompileShader(vertexShader);

        // Create Fragment Shader Object and get its reference
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        // Attach Fragment Shader source to the Fragment Shader Object
        glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
        // Compile the Vertex Shader into machine code
        glCompileShader(fragmentShader);

        // Create Shader Program Object and get its reference
        ID = glCreateProgram();
        // Attach the Vertex and Fragment Shaders to the Shader Program
        glAttachShader(ID, vertexShader);
        glAttachShader(ID, fragmentShader);
        // Wrap-up/Link all the shaders together into the Shader Program
        glLinkProgram(ID);

        // Delete the now useless Vertex and Fragment Shader objects
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

    void Shaders::CompileErrors(unsigned int shader, const char* type)
    {
        // Stores status of compilation
        GLint hasCompiled;
        // Character array to store error message in
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
            if (hasCompiled == GL_FALSE)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                FE_CORE_ERROR("SHADER_LINKING_ERROR" /*+ << type << "\n" << infoLog << std::endl*/);
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
            if (hasCompiled == GL_FALSE)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                FE_CORE_ERROR("SHADER_LINKING_ERROR" /*+ type + "\n" + infoLog*/);
            }
        }
    }
}
