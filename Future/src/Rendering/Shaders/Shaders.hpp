#pragma once
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <string>
#include "../../Log.hpp"

namespace Future
{
    class Shaders
    {
        public:
            GLuint ID;
            Shaders(const char *vertexPath, const char *fragmentPath, const char *geomentryPath = nullptr);
            void Activate();
            void Delete();
            GLuint vertexShader;
            GLuint fragmentShader;
            GLuint geometryShader;
        private:
            void CheckCompileErrors(GLuint shader, std::string type);
            std::string GetFileContents(const char* filename);
    };
}
