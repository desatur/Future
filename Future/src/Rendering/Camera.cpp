#include "Camera.hpp"

namespace Future
{
	Camera::Camera(float width, float height, const glm::vec3 position)
	{
		Camera::width = width;
		Camera::height = height;
		Position = position;
	}

	void Camera::UpdateMatrix(float FOVdeg, const float nearPlane, const float farPlane)
	{
		// Initializes matrices since otherwise they will be the null matrix
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		// Makes camera look in the right direction from the right position
		view = glm::lookAt(Position, Position + Orientation, Up);

		// Adds perspective to the scene
		projection = glm::perspective(glm::radians(FOVdeg), width / height, nearPlane, farPlane);
		
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

	void Camera::DebugMove(float deltaTime)
	{
		float speed = 10.0f * deltaTime;
		float sensitivity = 100.0f * deltaTime;
		const Uint8* state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_LALT]) // Left Alt key
		{
			focus = false;
		}
		if (state[SDL_SCANCODE_RALT]) // Right Alt key
		{
			focus = true;
		}

		if (state[SDL_SCANCODE_LSHIFT]) // Left Shift key
		{
			speed = speed * 2;
		}
		if (state[SDL_SCANCODE_C]) // C key
		{
			speed = speed * 0.5;
		}

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
		if (focus)
		{
			SDL_ShowCursor(SDL_DISABLE);
				
			// Get the current position of the mouse
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			// Calculate mouse displacement relative to center of the screen
			float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
			float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

			// Apply vertical rotation (pitch) using the right vector
			glm::vec3 right = glm::normalize(glm::cross(Orientation, Up));
			glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), right);

			// Ensure the camera doesn't flip upside down (clamping between -89 to 89 degrees for pitch)
			if (glm::angle(newOrientation, Up) < glm::radians(89.0f))
			{
				Orientation = newOrientation;
			}

			// Apply horizontal rotation (yaw) using the up vector
			Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

			SDL_WarpMouseInWindow(NULL, width / 2, height / 2);
		}
		else
		{
			SDL_ShowCursor(SDL_ENABLE);
		}
	}

}
