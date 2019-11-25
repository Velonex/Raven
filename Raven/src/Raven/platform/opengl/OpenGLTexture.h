#pragma once

#include <Raven/rendering/Texture.h>

#include <glad/glad.h>

namespace rvn {

	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();

		virtual uint32_t getWidth() const override;
		virtual uint32_t getHeight() const override;

		virtual void setData(void* data, uint32_t size) override;

		virtual void bind(uint32_t slot = 0) const override;
	private:
		uint32_t _width, _height;
		uint32_t _id;
		std::string path;
		GLenum _internalFormat, _format;
	};

}