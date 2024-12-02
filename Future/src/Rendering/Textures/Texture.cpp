#include "Texture.hpp"

namespace Future
{
	Texture::Texture(const char* image_path, const char* texType, GLuint slot)
	{
		type = texType;
		int widthImg, heightImg, numColCh;
		//stbi_set_flip_vertically_on_load(true);
		unsigned char* bytes = stbi_load(image_path, &widthImg, &heightImg, &numColCh, 0);

		glGenTextures(1, &ID);
		// Assigns the texture to a Texture Unit
		glActiveTexture(GL_TEXTURE0 + slot);
		unit = slot;
		glBindTexture(GL_TEXTURE_2D, ID);

		// Configures the type of algorithm that is used to make the image_path smaller or bigger
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Configures the way the texture repeats (if it does at all)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		if (type == "normal") // prevents SRGB from deforming normals
			glTexImage2D
			(
				GL_TEXTURE_2D,
				0,
				GL_SRGB,
				widthImg,
				heightImg,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				bytes
			);
		else if (numColCh == 4)
			glTexImage2D
			(
				GL_TEXTURE_2D,
				0,
				GL_SRGB_ALPHA,
				widthImg,
				heightImg,
				0,
				GL_RGBA,
				GL_UNSIGNED_BYTE,
				bytes
			);
		else if (numColCh == 3)
			glTexImage2D
			(
				GL_TEXTURE_2D,
				0,
				GL_SRGB_ALPHA,
				widthImg,
				heightImg,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				bytes
			);
		else if (numColCh == 1)
			glTexImage2D
			(
				GL_TEXTURE_2D,
				0,
				GL_SRGB_ALPHA,
				widthImg,
				heightImg,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				bytes
			);
		else
			return;
		
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(bytes);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::texUnit(Shaders& shader, const char* uniform, GLuint unit)
	{
		GLuint texUni = glGetUniformLocation(shader.ID, uniform); // Gets the location of the uniform
		shader.Activate(); // Shader needs to be activated before changing the value of a uniform
		glUniform1i(texUni, unit); // Sets the value of the uniform
	}

	void Texture::Bind()
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, ID);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::Delete()
	{
		glDeleteTextures(1, &ID);
	}
}
