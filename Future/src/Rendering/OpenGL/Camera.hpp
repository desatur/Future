#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Shaders.hpp"
#include "vec3.hpp"
#include "GLFW/glfw3.h"
#include "glm\glm.hpp"
#include "glad\glad.h"
#include "gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/vector_angle.hpp"

namespace Future {
    class Camera
    {
        public:
            // Stores the main vectors of the camera
            glm::vec3 Position;
            glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
            glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
            glm::mat4 cameraMatrix = glm::mat4(1.0f);

            // Prevents the camera from jumping around when first clicking left click
            bool firstClick = true;

            // Stores the width and height of the window
            int width, height;

            // Adjust the speed of the camera and it's sensitivity when looking around
            float speed = 0.00001f;
            float sensitivity = 50.0f;

            // Camera constructor to set up initial values
            Camera(int width, int height, glm::vec3 position);

            // Updates and exports the camera matrix to the Vertex Shader
            void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
            void Matrix(Shaders& shader, const char* uniform);
            void Inputs(GLFWwindow* window);
    };
}

#endif //CAMERA_HPP
