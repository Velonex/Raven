#include "OpenGLBuffer.h"
#include <glad/glad.h>

namespace nfe {

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glGenBuffers(1, &_id);
		glBindBuffer(GL_ARRAY_BUFFER, _id);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	void OpenGLVertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, _id);
	}

	void OpenGLVertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	

	void OpenGLVertexBuffer::setLayout(const BufferLayout& layout)
	{
		_layout = layout;
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &_id);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t size)
	{
		glGenBuffers(1, &_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	void OpenGLIndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
	}

	void OpenGLIndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &_id);
	}
}