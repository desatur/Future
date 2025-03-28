#pragma once
#include "Shaders/Shaders.hpp"
#include "../../../thirdParty/glm/glm/vec3.hpp"
#include "../../../thirdParty/glm/glm/glm.hpp"
#include <glad/glad.h>
#include "../../../thirdParty/glm/glm/gtc/type_ptr.hpp"
#include "../../../thirdParty/glm/glm/gtc/matrix_transform.hpp"
#include "../../../thirdParty/glm/glm/gtc/type_ptr.hpp"
#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#include "../../../thirdParty/glm/glm/gtx/vector_angle.hpp"
#include "SDL.h"
#include "../Window/Window.hpp"

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

            bool focus = true;

            // Stores the width and height of the window
            float width, height;

            // Camera constructor to set up initial values
            Camera(float width, float height, const glm::vec3 position);

            // Updates and exports the camera matrix to the Vertex Shader
            void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
            void Matrix(Shaders& shader, const char* uniform);
            void SetPosition(glm::vec3 position);
            void DebugMove(float deltaTime);
    };
}
