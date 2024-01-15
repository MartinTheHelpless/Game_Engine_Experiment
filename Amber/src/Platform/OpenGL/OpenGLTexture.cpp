#include "precHeaders.h"
#include "OpenGLTexture.h"
  
#include <glad/glad.h>

namespace Amber
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path) 
	{ 
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		AM_CORE_ASSERT(data, "Failed to load image!");

		m_Width = width;
		m_Height = height;

		AM_INFO("The texture: {0} has {1} color channels.", path, channels);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

		GLenum internalFormat = 0, dataFormat = 0;

		switch (channels)
		{
		case 1:
			internalFormat = GL_RED;
			dataFormat = 0;
			break;

		case 3:
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
			break;

		case 4:
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
			break;

		default:
			AM_CORE_ASSERT(false, "Texture format not supported");
			break;
		}


		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}