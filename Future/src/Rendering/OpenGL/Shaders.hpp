#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <fstream>
#include <glad/glad.h>

namespace Future
{
    class Shaders
    {
        public:
            GLuint ID;
            Shaders(const char* vertexPath, const char* fragmentPath);
            void Activate();
            void Delete();
        private:
            void CompileErrors(unsigned int shader, const char* type);
            std::string GetFileContents(const char* filename);
    };
}

#endif //SHADERS_HPP
