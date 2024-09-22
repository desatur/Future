#include "Camera.hpp"

namespace Future
{
	Camera::Camera(int width, int height, const glm::vec3 position)
	{
		Camera::width = width;
		Camera::height = height;
		Position = position;
	}

	void Camera::UpdateMatrix(float FOVdeg, const float nearPlane, const float farPlane)
	{
		const float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

		// Initializes matrices since otherwise they will be the null matrix
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		// Makes camera look in the right direction from the right position
		view = glm::lookAt(Position, Position + Orientation, Up);

		// Adds perspective to the scene
		projection = glm::perspective(glm::radians(FOVdeg), aspectRatio, nearPlane, farPlane);
		cameraMatrix = projection * view;
	}

	void Camera::Matrix(Shaders &shader, const char *uniform)
	{
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix)); // Exports the camera matrix to the Vertex Shader
	}

	void Camera::SetPosition(const glm::vec3 position)
	{
		Position = position;
	}
}
