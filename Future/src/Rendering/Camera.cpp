#include "Camera.hpp"
#include "SDL.h"

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

	void Camera::DebugMove()
	{
		float speed = 0.4f;
		const Uint8* state = SDL_GetKeyboardState(NULL);

		// Handles key inputs
		if (state[SDL_SCANCODE_W]) // W key
		{
			Position += speed * Orientation;
		}
		if (state[SDL_SCANCODE_A]) // A key
		{
			Position += speed * -glm::normalize(glm::cross(Orientation, Up));
		}
		if (state[SDL_SCANCODE_S]) // S key
		{
			Position += speed * -Orientation;
		}
		if (state[SDL_SCANCODE_D]) // D key
		{
			Position += speed * glm::normalize(glm::cross(Orientation, Up));
		}

		// Handles mouse inputs
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) // Left mouse button
		{
			// Hides mouse cursor
			SDL_ShowCursor(SDL_DISABLE);

			// Stores the coordinates of the cursor
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			// Normalizes and shifts the coordinates of the cursor
			float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
			float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

			// Calculates upcoming vertical change in the Orientation
			glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

			// Decides whether or not the next vertical Orientation is legal or not
			if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
			{
				Orientation = newOrientation;
			}

			// Rotates the Orientation left and right
			Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

			// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
			//SDL_WarpMouseInWindow(window, width / 2, height / 2);
		}
		else // If left mouse button is released
		{
			// Unhides cursor since camera is not looking around anymore
			SDL_ShowCursor(SDL_ENABLE);
			// Makes sure the next time the camera looks around it doesn't jump
			firstClick = true;
		}
	}
}
