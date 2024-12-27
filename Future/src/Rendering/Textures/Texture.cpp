#include "Texture.hpp"

namespace Future
{
	Texture::Texture(const char* image_path, TexType texType, GLuint slot)
	{
		type = texType;
		int widthImg, heightImg, numColCh;
		//stbi_set_flip_vertically_on_load(true);
		unsigned char* bytes = stbi_load(image_path, &widthImg, &heightImg, &numColCh, 0);
		if (!bytes)
		{
			std::cerr << "Failed to load texture: " << image_path << std::endl;
			return;
		}

		glGenTextures(1, &ID);
		// Assigns the texture to a Texture Unit
		glActiveTexture(GL_TEXTURE0 + slot);
		unit = slot;
		glBindTexture(GL_TEXTURE_2D, ID);

		// Configures the type of algorithm that is used to make the image_path smaller or bigger
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Configures the way the texture repeats (if it does at all)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Determine the appropriate internal format and format based on channel count
		GLenum internalFormat;
		GLenum format;

		switch (numColCh)
		{
			case 1: // Single-channel (e.g., grayscale image)
				internalFormat = (type == TexType::NORMAL) ? GL_RGB : GL_SRGB; // Use GL_RGB for NORMAL maps
				format = GL_RGB;
				break;

			case 3: // Three-channel (RGB image)
				internalFormat = (type == TexType::NORMAL) ? GL_RGB : GL_SRGB; // Use GL_RGB for NORMAL maps
				format = GL_RGB;
				break;

			case 4: // Four-channel (RGBA image)
				internalFormat = (type == TexType::NORMAL) ? GL_RGBA : GL_SRGB_ALPHA; // Use GL_RGBA for NORMAL maps
				format = GL_RGBA;
				break;

			default:
				std::cerr << "Unsupported number of channels in texture: " << numColCh << std::endl;
				stbi_image_free(bytes);
				return;
		}

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			internalFormat,
			widthImg,
			heightImg,
			0,
			format,
			GL_UNSIGNED_BYTE,
			bytes
		);
		
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
