#include "OpenGLTexture.h"

#include <stb_image.h>
#include <Raven/utils/DebugTools.h>
#include <glad/glad.h>

rvn::OpenGLTexture2D::OpenGLTexture2D(const std::string & path)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	ASSERT(data, "Failed to load image!");
	_width = width;
	_height = height;

	GLenum internalFormat = 0, dataFormat = 0;
	if (channels == 4)
	{
		internalFormat = GL_RGBA8;
		dataFormat = GL_RGBA;
	}
	else if (channels == 3)
	{
		internalFormat = GL_RGB8;
		dataFormat = GL_RGB;
	}

	ASSERT(internalFormat & dataFormat, "Format not supported!");

	glCreateTextures(GL_TEXTURE_2D, 1, &_id);
	glTextureStorage2D(_id, 1, internalFormat, _width, _height);

	glTextureParameteri(_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(_id, 0, 0, 0, _width, _height, dataFormat, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

rvn::OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &_id);
}

uint32_t rvn::OpenGLTexture2D::getWidth() const
{
	return _width;
}

uint32_t rvn::OpenGLTexture2D::getHeight() const
{
	return _height;
}

void rvn::OpenGLTexture2D::bind(uint32_t slot) const
{
	glBindTextureUnit(slot, _id);
}
